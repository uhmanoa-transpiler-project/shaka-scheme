#ifndef RULE_STRING_IMPL_H
#define RULE_STRING_IMPL_H

#include "rule_string.h"

namespace shaka {
namespace parser {
namespace rule {

template <typename T>
bool string(
	InputStream&	in,
	NodePtr			root,
	T&				interm
) {
	Token str_tok = in.peek();

	if(str_tok.type == Token::Type::STRING) {
		interm = str_tok.get_string();
		root->push_child( String(interm) );
		return true;
	} else {
		throw std::runtime_error("Could not push DataNode onto tree");
		return false;
	}
	
}

} // namespace rule
} // namespace parser
} // namespace shaka

#endif // RULE_STRING_IMPL_H
