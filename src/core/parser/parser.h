#ifndef SHAKA_CORE_PARSER_PARSE_H_
#define SHAKA_CORE_PARSER_PARSE_H_

#include <iostream>
#include <exception>
#include "core/parser/primitives.h"
#include "core/parser/list.h"
#include "core/parser/exception.h"

namespace shaka {
namespace parser {


template <typename T>
bool parse(
    InputStream&    in,
    NodePtr         node
) {



    try {
        /*
        while(in.peek().type != shaka::Token::Type::END_OF_FILE) {
        */
        if (in.is_done()) {
            throw shaka::parser::end();
        }
            switch(in.peek().type) {
                case shaka::Token::Type::END_OF_FILE:
                    in.stop();
                    throw shaka::parser::end();
                    break;

                case shaka::Token::Type::CHARACTER:
                case shaka::Token::Type::STRING:
                    node->append(DataNode::list(String(in.get().get_string())));
                    break;

                case shaka::Token::Type::IDENTIFIER:
                    
                    if (in.peek().str == "$quit") {
                        in.unget(shaka::Token(shaka::Token::Type::END_OF_FILE));
                        return parse<void>(in, node);
                    }
                    node->append(DataNode::list(Symbol(in.get().get_string())));
                    break;

                case shaka::Token::Type::QUOTE:
                    node->append(DataNode::list(Symbol("quote")));
                    in.get();
                    break;

                case shaka::Token::Type::BOOLEAN_TRUE:
                    node->append(DataNode::list(Boolean(true)));
                    in.get();
                    break;

                case shaka::Token::Type::BOOLEAN_FALSE:
                    node->append(DataNode::list(Boolean(false)));
                    in.get();
                    break;

                case shaka::Token::Type::NUMBER:
                    node->append(
                        DataNode::list(
                            Number(
                                stod(in.get().get_string())
                            )
                        )
                    );
                    break;

                case shaka::Token::Type::PAREN_START:
                    node->append(DataNode::list(list(in)));
                    break;

                case shaka::Token::Type::PERIOD:
                    node->append(cons(in));
                    break;
                    
                default:
                    throw std::runtime_error("LIST: Got to default");
                    break; 
            } // end switch
        /*
        }
        */

    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}


} // parser
} // shaka

#endif // SHAKA_CORE_PARSER_PARSE_H_
