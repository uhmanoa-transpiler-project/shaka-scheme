//
// Created by Herman on 2/15/2018.
//

#ifndef SHAKA_SCHEME_STDPROC_BOOLEAN_HPP
#define SHAKA_SCHEME_STDPROC_BOOLEAN_HPP

#include "shaka_scheme/system/base/Number.hpp"
#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/exceptions/InvalidInputException.hpp"

namespace shaka{
namespace stdproc{

using Args = std::deque<NodePtr>;
using Callable = std::function<std::deque<NodePtr>(std::deque<NodePtr>)>;

namespace impl{

Args not_boolean(Args);

Args check_boolean(Args);

Args alltf(Args);

}

Callable notbool = impl::not_boolean;
Callable checkbool = impl::check_boolean;
Callable alltf = impl::alltf;

} //namespace stdproc
} //namespace shaka

#endif //SHAKA_SCHEME_STDPROC_BOOLEAN_HPP
