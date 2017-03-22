#include <stack>
#include "parser/primitives.h"

namespace shaka {
namespace parser{
namespace rule {

template <typename T> 
bool conditional(
	InputStream&	in,
	NodePtr		root,
	T&		interm
);

template <typename T>
bool conditional(
	InputStream&	in,
	NodePtr		root,
	T&		interm
) {
	using shaka::Token;

	std::stack<shaka::Token> tokens;
	std::shared_ptr<Node> defNode;

	//define if token as "if"
	shaka::Token if_token(
		shaka::Token::Type::IDENTIFIER,
		"if"
	);

	//define mock symbol as ">"
	shaka::Token mock_symbol(
		shaka::Token::Type::IDENTIFIER,
		">"
	);

	//define first mock number as 3
	shaka::Token mock_num1(
		shaka::Token::Type::NUMBER,
		"3"
	);

	//define second mock number as 2
	shaka::Token mock_num2(
		shaka::Token::Type::NUMBER,
		"2"
	);

	//check for start parenthesis
	if(in.peek().type == shaka::Token::Type::PAREN_START){	
	        tokens.push(in.get());
		interm += tokens.top().get_string();

		//check for "if" token
           	if(in.peek() == if_token) {
			tokens.push(in.get());
			interm += tokens.top().get_string();

		//check for mock procedure call
		if(in.peek().type == shaka::Token::Type::PAREN_START) {
			tokens.push(in.get());
			interm += tokens.top().get_string();

		//check for mock symbol
		if(in.peek() == mock_symbol) {
			tokens.push(in.get());
			interm += tokens.top().get_string();
		
		//check for first mock number
		if(in.peek() == mock_num1) {
			tokens.push(in.get());
			interm += tokens.top().get_string();

		//check for second mock number
		if(in.peek() == mock_num2) {
			tokens.push(in.get());
			interm += tokens.top().get_string();

		//check for end of mock procedure call
		if(in.peek().type == shaka::Token::Type::PAREN_END) {
			tokens.push(in.get());
			interm += tokens.top().get_string();

		//check for boolean true
		if(in.peek().type == shaka::Token::Type::BOOLEAN_TRUE) {
			tokens.push(in.get());
			interm += tokens.top().get_string();

		//check for boolean false
		if(in.peek().type == shaka::Token::Type::BOOLEAN_FALSE) {
			tokens.push(in.get());
		        interm += tokens.top().get_string();	
			
		//check for end parenthesis
		if(in.peek().type == shaka::Token::Type::PAREN_END) {
			return true;
		}

		else return false;
		} //end of boolean false
			
		else return false;
		} //end of boolean true

		else return false;
		} //end of end of mock proc call 

		else return false;
		} //end of second mock number

		else return false;
		} //end of first mock number
		
		else return false;
		} //end of mock symbol

		else return false;
		} //end of procedure call check

		else return false;
		} //end of "if" token check

//		else if(in.peek().type == shaka::Token::Type::END_OF_FILE) {
//			return false;
//		}

	}

	else return false;	
} //end of first parenthesis check

}
}
}
