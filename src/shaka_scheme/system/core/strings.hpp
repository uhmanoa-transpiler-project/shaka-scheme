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
inline NodePtr make_string(int size) {
    std::string s;
    for(std::size_t i = 0; i < size; i++)
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
inline NodePtr make_string(int size, char c) {
    std::string s;
    for(std::size_t i = 0; i < size; i++){
        s.push_back(c);
    }

    String str(s);
    NodePtr result = create_node(str);
    return result;
}

/**
 * @brief Implements (string char ...)
 * @param args list of chars to be added to the string
 * @return the newly allocated string composed of the args
 */
inline NodePtr string_list(std::deque<char> args) {
    std::string s;
    for (std::size_t i = 0; i < args.size(); i++){
        s.push_back(args[i]);
    }

    String str(s);
    NodePtr result = create_node(str);
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
