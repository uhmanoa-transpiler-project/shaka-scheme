#ifndef SHAKA_PARSER_RULE_RULE_NUMBER_H
#define SHAKA_PARSER_RULE_RULE_NUMBER_H

#include "parser/primitives.h"

#include <cctype>

namespace shaka {
namespace parser {
namespace rule {

bool checkLimit(std::string s);
int tothepower(int base, int power);
	
/// @brief Matches to an integer, and then
///        appends the string matching the integer
///        to interm.
template <typename T>
bool number_integer(
    InputStream&    in,
    NodePtr         root,
    T&              interm
);

template <typename T>
bool number_real(
    InputStream&    in,
    NodePtr         root,
    T&              interm
);

template <typename T>
bool number_rational(
	InputStream&	in,
	NodePtr		root,
	T&		interm
);

} // namespace rule
} // namespace parser
} // namespace shaka


#endif // SHAKA_PARSER_RULE_RULE_NUMBER_H
