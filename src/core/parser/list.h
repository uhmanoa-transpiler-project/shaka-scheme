#ifndef SHAKA_CORE_PARSER_LIST_H_
#define SHAKA_CORE_PARSER_LIST_H_

#include <iostream>
#include <exception>
#include "core/parser/primitives.h"

namespace shaka {
namespace parser {

template <typename T>
bool cons(
    InputStream&    in,
    NodePtr         root,
    T&              interm
);

// Function that may be recursively called which 
// populated any nested lists and returns them.
template <typename T>
bool list(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {


    if(in.peek().type != shaka::Token::Type::PAREN_START)
        throw std::runtime_error("LIST: No start parethesis");

    in.get(); // Gets the start parenthesis

    while(in.peek().type != shaka::Token::Type::PAREN_END) {

        switch(in.peek().type) {

            case shaka::Token::Type::CHARACTER:
            case shaka::Token::Type::STRING:
                root->append(DataNode::list(String(in.get().get_string())));
                break;

            case shaka::Token::Type::IDENTIFIER:
                root->append(DataNode::list(Symbol(in.get().get_string())));
                break;

            case shaka::Token::Type::QUOTE:
                root->append(DataNode::list(Symbol("quote")));
                in.get();
                break;

            case shaka::Token::Type::BOOLEAN_TRUE:
                root->append(DataNode::list(Boolean(true)));
                in.get();
                break;

            case shaka::Token::Type::BOOLEAN_FALSE:
                root->append(DataNode::list(Boolean(false)));
                in.get();
                break;

            case shaka::Token::Type::NUMBER:
                root->append(
                    DataNode::list(
                        Number(
                            stod(in.get().get_string())
                        )
                    )
                );
                break;

            case shaka::Token::Type::PAREN_START:
                std::cout << *root;
                root->append(DataNode::list(DataNode::list()));
                std::cout << "About to enter List recursive\n";
                std::cout << *root;
                list(in, root->cdr(), interm);
                std::cout << "FINISHED RECURSIVE LIST CALL\n";
                std::cout << *root;
                break;

            case shaka::Token::Type::PERIOD:
                if(!cons(in, root, interm))
                    throw std::runtime_error("LIST: Failed to cons");
                break;
                
            default:
                throw std::runtime_error("LIST: Got to default");
                break;

        } // end switch

    } // end while
    if(in.peek().type == shaka::Token::Type::PAREN_END)
        in.get();
    return true;
}

/* If this function is called, then there is a period currently
 * on the InputStream. This function needs to parse in the period
 * as well as anything that comes after the period.
 *
 * After the period, we expect an atom or a single list.
 */
template <typename T>
bool cons(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {

    try {
        if(in.peek().type != shaka::Token::Type::PERIOD)
            throw std::runtime_error("CONS: No period on InputStream");
        in.get();

        switch(in.peek().type) {
        
            case shaka::Token::Type::IDENTIFIER:
                root->append(DataNode(Symbol(in.get().get_string())));
                break;

            case shaka::Token::Type::BOOLEAN_TRUE:
                in.get();
                root->append(DataNode(Boolean(true)));
                break;

            case shaka::Token::Type::BOOLEAN_FALSE:
                in.get();
                root->append(DataNode(Boolean(false)));
                break;

            case shaka::Token::Type::CHARACTER:
            case shaka::Token::Type::STRING:
                root->append(DataNode(String(in.get().get_string())));
                break;

            case shaka::Token::Type::QUOTE:
                root->append(DataNode(Symbol("quote")));
                break;

            case shaka::Token::Type::NUMBER:
                root->append(DataNode(Number(stod(in.get().get_string()))));
                break;

            case shaka::Token::Type::PAREN_START:
                if(!list(in, root, interm))
                    throw std::runtime_error("CONS: No valid list");
                break;

            default:
                throw std::runtime_error("CONS: No valid Token after period");
                break;

        } // switch end
        return true;

    } catch(std::runtime_error& e) {
        return false;
    }
} // cons end



} // parser
} // shaka

#endif // SHAKA_CORE_PARSER_LIST_H_
