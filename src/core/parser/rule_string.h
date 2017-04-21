#ifndef RULE_STRING_H
#define RULE_STRING_H

#include <cctype>
#include <iostream>
#include <string>

#include "core/parser/primitives.h"
#include "core/parser/Tokenizer.h"
//#include "core/parser/Token.h"

#include "core/base/String.h"
#include "core/base/Core.h"
#include "core/base/Data.h"
#include "core/base/DataNode.h"

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
