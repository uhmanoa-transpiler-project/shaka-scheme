//
// Created by aytas on 9/21/2017.
//

#ifndef SHAKA_SCHEME_TYPES_HPP
#define SHAKA_SCHEME_TYPES_HPP

#include "shaka_scheme/system/base/Data.hpp"

namespace shaka {
namespace core {

/**
 * @brief Implements (boolean?).
 * @param node The data to take in
 * @return A boolean of whether the predicate was satisfied.
 */
bool is_boolean(NodePtr node) {
  return node->get_type() == Data::Type::BOOLEAN;
}

/**
 * @brief Implements (symbol?).
 * @param node The data to take in
 * @return A boolean of whether the predicate was satisfied.
 */
bool is_symbol(NodePtr node) {
  return node->get_type() == Data::Type::SYMBOL;
}

/**
 * @brief Implements (string?).
 * @param node The data to take in
 * @return A boolean of whether the predicate was satisfied.
 */
bool is_string(NodePtr node) {
  return node->get_type() == Data::Type::STRING;
}

/**
 * @brief Checks to see whether a value is the "unspecified" value.
 * @param node The data to take in
 * @return A boolean of whether the predicate was satisfied.
 *
 * @note Certain procedures in Scheme (e.g. the return value of an (if then
 * else) where the else parameter is not provided, the return value of (set!))
 * return an unspecified value.
 *
 * @implementation_specific "Unspecified" is a first-class value in our type
 * system. Here, we provide this function to act as the type predicate for the
 * "unspecified" value.
 */
bool is_unspecified(NodePtr node) {
  return node->get_type() == Data::Type::UNSPECIFIED;
}

/**
 * @brief A helper function to create a Data value with an unspecified value.
 * @return A Data with its type set to UNSPECIFIED.
 *
 * @implementation_specific
 */
NodePtr create_unspecified_node() {
  return shaka::create_unspecified();
}

/**
 * @brief Implements (eqv), the literal/memory-equivalence comparison operator.
 * @param left The left object
 * @param right The right object
 * @return A boolean denoting the equivalence predicate
 */
bool is_eqv(NodePtr left, NodePtr right) {
  auto left_type = left->get_type();
  auto right_type = right->get_type();
  if (left_type != right_type) {
    return false;
  }
  if (left_type == Data::Type::SYMBOL) {
    return left->get<Symbol>() == right->get<Symbol>();
  }
  else if (left_type == Data::Type::BOOLEAN) {
    return left->get<Boolean>() == right->get<Boolean>();
  }
  else if (left_type == Data::Type::NULL_LIST) {
    return true;
  }
  else return left == right;
}

} // namespace core
} // namespace shaka

#endif //SHAKA_SCHEME_TYPES_HPP
