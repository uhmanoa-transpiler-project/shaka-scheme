#include <cctype>
#include <exception>
#include <functional>
#include <stack>
#include <string>
#include <iostream>

#include "Number.h"
#include "Symbol.h"
#include "Data.h"
#include "IDataNode.h"

#include "Environment.h"
#include "Evaluator.h"
#include "Eval_Define.h"
#include "Procedure.h"
#include "Eval_Expression.h"
#include "Eval_PrintTree.h"

#include "parser/primitives.h"
#include "parser/Tokenizer.h"
#include "parser/Token.h"

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

	//check for mock procedure call
	if(in.peek().type != shaka::Token::Type::PAREN_START)
		throw std::runtime_error("No Start to Mock Proc Call");
			
	tokens.push(in.get());
	interm += tokens.top().get_string();

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

		if(in.peek().type != shaka::Token::Type::PAREN_END)
			throw std::runtime_error("No End Parenthesis");

		tokens.push(in.get());
		interm += tokens.top().get_string();
	}

	if(in.peek().type != shaka::Token::Type::END_OF_FILE)
		throw std::runtime_error("Excess Symbols Detected");	
	
	switch(tokens.top().type) {
		case shaka::Token::Type::NUMBER:
			if(defNode != nullptr) {
				defNode->push_child(
					shaka::Number(
						std::stod(tokens.top().get_string())
					)
				);
			}
			break;

		default:
			if(defNode != nullptr) {
				defNode->push_child(
					shaka::Symbol(tokens.top().get_string())
				);
			}
			break;
	}

//	if(in.peek().type != shaka::Token::Type::END_OF_FILE) {
	//check for end parenthesis or end of file
//	if(in.peek().type != shaka::Token::Type::PAREN_END) 
//		throw std::runtime_error("No End Parenthesis");
//	}

	return true;

	} catch (std::runtime_error& e) {
		while(!tokens.empty()) {
			in.unget(tokens.top());
			tokens.pop();
		}

		if(defNode != nullptr) {
			std::size_t size = defNode->get_num_children();
			for(std::size_t i = 0; i < size; i++) {
				defNode->remove_child(i);
			}
		}

		return false;
	}
}

}
}
}
