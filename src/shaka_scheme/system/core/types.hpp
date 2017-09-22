//
// Created by aytas on 9/21/2017.
//

#ifndef SHAKA_SCHEME_TYPES_HPP
#define SHAKA_SCHEME_TYPES_HPP

#include "shaka_scheme/system/base/Data.hpp"

namespace shaka {
namespace core {

bool is_boolean(NodePtr node) {
  return node->get_type() == Data::Type::BOOLEAN;
}

bool is_symbol(NodePtr node) {
  return node->get_type() == Data::Type::SYMBOL;
}

bool is_string(NodePtr node) {
  return node->get_type() == Data::Type::STRING;
}

bool is_unspecified(NodePtr node) {
  return node->get_type() == Data::Type::UNSPECIFIED;
}

} // namespace core
} // namespace shaka

#endif //SHAKA_SCHEME_TYPES_HPP
