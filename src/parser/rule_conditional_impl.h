#include "rule_conditional.h"

namespace shaka {
namespace parser{
namespace rule {

template <typename T>
bool conditional(
	InputStream&	in,
	NodePtr		root,
	T&		interm
) {
	using shaka::Token;

	std::stack<shaka::Token> tokens;
	NodePtr ifNode;
	shaka::Data tag = shaka::MetaTag::IF;

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

	try {
	//check for start parenthesis
	if(in.peek().type != shaka::Token::Type::PAREN_START) 
	        throw std::runtime_error("No Starting Parenthesis");

	tokens.push(in.get());
	interm += tokens.top().get_string();

	//check for "if" token
        if(in.peek() != if_token)
		throw std::runtime_error("No 'if' Declared");

	tokens.push(in.get());
	interm += tokens.top().get_string();

	//Add "if" statement as root node
	if(root != nullptr)
		ifNode = root->push_child(shaka::Data{shaka::MetaTag::IF});

	//check for mock procedure call
	if(in.peek().type != shaka::Token::Type::PAREN_START)
		throw std::runtime_error("No Start to Mock Proc Call");
			
	tokens.push(in.get());
	interm += tokens.top().get_string();

	//add "(" to tree
	if(ifNode != nullptr)
		ifNode->push_child(shaka::String(tokens.top().get_string()));

	//check for mock symbol
	if(in.peek().type != shaka::Token::Type::IDENTIFIER)
		throw std::runtime_error("No Symbol in Mock Proc Call");	
	
	tokens.push(in.get());
	interm += tokens.top().get_string();
		
	//check for first mock number
	if(in.peek().type != shaka::Token::Type::NUMBER) 
		throw std::runtime_error("No first numerical variable");

	tokens.push(in.get());
	interm += tokens.top().get_string();

	//check for second mock number
	if(in.peek().type != shaka::Token::Type::NUMBER)
		throw std::runtime_error("No second numerical variable");
		
	tokens.push(in.get());
	interm += tokens.top().get_string();

	//check for end of mock procedure call
	if(in.peek().type != shaka::Token::Type::PAREN_END)
		throw std::runtime_error("No End to Mock Proc Call");

	tokens.push(in.get());
	interm += tokens.top().get_string();

	//check for first condition
	if(in.peek().type != shaka::Token::Type::BOOLEAN_TRUE  && 
	   in.peek().type != shaka::Token::Type::BOOLEAN_FALSE &&
	   in.peek().type != shaka::Token::Type::IDENTIFIER)
		throw std::runtime_error("No Consequent");

	tokens.push(in.get());
	interm += tokens.top().get_string();

	//add first condition to tree
	if(ifNode != nullptr) {
		switch(tokens.top().type) {
			case shaka::Token::Type::NUMBER:
				ifNode->push_child(
					shaka::Number(
						std::stod(tokens.top().get_string())
					)
				);

				break;

			default:
				ifNode->push_child(
					shaka::Symbol(tokens.top().get_string()));
				break;
		}
	}

	//check for second condition or end parenthesis
	if(in.peek().type != shaka::Token::Type::BOOLEAN_TRUE  &&
	   in.peek().type != shaka::Token::Type::BOOLEAN_FALSE &&
	   in.peek().type != shaka::Token::Type::IDENTIFIER    &&
	   in.peek().type != shaka::Token::Type::PAREN_END)
		throw std::runtime_error("No Alternate or End Parenthesis");

	if(in.peek().type == shaka::Token::Type::PAREN_END){		
		tokens.push(in.get());
        	interm += tokens.top().get_string();
	}

	else {
		tokens.push(in.get());
		interm += tokens.top().get_string();

		//add second condition to tree
		if(ifNode != nullptr) {
			switch(tokens.top().type) {
				case shaka::Token::Type::NUMBER:
					ifNode->push_child(
						shaka::Number(
							std::stod(
								tokens.top().
								get_string())
						)
					);

					break;

				default:
					ifNode->push_child(
						shaka::Symbol(tokens.top().
								get_string()));
					break;
			}
		}


		if(in.peek().type != shaka::Token::Type::PAREN_END)
			throw std::runtime_error("No End Parenthesis");

		tokens.push(in.get());
		interm += tokens.top().get_string();
	}

	if(in.peek().type != shaka::Token::Type::END_OF_FILE)
		throw std::runtime_error("Excess Symbols Detected");

	return true;

	} catch (std::runtime_error& e) {
		while(!tokens.empty()) {
			in.unget(tokens.top());
			tokens.pop();
		}

		if(ifNode != nullptr) {
			std::size_t size = ifNode->get_num_children();
			for(std::size_t i = 0; i < size; i++) {
				ifNode->remove_child(i);
			}
		}

		return false;
	}
}

}
}
}
