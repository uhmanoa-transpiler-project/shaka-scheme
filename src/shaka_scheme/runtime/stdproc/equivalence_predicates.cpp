//
// Created by Sean Takafuji on 2/23/2018.
//

#ifndef SHAKA_SCHEME_STDPROC_EQUIVALENCE_PREDICATES_HPP
#define SHAKA_SCHEME_STDPROC_EQUIVALENCE_PREDICATES_HPP
#endif

#include "shaka_scheme/system/base/Number.hpp"
#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/exceptions/TypeException.hpp"
#include "shaka_scheme/system/base/"

#include <cmath>
#include <functional>
#include <typeinfo>
#include <deque>

using Args = std::deque<NodePtr>;

Args is_eqv(Args args) {
  if (args.size() != 2) {
    throw InvalidInputException(1,
    "eqv?: Invalid number of arguments for procedure");
  }

  NodePtr result_value;

  auto result = args[0]->get_type() == args[0]->get_type();
  if (args[0]->ge)
  if (args[0]->get_type() != args[1]->get_type()) {
    return { create_node(shaka::Data(shaka::Boolean(false))) };
  }
}