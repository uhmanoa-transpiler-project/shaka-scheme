#ifndef SHAKA_SCHEME_VECTORS_HPP
#define SHAKA_SCHEME_VECTORS_HPP

#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/core/lists.hpp"

namespace shaka {
namespace core {

/**
 * @brief Converts a proper list into a vector.
 * @param list A proper list, terminated with a null list
 * @return A vector containing the same elements as the original list
 */
NodePtr list_to_vector(NodePtr list);

/**
 * @brief Converts a vector into a proper list.
 * @param vector A vector of fixed size.
 * @return A proper list containing the same elements as the original list
 */
NodePtr vector_to_list(NodePtr vector);

} // namespace core
} // namespace shaka

#endif //SHAKA_SCHEME_VECTORS_HPP
