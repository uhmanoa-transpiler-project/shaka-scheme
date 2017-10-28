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

namespace core {

std::vector<NodePtr> str_append(std::vector<NodePtr> args) {
  if (args[0]->get_type() != Data::Type::STRING) {
    throw TypeException(10001, "Incompatible argument type to NativeClosure");
  }

  String result("");

  for (int i = args.size() - 1; i >= 0; i--) {
    result.append(args[i]->get<String>());
  }

  std::vector<NodePtr> results = {create_node(result)};
  return results;
}

}

Callable string_append = core::str_append;

}
#endif //SHAKA_SCHEME_STRINGS_HPP
