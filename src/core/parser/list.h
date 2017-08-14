#ifndef SHAKA_CORE_PARSER_LIST_H_
#define SHAKA_CORE_PARSER_LIST_H_

#include "core/parser/primitives.h"

namespace shaka {
namespace parser {

template <typename T>
bool parse(
    InputStream&    in,
    NodePtr         node
);

DataNode cons(
    InputStream& in
);

// Function that may be recursively called which 
// populated any nested lists and returns them.
DataNode list(
    InputStream& in
) {

    DataNode node(NodePtr(nullptr));

    if(in.peek().type != shaka::Token::Type::PAREN_START)
        throw std::runtime_error("LIST: No start parethesis");

    in.get(); // Gets the start parenthesis

    while(in.peek().type != shaka::Token::Type::PAREN_END) {

        switch(in.peek().type) {

            case shaka::Token::Type::CHARACTER:
            case shaka::Token::Type::STRING:
                node.append(DataNode::list(String(in.get().get_string())));
                break;

            case shaka::Token::Type::IDENTIFIER:
                node.append(DataNode::list(Symbol(in.get().get_string())));
                break;

            case shaka::Token::Type::QUOTE:
                {
                    in.get();
                    auto quote_expr = make_node(DataNode::list(Symbol("quote")));
                    if(parse<void>(in, quote_expr)) {
                        node.append(DataNode::list(quote_expr));
                    }
                    else {
                        throw std::runtime_error("List: Invalid quote");
                    }
                }
                break;

            case shaka::Token::Type::BOOLEAN_TRUE:
                node.append(DataNode::list(Boolean(true)));
                in.get();
                break;

            case shaka::Token::Type::BOOLEAN_FALSE:
                node.append(DataNode::list(Boolean(false)));
                in.get();
                break;

            case shaka::Token::Type::NUMBER:
                {
                    std::string numberStr = in.get().get_string();

                    if(numberStr.find(".") != std::string::npos) {
                        node.append( DataNode::list(Number(stod(numberStr))) );
                    }
                    else if(numberStr.find("/") != std::string::npos) {
                        int index = numberStr.find("/");
                        int num   = stoi( numberStr.substr(0, index) );
                        int den   = stoi( numberStr.substr(index + 1, numberStr.size() - index) );
                        node.append( DataNode::list(Number(num, den)) );
                    }
                    else {
                        node.append( DataNode::list(Number(stoi(numberStr))) );
                    }
                }
                break;

            case shaka::Token::Type::PAREN_START:
                node.append(DataNode::list(list(in)));
                break;

            case shaka::Token::Type::PERIOD:
                node.append(cons(in));
                break;
                
            default:
                throw std::runtime_error("LIST: Got to default");
                break;

        } // end switch

    } // end while
    if(in.peek().type == shaka::Token::Type::PAREN_END)
        in.get();
    return node;
}

/* If this function is called, then there is a period currently
 * on the InputStream. This function needs to parse in the period
 * as well as anything that comes after the period.
 *
 * After the period, we expect an atom or a single list.
 */
DataNode cons(
    InputStream& in
) {

    if(in.peek().type != shaka::Token::Type::PERIOD)
        throw std::runtime_error("CONS: No period on InputStream");
    in.get();

    switch(in.peek().type) {
    
        case shaka::Token::Type::IDENTIFIER:
            return DataNode(Symbol(in.get().get_string()));

        case shaka::Token::Type::BOOLEAN_TRUE:
            in.get();
            return DataNode(Boolean(true));

        case shaka::Token::Type::BOOLEAN_FALSE:
            in.get();
            return DataNode(Boolean(false));

        case shaka::Token::Type::CHARACTER:
        case shaka::Token::Type::STRING:
            return DataNode(String(in.get().get_string()));

        case shaka::Token::Type::QUOTE:
            return DataNode(Symbol("quote"));

        case shaka::Token::Type::NUMBER:
            return DataNode(Number(stod(in.get().get_string())));

        case shaka::Token::Type::PAREN_START:
            return list(in);

        default:
            throw std::runtime_error("CONS: No valid Token after period");
            break;

    } // switch end
} // cons end



} // parser
} // shaka

#endif // SHAKA_CORE_PARSER_LIST_H_
