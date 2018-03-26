#ifndef SHAKA_SCHEME_CORE_TYPES_HPP
#define SHAKA_SCHEME_CORE_TYPES_HPP

#include "shaka_scheme/system/base/Data.hpp"

namespace shaka {
namespace core {

/**
 * @brief Implements (boolean?).
 * @param node The data to take in
 * @return A boolean of whether the predicate was satisfied.
 */
bool is_boolean(NodePtr node);

/**
 * @brief Implements (symbol?).
 * @param node The data to take in
 * @return A boolean of whether the predicate was satisfied.
 */
bool is_symbol(NodePtr node);

/**
 * @brief Implements (string?).
 * @param node The data to take in
 * @return A boolean of whether the predicate was satisfied.
 */
bool is_string(NodePtr node);

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
bool is_unspecified(NodePtr node);

/**
 * @brief A helper function to create a Data value with an unspecified value.
 * @return A Data with its type set to UNSPECIFIED.
 *
 * @implementation_specific
 */
NodePtr create_unspecified_node();

/**
 * @brief Implements (eqv), the literal/memory-equivalence comparison operator.
 * @param left The left object
 * @param right The right object
 * @return A boolean denoting the equivalence predicate
 */
bool is_eqv(NodePtr left, NodePtr right);

} // namespace core
} // namespace shaka

#endif //SHAKA_SCHEME_TYPES_HPP
