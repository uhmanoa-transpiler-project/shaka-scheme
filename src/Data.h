#ifndef SHAKA_DATA_H
#define SHAKA_DATA_H

#include <boost/variant.hpp>


namespace shaka {

class Number;
class Symbol;
class String;
class Procedure;

/// @brief Auxillary "type-tags" used to decide whether the
/// contained type should have children, according to the sematnics
/// of the Meta Tag.
///
/// For example, an `ATOM` should have no children nodes, but
/// a `LIST` should have links to its children as a vector of pointers.
enum class MetaTag : int {
    DEFINE = 0,
    LIST = 1,
    PROC_CALL = 2,
    QUOTE = 3,
    LAMBDA = 4
};

using Data = typename
boost::variant<
/*
*/
    boost::recursive_wrapper<shaka::Procedure>,
    shaka::MetaTag,
    shaka::Symbol,
    shaka::Number,
    shaka::String
>;

}

#include "Number.h"
#include "Symbol.h"
#include "ASCII_String.h"
#include "Procedure.h"

std::ostream& operator<< (std::ostream& lhs, const shaka::MetaTag rhs) {
    using shaka::MetaTag;
    if (rhs == MetaTag::DEFINE) { lhs << "DEFINE"; }
    else if (rhs == MetaTag::LIST) { lhs << "LIST"; }
    else if (rhs == MetaTag::PROC_CALL) { lhs << "PROC_CALL"; }
    else if (rhs == MetaTag::QUOTE) { lhs << "QUOTE"; }
    else if (rhs == MetaTag::LAMBDA) { lhs << "LAMBDA"; }
}


#endif // SHAKA_DATA_H
