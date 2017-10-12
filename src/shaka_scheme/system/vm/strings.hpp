//
// Created by Billy Wooton on 10/11/17.
//

#ifndef SHAKA_SCHEME_STRINGS_HPP
#define SHAKA_SCHEME_STRINGS_HPP

#include "shaka_scheme/system/base/String.hpp"
#include "shaka_scheme/system/base/Data.hpp"
#include <functional>
#include <vector>
#include <string>

namespace shaka {

using Callable = std::function<std::vector<NodePtr>(std::vector<NodePtr>)>;

std::vector<NodePtr> str_length(std::vector<NodePtr> args) {
  if (args[0]->get_type() != Data::Type::STRING) {
    throw TypeException(10001, "Incompatible argument type to NativeClosure");
  }

  std::vector<NodePtr> results;

  results[0] = args[0]->get<String>()->length();
  return results;
}

Callable string_length = str_length;

}
#endif //SHAKA_SCHEME_STRINGS_HPP
