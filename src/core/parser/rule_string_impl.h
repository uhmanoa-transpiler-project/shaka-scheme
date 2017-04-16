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
	Token str_list = in.peek();

	//IF the token is of the type STRING
	if(str_list.type == Token::Type::STRING) {
		//Clear InputStream
		in.get();
		
		//Get string stored in token
		interm = str_list.get_string();
		
		//Create DataNode list using interm string
		DataNode str_node = DataNode::list(String(interm));

		//Append DataNode list to root root DataNode
		root->append(str_node);
		
		return true;
	} else {	
		return false;
	}
	
}

} // namespace rule
} // namespace parser
} // namespace shaka

#endif // RULE_STRING_IMPL_H
