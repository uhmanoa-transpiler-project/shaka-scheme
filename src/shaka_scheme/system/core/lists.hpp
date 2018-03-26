//
// Created by aytas on 9/12/2017.
//

#ifndef SHAKA_SCHEME_CORE_LISTS_HPP
#define SHAKA_SCHEME_CORE_LISTS_HPP

#include <shaka_scheme/system/base/Data.hpp>
#include <shaka_scheme/system/base/DataPair.hpp>

#include <shaka_scheme/system/core/types.hpp>

namespace shaka {
namespace core {

NodePtr cons(NodePtr left, NodePtr right);

NodePtr car(NodePtr node);

NodePtr cdr(NodePtr node);

void set_car(NodePtr pair, NodePtr obj);

void set_cdr(NodePtr pair, NodePtr obj);

NodePtr list();

template <typename... Args>
NodePtr list(NodePtr first, Args... rest) {
  return shaka::core::cons(first, shaka::core::list(rest...));
}

/**
 * @brief Determines whether a node is a pair.
 * @param node The node to examine.
 * @return true if object is a pair, false if otherwise.
 */
bool is_pair(NodePtr node);

bool is_null_list(NodePtr node);

bool is_proper_list(NodePtr node);

bool is_improper_list(NodePtr node);

std::size_t length(NodePtr node);

NodePtr append();

NodePtr append(NodePtr first);

NodePtr append(NodePtr first, NodePtr second);

template <typename... Args>
NodePtr append(NodePtr first, NodePtr second, Args... rest) {
  auto node = append(first, second);
  return append(node, rest...);
}

NodePtr reverse_helper(const NodePtr left, const NodePtr right);

NodePtr reverse(NodePtr first);

} // namespace core
} // namespace shaka


#endif //SHAKA_SCHEME_LISTS_HPP
