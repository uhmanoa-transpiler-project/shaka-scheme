#ifndef SHAKA_PARSER_RULE_RULE_NUMBER_CDRAFAEL_H
#define SHAKA_PARSER_RULE_RULE_NUMBER_CDRAFAEL_H

#include <cctype>

#include "parser/char_rules_cdrafael.h"

namespace shaka {
namespace parser {
namespace rule {

/// @brief Matches to an integer, and then
///        appends the string matching the integer
///        to interm.
///     
/// This will not put the node onto the tree.
template <typename T>
bool number_integer(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
    std::string buffer;
    if (digit(in, root, buffer)) {
        while (digit(in, root, buffer));
        interm += buffer;
        return true;
    } else {
        return false;
    }
}

template <>
bool number_integer<std::string>(
    InputStream&    in,
    NodePtr         root,
    std::string&    interm
) {
    std::string buffer;
    if (digit(in, root, buffer)) {
        while (digit(in, root, buffer));
        interm += buffer;
        // Now, we have the number
        if (root) {
            root->push_child(
                shaka::Number(std::stoi(interm))       
            );
        }
        return true;
    } else {
        return false;
    }
}

/// @brief Template specialization of integer for int.
/// 
/// Adds the value of the converted string to interm.
template <>
bool number_integer<int>(
    InputStream&    in,
    NodePtr         root,
    int&            interm
) {
    std::string buffer;
    if (digit(in, root, buffer)) {
        while (digit(in, root, buffer));
        interm += std::stoi(buffer);
        // Now, we have the number
        if (root) {
            root->push_child(
                shaka::Number(interm)       
            );
        }
        return true;
    } else {
        return false;
    }
}

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

} // namespace rule
} // namespace parser
} // namespace shaka


#endif // SHAKA_PARSER_RULE_RULE_NUMBER_H
