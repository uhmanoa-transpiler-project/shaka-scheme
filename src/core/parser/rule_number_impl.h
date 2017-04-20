#ifndef RULE_NUMBER_IMPL_H
#define RULE_NUMBER_IMPL_H

#include "rule_number.h"

#include <cctype>
#include <climits>

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

	if(checkLimit(token.str) == false) {
		accept = false;
		throw std::out_of_range("Number entered is too large");

	}

  	if (accept == true) {
        	DataNode d1({Number(std::stoi(interm))}, {NodePtr{nullptr}});
		root -> append(d1);
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

	if(checkLimit(token.str) == false) {
		accept = false;
		throw std::out_of_range("Number entered is too large");

	}
	if (accept == true) {
        	DataNode d1({Number(std::stod(interm))}, {NodePtr{nullptr}});
		root -> append(d1);
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

		if(checkLimit(token.str) == false) {
			accept = false;
			throw std::out_of_range("Number entered is too large");

		}

		if(accept == true) {
        		DataNode d1({Number(std::stoi(numer),
				std::stoi(denom))}, 
				{NodePtr{nullptr}});
			root -> append(d1);
		}

	}
	
	return accept;
}	

bool checkLimit(std::string numstring) {
	int digits = numstring.length();
	int n = LONG_MAX;
	int max[10];
	int num[10];
	int difference = 0;
	int temp_diff;
	int flag = 1;

	//If the number enntered has more digits than the max, invalid number
	if (digits > 10) {
		return false;
	}

	//If the number entered has less digits than the max, valid number
	if (digits < 10) {
		return true;
	}

	//If the number entered has equal digits than max, check by subracting
	//If difference is negative, number entered is invalid
	//If different is positve, number entered is valid
	if (digits == 10) {

		//Put the max number into an array
		for(int i = 10; i > 0; i--) {
			max[i] = n % 10;
			n = n / 10;
		}	
	
		//Put the given digit into an array
		for(int i = 0; i < digits; i++) {
			num[i] = numstring[i] - '0';
		}

		//Subtract the numbers
		for(int i = 10; i > 0; i--) {	
			temp_diff = max[i] - num[i];
			difference = temp_diff * tothepower(10, flag);
			flag++;
		}

		if(difference >= 0) {
			return true;
		}

		else {
			return false;
		}	
	}

	return false;	
}

int tothepower(int base, int power) {
	int value = 1;

	for(int i = 1; i <= power; i++) {
		value = value * base;	
	}

	return value;
}
} // namespace rule
} // namespace parser
} // namespace shaka


#endif // SHAKA_PARSER_RULE_RULE_NUMBER_H
