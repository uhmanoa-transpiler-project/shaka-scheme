#ifndef RULE_IF_IMPL_H
#define RULE_IF_IMPL_H

#include "rule_if.h"

namespace shaka {
namespace parser{
namespace rule {

template <typename T>
bool rule_if(
	InputStream&	in,
	NodePtr		root,
	T&		interm
) {

	//Token for if
	Token if_token = in.peek();

	//Check the opening "("
	if(if_token.type == Token::Type::PAREN_START) { in.get(); }
	else { throw std::runtime_error("No Starting Parenthesis"); }

	if_token = in.peek();

	//Check if you have "if"
	if(if_token.type == Token::Type::IDENTIFIER) { 
		in.get();
		interm = if_token.get_string();
		root->push_child( String(interm) );
	}
	else { throw std::runtime_error("No 'if' Declared"); }

	//Check if you have an expression <test>
	expression(in,root->get_child(0),interm);

	//Check if you have an expression <consequent>
	expression(in,root->get_child(0),interm);

	if_token = in.peek();

	//Check for closing 
	if(if_token.type == Token::Type::PAREN_END) { in.get(); }
	else { 
		//Check if you have an expression <alternate>
		expression(in,root->get_child(0),interm);

		if_token = in.peek();

		//Check for closing
		if(if_token.type == Token::Type::PAREN_END) { in.get(); }
		else { throw std::runtime_error("No Alternate or End Parenthesis"); }
	}

}

}	//shaka
}	//parser
}	//rule

#endif //RULE_IF_IMPL_H