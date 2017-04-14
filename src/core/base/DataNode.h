#ifndef SHAKA_CORE_BASE_DATANODE_H
#define SHAKA_CORE_BASE_DATANODE_H

#include <boost/variant.hpp>

#include "core/base/Data.h"

namespace shaka {

/// @brief Implements the basic list and literal data structure
///        for Scheme. It is closely related to the pair.
class DataNode : public std::enable_shared_from_this<DataNode>{
public:

    /// @brief Used for cons
    // DataNode (Ptr head, Ptr tail = nullptr) :
    //     head(head),
    //     tail(tail) {}
    DataNode (Data head) :
        head(head),
        tail(nullptr) {}

    DataNode (DataNode left, DataNode right) {

        // If the left node is an atom,
        // then just append the right as its tail
        if (!left.is_pair()) {
            this->head = left.head;
        }
        // Otherwise, we must create a new head to
        // represent the cons of the left list and
        // the right list.
        else {
            auto h = std::make_shared<DataNode>(left.head);
            h->tail = left.tail;
            head = h;
        }

        // Put the tail in the tail slot.
        auto t = std::make_shared<DataNode>(right.head);
        t->tail = right.tail;
        tail = t;
    }

    //DataNode (const DataNode& other) :
    //    head(other.car()),
    //    tail(other.cdr()) {}

    bool is_null() const {
        if (head.type() == typeid(ListPtr)) {
            if (tail.type() == typeid(ListPtr)) {
                return !get<ListPtr>(head) && !get<ListPtr>(tail);
            }
        }
        return false;
    }

    bool is_pair() const {
        if (tail.type() == typeid(ListPtr)) {
            return get<ListPtr>(tail) != nullptr;
        }
        return false;
    }

    static DataNode cons (DataNode left, DataNode right) {
        return DataNode(left, right);
    }


    template <typename T, typename... Args>
    static DataNode list (T head, Args... tail) {
        return list_recursive(head, tail...); 
    }

    ListPtr car() const {
        if (this->is_pair()) {
            if (head.type() == typeid(ListPtr)) {
                return get<ListPtr>(head);
            } else {
                return std::make_shared<DataNode>(head);
            }
        } else {
            throw std::runtime_error("DataNode.cdr: argument is not pair");
            return nullptr;
        }
    }

    ListPtr cdr() const {
        if (this->is_pair()) {
            if (tail.type() == typeid(ListPtr)) {
                return get<ListPtr>(tail);
            }
        } else {
            throw std::runtime_error("DataNode.cdr: argument is not pair");
            return nullptr;
        }
    }

    std::size_t length() const {
        return this->length_recursive(0);
    }
    

    bool is_list() const {
        if (this->is_null()) { return true; }
        else if (this->is_pair()) {
            return this->cdr()->is_list();
        }
    }

    bool is_number() const {
        return !this->is_pair() && this->head.type() == typeid(shaka::Number);
    }

    bool is_string() const {
        return !this->is_pair() && this->head.type() == typeid(shaka::String);
    }

    bool is_symbol() const {
        return !this->is_pair() && this->head.type() == typeid(shaka::Symbol);
    }

    bool is_boolean() const {
        return !this->is_pair() && this->head.type() == typeid(shaka::Boolean);
    }
    
    bool is_environment() const {
        return !this->is_pair() && this->head.type() == typeid(shaka::Environment);
    }

    /// @brief Overloadable virtual destructor
    virtual ~DataNode () {}

    friend bool operator== (DataNode lhs, DataNode rhs);
    friend bool operator!= (DataNode lhs, DataNode rhs);
    friend std::ostream& operator<< (std::ostream& lhs, const DataNode& rhs);
private:
    std::size_t length_recursive(std::size_t l) const {
        if (this->is_null()) { return 0; }
        else if (this->is_pair()) {
            auto next = this->cdr();
            return next->length_recursive(l)+1;
        } else {
            throw std::runtime_error("DataNode.length: argument is not a list.");
            return 0;
        }
    }
    
    template <typename T, typename... Args>
    static DataNode list_recursive(T first, Args... rest) {
        return cons({first}, list_recursive(rest...));
    }

    template <typename T>
    static DataNode list_recursive (T last) {
        return cons({last}, {nullptr});
    }

    // The two storage cells in a list.
    Data head;
    Data tail;
};


bool operator== (shaka::DataNode lhs, shaka::DataNode rhs) {
    if (lhs.is_pair() && rhs.is_pair()) {
        return *lhs.car() == *rhs.car() && *lhs.cdr() == *rhs.cdr();
    }
    else if (!lhs.is_pair() && !rhs.is_pair()) {
        return lhs.head == rhs.head && lhs.tail == rhs.tail;
    }
    else {
        return false;
    }
}

bool operator!= (shaka::DataNode lhs, shaka::DataNode rhs) {
    return !operator==(lhs, rhs);
}


std::ostream& operator<< (std::ostream& lhs, const DataNode& rhs) {
    // If the current one is a single
    if (!rhs.is_pair()) {
        // null list ==> ()
        if (rhs.is_null()) {
            lhs << "()";
        }
        else if (rhs.is_number()) {
            auto data = get<Number>(rhs.head);
            lhs << data;
        }
        else if (rhs.is_string()) {
            auto data = get<String>(rhs.head);
            lhs << data;
        }
        else if (rhs.is_symbol()) {
            auto data = get<Symbol>(rhs.head);
            lhs << data;
        }
        else if (rhs.is_boolean()) {
            auto data = get<Boolean>(rhs.head);
            lhs << data;
        }
        else if (rhs.is_environment()) {
            lhs << "#<environment>";
        }
    }
    // Otherwise, this is some sort of list
    else {
        // Print out the first item.
        lhs << "("; 
        lhs << *rhs.car();
        // Then continue to print out the
        // other items.
        auto tail = *rhs.cdr();
        while (tail.is_pair()) {
            lhs << ' ' << *tail.car();
            tail = *tail.cdr();
        }
        // If this is a proper list, just close it.
        if (tail.is_null()) {
            auto last = get<ListPtr>(tail.tail);
            if (!last) { lhs << ")"; }
        }
        // Otherwise, this is an improper list,
        // and we must print out the last element.
        else {
            auto last = DataNode(tail.head);
            lhs << " . " << last << ")";
        }
    }
    return lhs;
}

}


#endif // SHAKA_CORE_BASE_DATANODE_H
