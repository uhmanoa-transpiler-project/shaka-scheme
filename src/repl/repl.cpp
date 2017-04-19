#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <deque>

#include "core/base/DataNode.h"
#include "core/parser/Tokenizer.h"
#include "core/parser/list.h"

int main() {
	shaka::Tokenizer in(std::cin);

	shaka::Token token = in.get();

	while(token.get_string() != "(quit)") {
//		token = in.get();
		try{
			shaka::DataNode node = shaka::parser::list(in);
			std::cout << node << std::endl;
		} catch(std::runtime_error& e) {
			std::cout << e.what() << std::endl;
		}
	}

}
