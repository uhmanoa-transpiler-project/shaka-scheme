#include "shaka_scheme/system/core/lists.hpp"

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
    throw shaka::TypeException(10001, "cdr(): Data does not hold DataPair");
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
  // The empty list is a proper list
  if (is_null_list(node)) { return true; }
  // Lists must be pairs if they are not the null list.
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

NodePtr append() {
  return list();
}

NodePtr append(NodePtr first) {
  return first;
}

NodePtr append(NodePtr first, NodePtr second) {
  // The first argument must be a proper list.
  if (!is_proper_list(first)) {
    throw shaka::TypeException(2002, "append(): first argument is not a "
        "proper list");
  }
  // Return the second argument if the first argument is a null list.
  if (is_null_list(first)) { return second; }

  // Otherwise, cons everything from first with the second after it.
  // First, create the root node as a list with just the first item of first.
  NodePtr root = cons(car(first), create_node(Data()));
  NodePtr list_it = root;
  // Get the NodePtr iterator for the cdr of the first list.
  NodePtr it = cdr(first);
  // While it is still a pair
  while (it->get_type() == shaka::Data::Type::DATA_PAIR) {
    // Append the next pair onto the list.
    set_cdr(list_it, cons(car(it), create_node(Data())));
    list_it = cdr(list_it);
    // Iterate.
    it = cdr(it);
  }

  // If second is not a pair, set cdr of the list to be second.
  if (!is_pair(second)) {
    set_cdr(list_it, second);
    return root;
  }

  // Otherwise, we need to iterate through second like first.
  it = second;
  set_cdr(list_it, cons(car(second), create_node(Data())));

  // While it is still a pair
  while (it->get_type() == shaka::Data::Type::DATA_PAIR) {
    // Append the next pair onto the list.
    set_cdr(list_it, cons(car(it), create_node(Data())));
    list_it = cdr(list_it);
    // Iterate.
    if (!is_pair(it)) { break; }
    it = cdr(it);
  }

  // If the last item is a not a null list, append it.
  if (!is_null_list(it)) {
    set_cdr(list_it, it);
  }
  return root;
}

NodePtr reverse_helper(const NodePtr left, const NodePtr right) {
  return core::cons(right, left);
}

NodePtr reverse(NodePtr first) {
  if (first->get_type() != shaka::Data::Type::DATA_PAIR) {
    return create_node(*first);
  }
  if (core::is_null_list(core::cdr(first)))  {
    return core::list(core::car(first));
  } else {
    return shaka::core::reverse_helper(core::car(first), reverse(core::cdr(first)));
  }
}


} // namespace core
} // namespace shaka
