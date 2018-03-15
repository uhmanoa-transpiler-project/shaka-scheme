//
// Created by Sean Takafuji on 2/23/2018.
//

#ifndef SHAKA_SCHEME_STDPROC_EQUIVALENCE_PREDICATES_HPP
#define SHAKA_SCHEME_STDPROC_EQUIVALENCE_PREDICATES_HPP

#include "shaka_scheme/system/base/Number.hpp"
#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/exceptions/TypeException.hpp"

#include <cmath>
#include <functional>
#include <typeinfo>
#include <deque>



namespace shaka {
namespace stdproc {

using Args = std::deque<NodePtr>;
using Callable = std::function<std::deque<NodePtr>(std::deque<NodePtr>)>;

namespace impl {

Args is_eqv(Args);
Args is_eq(Args);
Args is_equal(Args);

} // namespace impl

Callable eqv = impl::is_eqv;
Callable eq = impl::is_eq;
Callable equal = impl::is_equal;

} // namespace stdproc
} // namespace shaka

#endif // SHAKA_SCHEME_STDPROC_EQUIVALENCE_PREDICATES_HPP


