#ifndef SHAKA_CORE_PARSER_EXPRESSION_H_
#define SHAKA_CORE_PARSER_EXPRESSION_H_

#include <iostream>
#include <exception>
#include "core/parser/primitives.h"
#include "core/parser/list.h"

namespace shaka {
namespace parser {


template <typename T>
bool parse(
    InputStream&    in,
    NodePtr         node
) {



    try {
        while(in.peek().type != shaka::Token::Type::END_OF_FILE) {
            switch(in.peek().type) {

                case shaka::Token::Type::QUOTE:
                    in.get();
                    // TODO:
                    break;

                case shaka::Token::Type::PAREN_START:
                    if(node == nullptr) node = list(in);
                    else                node.append(list(in));
                    break;
            }
        }

    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return false;
    }
}


} // parser
} // shaka

#endif // SHAKA_CORE_PARSER_EXPRESSION_H_
