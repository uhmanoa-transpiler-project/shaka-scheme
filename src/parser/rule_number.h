#ifndef SHAKA_PARSER_RULES_RUL_NUMBER_H
#define SHAKA_PARSER_RULES_RUL_NUMBER_H

#include <cctype>

#include "parser/char_rules.h"

namespace shaka {
namespace parser {
namespace rule {

/// @brief Matches to an integer, and then
///        appends the string matching the integer
///        to interm.
template <typename T>
bool integer(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
    std::string buffer;
    if (digit(in, root, buffer)) {
        while (digit(in, root, buffer));
        interm += buffer;
        return true;
    } else {
        return false;
    }
}

/// @brief Template specialization of integer for int.
/// 
/// Adds the value of the converted string to interm.
template <>
bool integer<int>(
    InputStream&    in,
    NodePtr         root,
    int&            interm
) {
    std::string buffer;
    if (digit(in, root, buffer)) {
        while (digit(in, root, buffer));
        interm += std::stoi(buffer);
        return true;
    } else {
        return false;
    }
}


} // namespace rule
} // namespace parser
} // namespace shaka


#endif // SHAKA_PARSER_RULE_RULE_NUMBER_H
