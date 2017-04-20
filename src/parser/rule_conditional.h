#ifndef SHAKA_PARSER_RULES_RULE_CONDITIONAL_H_
#define SHAKA_PARSER_RULES_RULE_CONDITIONAL_H_

#include <stack>
#include "parser/primitives.h"

namespace shaka {
namespace parser{
namespace rule {

template <typename T> 
bool conditional(
	InputStream&	in,
	NodePtr	        root,
	T&              interm
);


} // rule
} // parser
} // shaka


#endif // SHAKA_PARSER_RULES_RULE_CONDITIONAL_H_
