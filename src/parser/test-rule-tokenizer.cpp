#include <iostream>
#include <queue>
#include <string>

#include "parser/primitives.h"
#include "parser/Tokenizer.h"

#include "Data.h"
#include "DataNode.h"
#include "Procedure.h"

#include "Eval_Expression_impl.h"

namespace shaka {
namespace parser {
namespace rule {

template <typename T> bool expression(InputStream&, NodePtr, T&);
template <typename T> bool list(InputStream&, NodePtr, T&);

template <typename T>
bool expression(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
    using shaka::Token;
    shaka::Token token = in.peek();
    if (token.type == Token::Type::NUMBER) {
        in.get();
        std::cout << "Number: " << token << std::endl;
    } else if (token.type == Token::Type::STRING) {
        in.get();
        std::cout << "String: " << token << std::endl;
    } else if (token.type == Token::Type::PAREN_START) {
        using namespace shaka::parser;
        NodePtr list_node = root->push_child(shaka::MetaTag::LIST);
        int i = 0;
        shaka::parser::rule::list<int>(
            in,
            list_node,
            i
        ); 
    } else {
        in.get();
        std::cout << "Else: " << token << std::endl;
    }
}

template <typename T>
bool list(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
    using shaka::Token;
    if (in.peek().type == Token::Type::PAREN_START) {
        std::cout << "List(" << std::endl;
        in.get();
        NodePtr list_node = root->push_child(shaka::MetaTag::LIST);
        while (in.peek().type != Token::Type::PAREN_END) {
            int i = 0;
            shaka::parser::rule::expression(
                in,
                list_node,
                i
            );
        }
        in.get();
        std::cout << ")" << std::endl;
         
    } else {
        throw std::runtime_error("Parser.rule_List: First token is not (");
    }
}

} // namespace rule
} // namespace parser
} // namespace shaka

int main() {
    // Create the tokenizer
    shaka::Tokenizer tokenizer(std::cin);
    // Create the root of the tree.
    shaka::parser::NodePtr root =
        std::make_shared<shaka::parser::Node>(shaka::MetaTag::LIST);

    // Prompt for input and then evaluate
    do {
        std::cout << ">>> ";
        int i = 0;
        try {
            if (tokenizer.peek().type == shaka::Token::Type::END_OF_FILE) { break; }
            shaka::parser::rule::expression<int>(
                tokenizer,
                root,
                i
            );
        } catch (...) {
            ///
        }
    } while (true);

    return 0;
}
