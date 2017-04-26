#ifndef SHAKA_CORE_PARSER_PARSE_H_
#define SHAKA_CORE_PARSER_PARSE_H_

#include <iostream>
#include <exception>
#include <string>
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
                {
                    in.stop();
                    throw shaka::parser::end();
                }
                break;

                case shaka::Token::Type::CHARACTER:
                case shaka::Token::Type::STRING:
                {
                    node->append(DataNode::list(String(in.get().get_string())));
                }
                break;

                case shaka::Token::Type::IDENTIFIER:
                {    
                    if (in.peek().str == "$quit") {
                        in.unget(shaka::Token(shaka::Token::Type::END_OF_FILE));
                        return parse<void>(in, node);
                    }
                    node->append(DataNode::list(Symbol(in.get().get_string())));
                }
                break;

                case shaka::Token::Type::QUOTE:
                {
                    auto quote_expr = make_node(DataNode::list(Symbol("quote")));
                    in.get();
                    if (parse<void>(in, quote_expr)) {
                        node->append(DataNode::list(quote_expr));
                    }
                    else {
                        return false;
                    }
                }
                break;

                case shaka::Token::Type::BOOLEAN_TRUE:
                {
                    node->append(DataNode::list(Boolean(true)));
                    in.get();
                }
                break;

                case shaka::Token::Type::BOOLEAN_FALSE:
                {
                    node->append(DataNode::list(Boolean(false)));
                    in.get();
                }
                break;

                case shaka::Token::Type::NUMBER:
                {
                    std::string numberStr = in.get().get_string();

                    if(numberStr.find(".") != std::string::npos) {
                        node->append( DataNode::list(Number(stod(numberStr))) );
                    }
                    else if(numberStr.find("/") != std::string::npos) {
                        int index = numberStr.find("/");
                        int num   = std::stoi( numberStr.substr(0, index) );
                        int den   = std::stoi( numberStr.substr(index + 1, numberStr.size() - index) );
                        node->append( DataNode::list(Number(num, den)) );
                    }
                    else {
                        node->append( DataNode::list(Number(stoi(numberStr))) );
                    }
                }
                break;

                case shaka::Token::Type::PAREN_START:
                {
                    node->append(DataNode::list(list(in)));
                }
                break;

                case shaka::Token::Type::PERIOD:
                {
                    node->append(cons(in));
                }
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
