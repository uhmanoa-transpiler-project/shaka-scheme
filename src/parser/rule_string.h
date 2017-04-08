#ifndef RULE_STRING_H
#define RULE_STRING_H

#include <cctype>
#include <iostream>
#include <string>

#include "parser/primitives.h"
#include "parser/Tokenizer.h"
#include "parser/Token.h"

#include "ASCII_String.h"
#include "Data.h"
#include "DataNode.h"
#include "IDataNode.h"

namespace shaka {
namespace parser {
namespace rule {

template <typename T>
bool string(
	InputStream&	in,
	NodePtr			root,
	T&				interm
);

} // namespace rule
} // namespace parser
} // namespace shaka


#endif // SHAKA_PARSER_RULE_CHAR_RULES_IMPL_H
