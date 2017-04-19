#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <deque>

#include "core/base/DataNode.h"
#include "core/parser/Tokenizer.h"
#include "core/parser/list.h"

int main() {
	std::string str;

	std::cin >> str;

	try{
		while(str != "(quit)") {
			std::stringstream ss(str);
			shaka::Tokenizer in(ss);
			
			//shaka::Token token = in.get();
			
			//token = in.get();
			//std::cout << token.get_string() << std::endl;	
			shaka::DataNode node = shaka::parser::list(in);
			std::cout << node << std::endl;

			std::cin >> str;
		}
	} catch(std::runtime_error& e) {
			std::cout << e.what() << std::endl;
	}
}

