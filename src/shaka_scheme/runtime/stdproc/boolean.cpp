//
// Created by Herman on 2/28/2018.
//

#include "shaka_scheme/runtime/stdproc/boolean.hpp"

namespace shaka {
namespace stdproc {
namespace impl {

Args not_boolean(Args args) {
  if (args.size() > 1) {
    throw InvalidInputException(1, "not: Too many arguments: +");
  }
  Args result;
  if (args[0]->get_type() == Data::Type::BOOLEAN) {
    return {create_node(shaka::Boolean(
        !args[0]->get<shaka::Boolean>().get_value()
    ))};
  } else {
    return {create_node(shaka::Data(shaka::Boolean(false)))};
  }
}

Args check_boolean(Args args) {
  if (args.size() > 1) {
    throw InvalidInputException(1, "boolean?: Too many arguments: +");
  }
  Args result;
  if (args[0]->get_type() == Data::Type::BOOLEAN) {
    result.push_back(create_node(shaka::Boolean(true)));
  } else {
    result.push_back(create_node(shaka::Boolean(false)));
  }
  return result;
}

Args alltf(Args args) {
  Args result;

  for (unsigned int i = 0; i < args.size(); ++i) {
    if (args[0]->get_type() != Data::Type::BOOLEAN) {
      throw InvalidInputException(1, "boolean=?: Argument contains "
          "non-boolean: +");
    }
  }

  shaka::Boolean type = args[0]->get<shaka::Boolean>();

  for (unsigned int i = 1; i < args.size(); ++i) {
    if (type != args[i]->get<shaka::Boolean>()) {
      result.push_back(create_node(shaka::Boolean(false)));
      return result;
    }
  }
  result.push_back(create_node(shaka::Boolean(true)));
  return result;
}

} //namespace impl
} //namespace stdproc
} //namespace shaka



