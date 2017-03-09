#ifndef SHAKA_PARSER_RULE_CHAR_RULES_CDRAFAEL_H
#define SHAKA_PARSER_RULE_CHAR_RULES_CDRAFAEL_H

#include <cctype>

#include "parser/primitives.h"

namespace shaka {
namespace parser {
namespace rule {


/// @brief Matches a digit character, and then appends it to
///        `interm`.
template <typename T>
bool digit(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
    if (std::isdigit(in.peek())) {
        interm += in.get();
        return true;        
    } else {
        return false;
    }
}

/// @brief Rule for '-'
template <typename T>
bool is_negative(
	InputStream&	in,
	NodePtr		root,
	T&		interm
) {
	if (in.peek() == '-')
	{
		interm += in.get();
		return true;
	}
	
	else
		return false;
}

/// @brief Rule for '.'
template <typename T>
bool is_decimal(
	InputStream&	in,
	NodePtr		root,
	T&		interm
) {
	if (in.peek() == '.')
	{
		interm += in.get();
		return true;
	}
	else
		return false;
}

/// @brief Matches an alpha character, and then
///        appends it to `interm`.
template <typename T>
bool alpha(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
    if (std::isalpha(in.peek())) {
        interm += in.get();
        return true;        
    } else {
        return false;
    }
}

/// @brief Matches an alpha character, and then
///        appends it to `interm`.
template <typename T>
bool space(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
    if (std::isspace(in.peek())) {
        interm += in.get();
        return true;        
    } else {
       return false;
    }
}

template <typename T, const char C>
bool match_char(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
    if (in.peek() == C) {
        interm += in.get();
        return true;
    } else {
        return false;
    }
}


} // namespace rule
} // namespace parser
} // namespace shaka


#endif // SHAKA_PARSER_RULE_CHAR_RULES_H
