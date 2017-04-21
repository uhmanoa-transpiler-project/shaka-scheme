#ifndef RULE_NUMBER_H
#define RULE_NUMBER_H

#include "core/parser/primitives.h"
#include "core/parser/Tokenizer.h"

#include "core/base/Number.h"
#include "core/base/Core.h"
#include "core/base/Data.h"
#include "core/base/DataNode.h"

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


#endif // RULENUMBER_H
