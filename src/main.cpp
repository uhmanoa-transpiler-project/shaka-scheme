#include <iostream>
#include <string>
#include <limits>

#include <boost/variant.hpp>

#include "DataNode.h"
#include "DummyDataNode.h"

#include "Tree.h"

using namespace shaka;

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
/*
bool REPL(std::istream& in, std::ostream& out, ITree<>& tree) {

    // Stores the input string line.
    std::string buffer;

    /// @todo Make REPL prompt string customizable.
    out << ">>> ";

    /// @todo Create a more sophisticated buffer function.
    std::getline(in, buffer, '\n');

    std::cout << get<std::string>(tree.get_data()->data) << std::endl;

    // Basic echo if not quit logic.
    /// @todo Fix the processing/parser logic.
    if (buffer == "(quit)") {
        return false;
    } else {
        std::cout << buffer << std::endl;
        return true;
    }
    /// @todo REMOVE THIS
    //asdfasdf
    //asdf
    //sadf
    //as
    //df
    //s
    //sa
    //fd
    //sa
    //
    //
}
*/


/// @brief The main function. Implements the REPL.
int main() {
    // The main REPL loop. 
    // Will stop only when it returns false (quits).
    /// @see REPL
    /*
    using Data = boost::variant<
        bool,
        int,
        std::string,
        MetaTag
    >;
    */

    //DummyDataNode< root("root");

    //while (REPL(std::cin, std::cout, root)) {}

    return 0;
}
