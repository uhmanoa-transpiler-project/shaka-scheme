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
	//Token Declaration
	Token str_tok = in.peek();

	//IF the token is of the type STRING
	if(str_tok.type == Token::Type::STRING) {
		//Clear InputStream
		in.get();
		
		//Get string stored in token
		interm = str_tok.get_string();
		
		//Create new DataNode
		//Push DataNode onto tree as child of root
		root->push_child( String(interm) );
		
		return true;
	} else {	
		return false;
	}
	
}

} // namespace rule
} // namespace parser
} // namespace shaka

#endif // RULE_STRING_IMPL_H
