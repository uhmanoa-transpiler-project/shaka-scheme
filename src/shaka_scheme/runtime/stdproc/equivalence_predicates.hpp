//
// Created by Sean Takafuji on 2/23/2018.
//

#ifndef SHAKA_SCHEME_STDPROC_EQUIVALENCE_PREDICATES_HPP
#define SHAKA_SCHEME_STDPROC_EQUIVALENCE_PREDICATES_HPP

#include "shaka_scheme/system/base/Number.hpp"
#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/exceptions/TypeException.hpp"
#include "shaka_scheme/system/exceptions/InvalidInputException.hpp"
//#include "shaka_scheme/system/base/"

#include <cmath>
#include <functional>
#include <typeinfo>
#include <deque>



namespace shaka {
namespace stdproc {

using Args = std::deque<NodePtr>;
using Callable = std::function<std::deque<NodePtr>(std::deque<NodePtr>)>;

namespace impl {

/**
 * @brief Implementation of eqv? an Equivalence Predicate
 * @param args List of arguments from a Shaka Scheme function call to eqv?
 * @return Returns if the two datas are equivalent to each other (will return
 * false on lists)
 */
Args is_eqv(Args args);

/**
 * @brief Implementation of eq? an Equivalence Predicate
 * @param args List of arguments from a Shaka Scheme function call to eq?
 * @return Returns if the two datas are equivalent to each other (follows the
 * same standard as eqv in this implementation)
 */
Args is_eq(Args args);

/**
 * @brief Implementation of equal an Equivalence Predicate
 * @param args List of arguments from a Shaka Scheme function call to equal?
 * @return Returns if the two items passed are equivalent to each other. Will
 * recursively compare two lists together for equivalence
 */
Args is_equal(Args args);

} // namespace impl


extern Callable eqv;
extern Callable eq;
extern Callable equal;

} // namespace stdproc
} // namespace shaka

#endif // SHAKA_SCHEME_STDPROC_EQUIVALENCE_PREDICATES_HPP


