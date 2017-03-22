#ifndef SHAKA_PARSER_RULE_RULE_NUMBER_H
#define SHAKA_PARSER_RULE_RULE_NUMBER_H

#include "parser/primitives.h"

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
    using shaka::Token;
    bool accept = false;
    std::string buffer;

    shaka::Token token = in.peek();
    if (token.type == Token::Type::NUMBER) {

	    in.get();
	    accept = true;

    	    if (accept == true) {
		    root -> push_child(
		    shaka::Number(std::stoi(token.str)));
    	    }
    }
    return accept;
}

/*
/// @brief Function that checks if the given is a negative number or decimal 
/// or a negative decimal
template <typename T>
bool number_real(
	InputStream& 	in,
	NodePtr 	root,
	T& 		interm
) {
	bool accept = false;
	std::string buffer;

    	if (digit(in, root, buffer)) {
        	while (digit(in, root, buffer));
        	interm += buffer;
        	accept = true;
		
		if (is_decimal(in, root, buffer))
		{
			interm = buffer;
			if (digit(in, root, buffer))
			{
				while(digit(in, root, buffer));
				interm = buffer;
				accept = true;
			}
			else
				accept = false;
		}
	} 
	else 
        	accept = false;

	if (is_negative(in, root, buffer))
	{
		if (digit(in, root, buffer))
	{
			while (digit(in, root, buffer));
			interm += buffer;
			accept = true;
		}

		else
			accept = false;
		
		if (is_decimal(in, root, buffer))
		{
			interm = buffer;
			if (digit(in, root, buffer))
			{
				while (digit(in, root, buffer));
				interm = buffer;	
				accept = true;
			}
			else
				accept = false;
	}
	}	
	return accept;
}
*/
} // namespace rule
} // namespace parser
} // namespace shaka


#endif // SHAKA_PARSER_RULE_RULE_NUMBER_H
