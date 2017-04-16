#ifndef RULE_BOOBLEAN_IMPL_H
#define RULE_BOOLEAN_IMPL_H

#include "rule_boolean.h"

namespace shaka {
namespace parser {
namespace rule {

template <typename T>
bool boolean(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
	Token bool_tok = in.peek();
	
	if (bool_tok.type == Token::Type::BOOLEAN_TRUE) {
		//Take string and create DataNode that holds a shaka::Symbol
		//interm temporarily holds a value
		in.get();
		//Create a list with interm
		DataNode list_bool = DataNode::list(Boolean(true));
		//Append the variable
		root->append(list_bool);
		return true;
	}
	
	else if (bool_tok.type == Token::Type::BOOLEAN_FALSE) {
		//Take string and create DataNode that holds a shaka::Symbol
		//interm temporarily holds a value
		in.get();
		//Create a list with interm
		DataNode list_bool = DataNode::list(Boolean(false));
		//Append the variable
		root->append(list_bool);
		return true;
	}

	return false;
	
}

} 
} 
} 

#endif //RULE_BOOLEAN_IMPL_H 
