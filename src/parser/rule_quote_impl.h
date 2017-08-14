#ifndef SHAKA_PARSER_RULES_RULE_LIST_IMPL_H
#define SHAKA_PARSER_RULES_RULE_LIST_IMPL_H

#include "parser/primitives.h"
#include "rule_quote.h"
#include <cctype>
#include <functional>
#include <vector>

namespace shaka {
namespace parser {
namespace rule {

// '(<datum>)
template <typename T>
bool quote_literal(InputStream& in,NodePtr root, T& interm) {
  std::stack<shaka::Token> tokens;
  NodePtr defNode;

  try {
    // '
    if (in.peek().type != shaka::Token::Type::QUOTE)
      throw std::runtime_error("BRUH WTF");

    tokens.push(in.get());
    interm += tokens.top().get_string();

    if(root != nullptr)
        defNode = root->push_child(shaka::Data{shaka::MetaTag::LIST});

    // (
    if (in.peek().type != shaka::Token::Type::PAREN_START)
      throw std::runtime_error("No open parenthesis");

    tokens.push(in.get());
    interm += tokens.top().get_string();

    // <datum>
    while (true)
    {
      if (in.peek().type == shaka::Token::Type::PAREN_END) {
        tokens.push(in.get());
        interm += tokens.top().get_string();
        break;
      }
      else if (in.peek().type == shaka::Token::Type::NUMBER) {
        tokens.push(in.get());
        interm += tokens.top().get_string();

        if(defNode != nullptr) defNode->push_child(shaka::Number(std::stod(tokens.top().get_string())));
      }
      else if (in.peek().type == shaka::Token::Type::IDENTIFIER || in.peek().type == shaka::Token::Type::CHARACTER ||
               in.peek().type ==  shaka::Token::Type::STRING  || in.peek().type == shaka::Token::Type::BOOLEAN_TRUE ||
               in.peek().type == shaka::Token::Type::BOOLEAN_FALSE) {
        tokens.push(in.get());
        interm += tokens.top().get_string();
        if(defNode != nullptr) {
            defNode->push_child(shaka::Symbol(tokens.top().get_string()));
        }
      }
      else
          throw std::runtime_error("BRUH WTF");
    }

    return true;

  }
  catch (std::runtime_error& e) {
    while(!tokens.empty()) {
        shaka::Token bruh = tokens.top();
        in.unget(tokens.top());
        tokens.pop();
    }

    // delete defNode and children
    if(defNode != nullptr) {

        std::size_t size = defNode->get_num_children();
        for(std::size_t i = 0; i < size; ++i) {
            defNode->remove_child(i);
        }
    }

    return false;
  }

}

// (quote <datum>)
template <typename T>
bool quote_procedure(InputStream& in,NodePtr root, T& interm) {
  std::stack<shaka::Token> tokens;
  NodePtr defNode;

  // '
  try {
    // Check if it starts with a open parenthesis
    if(in.peek().type != shaka::Token::Type::PAREN_START)
        throw std::runtime_error("No open parenthesis");

    tokens.push(in.get());
    interm += tokens.top().get_string();

    if(root != nullptr)
        defNode = root->push_child(shaka::Data{shaka::MetaTag::LIST});

    // Open parenthesis must be followed by 'quote'
    if(in.peek().type != shaka::Token::Type::IDENTIFIER &&
       in.peek().get_string() != "quote")
        throw std::runtime_error("No quote keyword");

    tokens.push(in.get());
    interm += tokens.top().get_string();

    while (true)
    {
      if (in.peek().type == shaka::Token::Type::PAREN_END) {
        tokens.push(in.get());
        interm += tokens.top().get_string();
        break;
      }
      else if (in.peek().type == shaka::Token::Type::NUMBER) {
        tokens.push(in.get());
        interm += tokens.top().get_string();
        if(defNode != nullptr) {
          defNode->push_child(shaka::Number(std::stod(tokens.top().get_string())));
        }
      }
      else if (in.peek().type == shaka::Token::Type::IDENTIFIER || in.peek().type == shaka::Token::Type::CHARACTER ||
               in.peek().type ==  shaka::Token::Type::STRING  || in.peek().type == shaka::Token::Type::BOOLEAN_TRUE ||
               in.peek().type == shaka::Token::Type::BOOLEAN_FALSE) {
        tokens.push(in.get());
        interm += tokens.top().get_string();
        if(defNode != nullptr) {
            defNode->push_child(shaka::Symbol(tokens.top().get_string()));
        }
      }
      else
          throw std::runtime_error("BRUH WTF");
    }

    return true;
  }
  catch (std::runtime_error& e) {
    while(!tokens.empty()) {
        in.unget(tokens.top());
        tokens.pop();
    }

    // delete defNode and children
    if(defNode != nullptr) {

        std::size_t size = defNode->get_num_children();
        for(std::size_t i = 0; i < size; ++i) {
            defNode->remove_child(i);
        }
    }

    return false;
  }
}
} // end rule
} // end parser
} // end shaka

#endif
