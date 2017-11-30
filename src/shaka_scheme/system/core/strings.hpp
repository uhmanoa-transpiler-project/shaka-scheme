//
// Created by Billy Wooton on 10/11/17.
// Edited by Jared Shimabukuro on 11/28-29/17
//

#ifndef SHAKA_SCHEME_STRINGS_HPP
#define SHAKA_SCHEME_STRINGS_HPP

#include "shaka_scheme/system/base/String.hpp"
#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/core/lists.hpp"
#include <functional>
#include <vector>
#include <string>

namespace shaka {

using Callable = std::function<std::deque<NodePtr>(std::deque<NodePtr>)>;
using NodeCall = std::function<NodePtr(NodePtr)>;
using DblNodeCall = std::function<NodePtr(NodePtr, NodePtr)>;
using DequeCall = std::function<NodePtr(std::deque<NodePtr>)>;

namespace core {

/**
 * @brief Implements (make-string k)
 * @param size the size of the string
 * @return the newly allocated string of length k
 */
NodePtr make_str_blank(NodePtr size) {
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
NodePtr make_str(NodePtr size, NodePtr c) {
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
NodePtr ch_str(std::deque<NodePtr> nodes) {
    String str("");
    for (std::size_t i = 0; i < nodes.size(); i++){
        str.append(nodes[i]->get<String>());
    }

    NodePtr result = create_node(str);
    return result;
}

/**
 * @brief Implements (string-length string)
 * @param node The string being measured
 * @return The number of characters in the given string
 */
NodePtr str_length(NodePtr node) {
    if(node->get_type() != Data::Type::STRING) {
        throw TypeException(10001, "Incompatible argument type to NativeClosure");
    }

    String str(node->get<String>());
    std::string l = std::to_string(str.get_string().size());
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

/**
 * @brief Implements (list->string list)
 * @param lst The list that will be converted into a string
 * @return The string containing the list elements
 */
inline NodePtr list_to_str(NodePtr lst) {
    std::string s;
    while(!(is_null_list(lst))) {
        switch (car(lst)->get_type()) {
            case Data::Type::STRING:
                s.append(car(lst)->get<String>().get_string());
                break;
            case Data::Type::SYMBOL:
                s.append(car(lst)->get<Symbol>().get_value());
                break;
            default:
                break;
        }

        lst = cdr(lst);
    }

    NodePtr result = create_node(Data(String(s)));
}

}

NodeCall make_string_blank = core::make_str_blank;
DblNodeCall make_string = core::make_str;
DequeCall char_string = core::ch_str;
NodeCall string_length = core::str_length;
Callable string_append = core::str_append;
NodeCall list_to_string = core::list_to_str;

}
#endif //SHAKA_SCHEME_STRINGS_HPP
