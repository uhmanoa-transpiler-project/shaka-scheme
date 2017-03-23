#ifndef SHAKA_PARSER_RULE_RULE_NUMBER_H
#define SHAKA_PARSER_RULE_RULE_NUMBER_H

#include "parser/primitives.h"
#include "rule_number.h"
#include <cctype>

namespace shaka {
namespace parser {
namespace rule {

	
/// @brief Matches to an integer, and then
///        appends the string matching the integer
///        to interm.
template <typename T>
bool number_integer(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
	bool accept = false;
   
	shaka::Token token = in.peek();

	if(token.type == Token::Type::NUMBER) {
		
	in.get();
	interm += token.str;
	accept = true;
    	}

    	if (accept == true) {
   	root -> push_child(
   		shaka::Number(std::stoi(token.str)));
    	}

   	return accept;
}

template <typename T>
bool number_real(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
	bool accept = false;

	shaka::Token token = in.peek();
    	if(token.type == Token::Type::NUMBER) {

		in.get();
		interm += token.str;
		accept = true;

	}

	if (accept == true) {
		root -> push_child(
   			shaka::Number(std::stod(interm)));
    	}

    	return accept;
}	

template <typename T>
bool number_rational(
	InputStream&	in,
	NodePtr		root,
	T&		interm
) {
	bool accept = false;
	std::string denom;
	std::string numer;
	int fraction;

	shaka::Token token = in.peek();
	if(token.type == Token::Type::NUMBER) {

		in.get();
		interm += token.str;

		fraction = token.str.find("/");
		numer = token.str.substr(0, fraction);
		denom = token.str.substr(fraction + 1, token.str.size());

		accept = true;

		if(accept == true) {
			root -> push_child(
				shaka::Number(std::stoi(numer),
				std::stoi(denom)));
		}

	}
	
	return accept;
}	

} // namespace rule
} // namespace parser
} // namespace shaka


#endif // SHAKA_PARSER_RULE_RULE_NUMBER_H
