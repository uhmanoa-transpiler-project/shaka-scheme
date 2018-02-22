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
Args not_boolean(Args args){
  if (args.size() > 1) {
    throw InvalidInputException(1, "not: Too many arguments: +");
  }
  Args result;
  if (args[0]->get_type() == Data::Type::BOOLEAN) {
    if (args[0]->get<shaka::Boolean>() == false) {
      result.push_back(create_node(shaka::Boolean(true)));
    } else {
      result.push_back(create_node(shaka::Boolean(false)));
    }
  } else {
    result.push_back(create_node(shaka::Boolean(false)));
  }
  return result;
}

}

Callable notbool = impl::not_boolean;

} //namespace stdproc
} //namespace shaka

#endif //SHAKA_SCHEME_STDPROC_BOOLEAN_HPP
