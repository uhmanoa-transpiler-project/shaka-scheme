/// @file main.cpp

#include <iostream>
#include <string>
#include <limits>

#include <boost/variant.hpp>

/// @brief The central data structure for a Scheme object.
///
/// The Shaka Scheme data node implements the core data structure
/// for all objects by providing a sum (variant) type. To leverage
/// already existing code, `boost::variant` from the Boost C++ Library
/// has been adopted to handle that part of the internal data structure.
///
/// DataNode is a variant-type node that is meant to be used as a part
/// of a tree data structure. As all Scheme programs are in the form of
/// trees due to the expression-only nature of the grammar and semantics
/// of the language, it is easy to idealize the organization of data as a
/// tree.
///
/// As it is the core data class for the project, it is also the primary
/// interface for data exchange within the program, along with DataTree.
struct DataNode {

    /// @brief Auxillary "type-tags" used to decide whether the
    /// contained type should have children, according to the sematnics
    /// of the Meta Tag.
    ///
    /// For example, an `ATOM` should have no children nodes, but
    /// a `LIST` should have links to its children as a vector of pointers.
    enum class MetaTag : int {
        
        LIST,
        PROCEDURE,
        IF,
        PAIR,
        VECTOR,
        BYTEVECTOR,
        NULL_LIST,
        ATOM,
        RECORD
    };

    /// @brief `boost::variant` is being re-aliased for the
    /// readability purposes of the project.
    using Data = 
    boost::variant<
        bool,
        int,
        std::string,
        MetaTag
    >;

    /// The key tag by which **Disjointness of Types** (R7RS, Sect. 3.2)
    /// will be implemented with and be kept updated with.
    MetaTag type_tag;

    /// The internal variant data type that will contain
    /// a reference to one of the contained data types.
    Data    data;
};

// #include <map>
// 
// struct Environment {
//     std::map<std::string, DataNode> symbol_table;
// };




struct DummyDataNode {
    enum class DummyMetaTag : int {
        SET,
        GET
    };

    using DummyData = boost::variant<
        std::string,
        DummyMetaTag
    >;

    DummyDataNode(std::string str) :
        data(str) {}

    DummyDataNode(DummyMetaTag metatag) :
        data(metatag) {}

    DummyMetaTag    type_tag;
    DummyData            data;
};

#include <memory>

/// @brief The interface for our internal `Tree` data structure.
///
/// The `ITree` requires use of `std::shared_ptr` for thread safety.
template <typename T>
struct ITree {
    /// @brief Overloadable destructor.
    virtual ~ITree() {}

    virtual std::shared_ptr<ITree> get_parent() = 0;
    virtual std::shared_ptr<ITree> insert_child(
        int                         index,
        std::shared_ptr<ITree<T>>   node
    ) = 0;
    virtual std::shared_ptr<ITree> push_child(T data) = 0;
    virtual std::shared_ptr<ITree> remove_child(int index) = 0;
    virtual std::shared_ptr<ITree> get_child(int index) = 0;
    virtual std::shared_ptr<ITree> get_last_child() = 0;
    virtual std::shared_ptr<T>        get_data() = 0;
    virtual std::shared_ptr<T>        set_data(T data) = 0;
};

#include <vector>

/// @brief A basic implementation of the `ITree` interface.
template <typename T>
struct Tree : public ITree<T> {
    virtual ~Tree() {}

    template <typename... Args>
    Tree(Args&&... args) :
        data(std::make_shared<T>(std::forward<Args&&...>(args)...)) {}

    virtual std::shared_ptr<ITree<T>> get_parent() {
        // If we can get the parent from the weak pointer,
        // then return it.

        // Otherwise, return a nullptr.
        if (auto ptr = this->parent.lock()) {
            return ptr;
        } else {
            /// @todo Decide on whether we should return nullptr or
            /// throw an exception.
            return nullptr;
        }
    }


    virtual std::shared_ptr<ITree<T>> insert_child(
        int                         index,
        std::shared_ptr<ITree<T>>   node
    ) {
        try {
            return *(this->children.insert(
                        this->children.begin() + valid_index(index),
                        node
                   ));
        } catch (std::runtime_error& e) {
            return nullptr;
        }
    }

    virtual std::shared_ptr<ITree<T>> remove_child(int index) {
        try {
            return *(this->children.erase(this->children.begin() + valid_index(index)));
        } catch (std::runtime_error& e) {
            return nullptr;
        }
    }

    virtual std::shared_ptr<ITree<T>> push_child(T data) {
        this->children.push_back(std::make_shared<Tree<T>>(data));
        return this->children[this->children.size() - 1];
    }

    virtual std::shared_ptr<ITree<T>> get_child(int index) {
        try {
            return this->children[valid_index(index)];
        } catch (std::runtime_error& e) {
            return nullptr;
        }
    }

    virtual std::shared_ptr<ITree<T>> get_last_child() {
        if (this->children.size() > 0) {
            return this->children[this->children.size() - 1];
        } else {
            return nullptr;
        }
    }

    virtual std::shared_ptr<T>        get_data() {
        return this->data;
    }

    virtual std::shared_ptr<T>        set_data(T data) {
        *this->data = data;
        return this->data;
    }

    std::vector<std::shared_ptr<ITree<T>>>   children;
    std::weak_ptr<ITree<T>>                  parent;    
    std::shared_ptr<T>                       data;

private:
    size_t valid_index(int index) {
        if (index >= 0) {
            const size_t pos_index = static_cast<size_t>(index);

            if (pos_index < this->children.size()) {
                return pos_index;
            } else {
                throw std::runtime_error("Tree<T>: Index is invalid (out of bounds).");
                return std::numeric_limits<size_t>::max();
            }
        } else {
            throw std::runtime_error("Tree<T>: Index is invalid (negative).");
            return std::numeric_limits<size_t>::max();
        }
    }
};

/// @brief The main Read-Eval-Print Loop (REPL) function.
///
/// Currently only a skeleton.
///
/// @param in
///     The input stream to read from. Usually std::cin but can also
///     be a file.
/// @param out
///     The output stream by which we are prompting the user/program for input.
/// @return
///         - \c true if the REPL needs to continue reading
///         - \c false if the REPL is done reading
bool REPL(std::istream& in, std::ostream& out, ITree<DummyDataNode>& tree) {

    // Stores the input string line.
    std::string buffer;

    /// @todo Make REPL prompt string customizable.
    out << ">>> ";

    /// @todo Create a more sophisticated buffer function.
    std::getline(in, buffer, '\n');

    std::cout << boost::get<std::string>(tree.get_data()->data) << std::endl;

    // Basic echo if not quit logic.
    /// @todo Fix the processing/parser logic.
    if (buffer == "(quit)") {
        return false;
    } else {
        std::cout << buffer << std::endl;
        return true;
    }
}


/// @brief The main function. Implements the REPL.
int main() {
    // The main REPL loop. 
    // Will stop only when it returns false (quits).
    /// @see REPL
    Tree<DummyDataNode> root("root");

    while (REPL(std::cin, std::cout, root)) {}

    return 0;
}