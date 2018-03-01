//
// Created by Herman on 2/28/2018.
//

#include "shaka_scheme/runtime/stdproc/boolean.hpp"

namespace shaka {
namespace stdproc {
namespace impl {

/**
 * @brief Implemenataion of not function
 * @param args - List of data of various types
 * @return single shaka::Boolean with True or False
 */
Args not_boolean(Args args) {
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

/**
 * @brief Implements function to check if variable is a shaka::Boolean
 * @param args - List of data of various types
 * @return Single shaka::Boolean with True or False
 */
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

/**
 * @brief Checks if all are boolean and whether all true or all false.
 * @param args - List of arguments of different types
 * @return Single shaka::Boolean with True or False
 */
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



