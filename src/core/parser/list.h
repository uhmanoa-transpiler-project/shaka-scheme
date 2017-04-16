#ifndef SHAKA_CORE_PARSER_LIST_H_
#define SHAKA_CORE_PARSER_LIST_H_

#include <deque>
#include "core/parser/primitives.h"
#include "core/parser/quote.h"

namespace shaka {
namespace parser {

// Function that may be recursively called which 
// populated any nested lists and returns them.
DataNode list(
    InputStream& in
) {

    std::deque<shaka::Token> deque;
    DataNode node(NodePtr(nullptr));

    if(in.peek().type != shaka::Token::Type::PAREN_START)
        throw std::runtime_error("LIST: No start parethesis");

    in.get(); // Gets the start parenthesis


    while(in.peek().type != shaka::Token::Type::PAREN_END ||
          in.peek().type != shaka::Token::Type::END_OF_FILE) {

        switch(in.peek().type) {

            case shaka::Token::Type::IDENTIFIER:
                node.append(DataNode::list(Symbol(in.get().get_string()));
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
                node.append(
                    DataNode::list(
                        Number(
                            stod(in.get().get_string())
                        )
                    )
                );
                break;

            case shaka::Token::Type::CHARACTER:
            case shaka::Token::Type::STRING:
                node.append(DataNode::list(String(in.get().get_string()));
                break;
        } // end switch

        if(in.peek().type == shaka::Token::Type::QUOTE) {
            node.append(quote(in));
        }
    }
}


} // parser
} // shaka

#endif // SHAKA_CORE_PARSER_LIST_H_
