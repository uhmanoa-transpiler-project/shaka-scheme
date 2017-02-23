#ifndef BIGINT_H
#define BIGINT_H
#include <cmath>
#include <boost/variant.hpp>
#include <boost/flyweight.hpp>
#include <typeinfo>
#include <vector>
#include <string>
//#include <stdlib>


	class BigInt
	{
//		~BigInt() {}

		// Description of Constructors below:
		//  store value in vector<int> given a long long int
		//  store value in vector<int> given a string

	  //  BigInt(long long int llival) { llint_to_array(llival); }
	   // BigInt(string sval) { string_to_intarray(sval); }

	public:
		//Get big int as string

		using Value = std::string;
		BigInt(Value v) : bvalue(v) {}

		Value get_Value() { return bvalue; }

		void string_to_intarray(std::string bvalue);

		BigInt(){}

		std::vector<int> value (100, 0);
		//std::vector<int> get_Vector() { return BigInt::value; }
		

		// Operations to be overloaded:
		//      Add
		//      Subtract
		//      Multiply
		//      Exponents
		//      Factorial
		//      Divide
		//      Modulo

	private:

		std::string bvalue;

		// Vector of ints
		std::vector<int> value;
		int length;
		
		// Functions for constructors
//		void llint_to_array(long long int v);
		

	};


	// Private Functions for constructors

//	void BigInt::llint_to_array(long long int v)
//	{
//	}

	void BigInt::string_to_intarray(std::string bvalue)
	{
		std::stringstream ss(bvalue);
			std::string temp;
			int itemp;
		while (ss >> temp) {
			itemp = std::stoi(temp);
			value.push_back(itemp);
		}
/*
		for (int j = 0; j < value.size(); j++) {
			std::cout << value.at(j) << " " << "\n";
		}*/
	}



#endif // BIGINT_H
