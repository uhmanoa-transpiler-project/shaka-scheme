#ifndef SHAKA_DATA_H
#define SHAKA_DATA_H

#include <boost/variant.hpp>


namespace shaka {

class Number;
class Symbol;
class String;
class Procedure;
class Boolean;

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
    shaka::String,
    shaka::Boolean
>;

}
#include "Boolean.h"
#include "Number.h"
#include "Symbol.h"
#include "ASCII_String.h"
#include "Procedure.h"


#endif // SHAKA_DATA_H
