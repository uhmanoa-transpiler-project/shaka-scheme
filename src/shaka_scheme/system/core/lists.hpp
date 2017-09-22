//
// Created by aytas on 9/12/2017.
//

#ifndef SHAKA_SCHEME_LISTS_HPP
#define SHAKA_SCHEME_LISTS_HPP

#include <shaka_scheme/system/base/Data.hpp>
#include <shaka_scheme/system/base/DataPair.hpp>

#include <shaka_scheme/system/core/types.hpp>

namespace shaka {
namespace core {

NodePtr cons(NodePtr left, NodePtr right) {
  return create_node(Data(DataPair(left, right)));
}

NodePtr car(NodePtr node) {
  if (node->get_type() != Data::Type::DATA_PAIR) {
    throw shaka::TypeException(10001, "car(): Data does not hold DataPair");
  }
  return node->get<DataPair>().car();
}

NodePtr cdr(NodePtr node) {
  if (node->get_type() != Data::Type::DATA_PAIR) {
    throw shaka::TypeException(10001, "car(): Data does not hold DataPair");
  }
  return node->get<DataPair>().cdr();
}

void set_car(NodePtr pair, NodePtr obj) {
  if (pair->get_type() != Data::Type::DATA_PAIR) {
    throw shaka::TypeException(10001, "set_car(): Data does not hold DataPair");
  }
  pair->get<DataPair>().set_car(obj);
}

void set_cdr(NodePtr pair, NodePtr obj) {
  if (pair->get_type() != Data::Type::DATA_PAIR) {
    throw shaka::TypeException(10001, "set_cdr(): Data does not hold DataPair");
  }
  pair->get<DataPair>().set_cdr(obj);
}

NodePtr list() {
  return create_node(Data());
}

template <typename... Args>
NodePtr list(NodePtr first, Args... rest) {
  return shaka::core::cons(first, shaka::core::list(rest...));
}

/**
 * @brief Determines whether a node is a pair.
 * @param node The node to examine.
 * @return true if object is a pair, false if otherwise.
 */
bool is_pair(NodePtr node) {
  return node->get_type() == Data::Type::DATA_PAIR;
}


bool is_null_list(NodePtr node) {
  return node->get_type() == Data::Type::NULL_LIST;
}

bool is_proper_list(NodePtr node) {
  // Lists must be pairs.
  if (!is_pair(node)) { return false; }
  // Get the last cdr of the last pair in the
  // nested structure of pairs within pairs (the list)
  auto it = node;
  while (is_pair(it)) {
    it = cdr(it);
  }
  // If the last item is a null list, it is proper list.
  return is_null_list(it);
}

bool is_improper_list(NodePtr node) {
  // Lists must be pairs.
  if (!is_pair(node)) { return false; }
  // Get the last cdr of the last pair in the
  // nested structure of pairs within pairs (the list)
  auto it = node;
  while (is_pair(it)) {
    it = cdr(it);
  }
  // If the last item is not null list, it is not a proper list.
  return !is_null_list(it);
}

std::size_t length(NodePtr node) {
  if (node->get_type() == shaka::Data::Type::NULL_LIST) {
    return 0;
  }
  else if (node->get_type() != shaka::Data::Type::DATA_PAIR) {
    throw shaka::TypeException(1000, "length(): data is not a pair");
  }
  int count = 0;
  auto it = node;
  for (; core::is_pair(it); it = core::cdr(it)) {
    ++count;
  }
  if (it->get_type() != shaka::Data::Type::NULL_LIST) {
    throw shaka::TypeException(1001, "length(): data is not a proper list");
  }
  return count;
}

} // namespace core
} // namespace shaka


#endif //SHAKA_SCHEME_LISTS_HPP
