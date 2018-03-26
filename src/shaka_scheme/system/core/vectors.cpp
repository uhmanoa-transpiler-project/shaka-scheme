#include "shaka_scheme/system/core/vectors.hpp"

namespace shaka {
namespace core {

/**
 * @brief Converts a proper list into a vector.
 * @param list A proper list, terminated with a null list
 * @return A vector containing the same elements as the original list
 */
NodePtr list_to_vector(NodePtr list) {
  // Find the length of the list.
  std::size_t length = core::length(list);
  shaka::Vector vector(length);
  // Copy the elements from the list over.
  for (std::size_t i = 0; i < length; ++i) {
    shaka::DataPair& pair = list->get<shaka::DataPair>();
    vector[i] = pair.car();
    list = pair.cdr();
  }
  // Move the vector into the node to return.
  return create_node(std::move(vector));
}

/**
 * @brief Converts a vector into a proper list.
 * @param vector A vector of fixed size.
 * @return A proper list containing the same elements as the original list
 */
NodePtr vector_to_list(NodePtr vector) {
  // Create a null list.
  shaka::NodePtr node = create_node(shaka::Data());
  // Get the actual vector.
  shaka::Vector& vec = vector->get<shaka::Vector>();
  // For each item in the vector, starting from the back, cons it onto the
  // null list.
  for (std::size_t i = vec.length(); i > 0; --i) {
    node = core::cons(create_node(*vec[i-1]), node);
  }
  return node;
}

} // namespace core
} // namespace shaka

