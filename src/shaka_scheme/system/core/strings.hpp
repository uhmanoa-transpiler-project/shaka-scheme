//
// Created by Billy Wooton on 10/11/17.
// Edited by Jared Shimabukuro on 11/28-29/17
//

#ifndef SHAKA_SCHEME_STRINGS_HPP
#define SHAKA_SCHEME_STRINGS_HPP

#include "shaka_scheme/system/base/String.hpp"
#include "shaka_scheme/system/base/Data.hpp"
#include <functional>
#include <vector>
#include <string>

namespace shaka {

using Callable = std::function<std::deque<NodePtr>(std::deque<NodePtr>)>;

namespace core {

/**
 * @brief Implements (make-string k)
 * @param size the size of the string
 * @return the newly allocated string of length k
 */
inline NodePtr make_string(NodePtr size) {
    int sz = std::stoi(size->get<String>().get_string());
    std::string s;
    for(std::size_t i = 0; i < sz; i++)
        s.push_back(' ');

    String str(s);
    NodePtr result = create_node(str);
    return result;
}

/**
 * @brief Implements (make-string k char)
 * @param size The size of the string
 * @param c The Initialized characters of the string
 * @return the newly allocated string of length k
 */
inline NodePtr make_string(NodePtr size, NodePtr c) {
    int sz = std::stoi(size->get<String>().get_string());
    char ch = c->get<String>().get_string()[0];

    std::string s;
    for(std::size_t i = 0; i < sz; i++){
        s.push_back(ch);
    }

    String str(s);
    NodePtr result = create_node(str);
    return result;
}

/**
 * @brief Implements (string char ...)
 * @param nodes list of chars to be added to the string
 * @return the newly allocated string composed of the args
 */
inline NodePtr string_char_list(std::deque<NodePtr> nodes) {
    String str("");
    for (std::size_t i = 0; i < nodes.size(); i++){
        str.append(nodes[i]->get<String>());
    }

    NodePtr result = create_node(str);
    return result;
}

inline NodePtr string_length(NodePtr node) {
    if(node->get_type() != Data::Type::STRING) {
        throw TypeException(10001, "Incompatible argument type to NativeClosure");
    }

    String str(node->get<String>());
    int l = str.get_string().size();
    String len(l);

    NodePtr result = create_node(len);
    return result;
}

std::deque<NodePtr> str_append(std::deque<NodePtr> args) {
  if (args[0]->get_type() != Data::Type::STRING) {
    throw TypeException(10001, "Incompatible argument type to NativeClosure");
  }

  String result("");

  for (std::size_t i = 0; i < args.size(); i++) {
    result.append(args[i]->get<String>());
  }

  std::deque<NodePtr> results = {create_node(result)};
  return results;
}

}

Callable string_append = core::str_append;

}
#endif //SHAKA_SCHEME_STRINGS_HPP
