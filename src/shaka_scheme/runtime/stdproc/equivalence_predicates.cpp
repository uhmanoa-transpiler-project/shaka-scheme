//
// Created by Sean Takafuji on 2/23/2018.
//

#include "shaka_scheme/runtime/stdproc/equivalence_predicates.hpp"
#include "shaka_scheme/system/core/lists.hpp"

namespace shaka {
namespace stdproc {
namespace impl {

Args is_eqv(Args args) {
  if (args.size() != 2) {
    throw InvalidInputException(
        1,
        "eqv?: Invalid number of arguments for procedure");
  }

  auto left_type = args[0]->get_type();
  auto right_type = args[1]->get_type();

  // If the Base Data types aren't equivalent, return false;
  if (left_type != right_type) {
    return {create_node(shaka::Data(shaka::Boolean(false)))};
  }
  auto result = false;

  // Data Type: Primitive Form
  if (left_type == Data::Type::PRIMITIVE_FORM) {
    result = args[0].get() == args[1].get();
  }
  // Data Type: Closure
  if (left_type == Data::Type::CLOSURE) {
    result = args[0].get() == args[1].get();
  }
  // Data Type: Data Pair
  else if (left_type == Data::Type::DATA_PAIR) {
    result = args[0].get() == args[1].get();
  }
  // Data Type: Boolean
  else if (left_type == Data::Type::BOOLEAN) {
    result = args[0]->get<Boolean>() == args[1]->get<Boolean>();
  }
    // Data Type: Symbol
  else if (left_type == Data::Type::SYMBOL) {
    result = args[0]->get<Symbol>() == args[1]->get<Symbol>();
  }
    // Data Type: Number
  else if (left_type == Data::Type::NUMBER) {
    // Check if the Number type is the same (Integer, Real, Rational)
    auto number_left_type = args[0]->get<Number>().get_type();
    auto number_right_type = args[1]->get<Number>().get_type();
    if (number_left_type != number_right_type) {
      return {create_node(shaka::Data(shaka::Boolean(result)))};
    }
    result = args[0]->get<Number>() == args[1]->get<Number>();
  }
    // Data Type: String
  else if (left_type == Data::Type::STRING) {
    result = args[0]->get<String>() == args[1]->get<String>();
  }


    // Data Type: Null List
  else if (left_type == Data::Type::NULL_LIST) {
    result = true;
  }

  return {create_node(shaka::Data(shaka::Boolean(result)))};
}

Args is_eq(Args args) {
  if (args.size() != 2) {
    throw InvalidInputException(
        1,
        "eq?: Invalid number of arguments for procedure");
  }

  auto left_type = args[0]->get_type();
  auto right_type = args[1]->get_type();

  // If the Base Data types aren't equivalent, return false;
  if (left_type != right_type) {
    return {create_node(shaka::Data(shaka::Boolean(false)))};
  }

  auto result = false;

  // Data Type: Primitive Form
  if (left_type == Data::Type::PRIMITIVE_FORM) {
    result = args[0].get() == args[1].get();
  }
  // Data Type: Closure
  else if (left_type == Data::Type::CLOSURE) {
    result = args[0].get() == args[1].get();
  }
  // Data Type: Data Pair
  else if (left_type == Data::Type::DATA_PAIR) {
    result = args[0].get() == args[1].get();
  }
  // Data Type: Boolean
  else if (left_type == Data::Type::BOOLEAN) {
    result = args[0]->get<Boolean>() == args[1]->get<Boolean>();
  }
    // Data Type: Symbol
  else if (left_type == Data::Type::SYMBOL) {
    result = args[0]->get<Symbol>() == args[1]->get<Symbol>();
  }
    // Data Type: Number
  else if (left_type == Data::Type::NUMBER) {
    // Check if the true Number type is the same (Integer, Real, Rational)
    auto number_left_type = args[0]->get<Number>().get_type();
    auto number_right_type = args[1]->get<Number>().get_type();
    if (number_left_type != number_right_type) {
      return {create_node(shaka::Data(shaka::Boolean(result)))};
    }
    result = args[0]->get<Number>() == args[1]->get<Number>();
  }
    // Data Type: String
  else if (left_type == Data::Type::STRING) {
    result = args[0]->get<String>() == args[1]->get<String>();
  }
    // Data Type: Null List
  else if (left_type == Data::Type::NULL_LIST) {
    result = true;
  }

  return {create_node(shaka::Data(shaka::Boolean(result)))};
}

Args is_equal(Args args) {
  if (args.size() != 2) {
    throw InvalidInputException(
        1,
        "equal?: Invalid number of arguments for procedure");
  }

  auto left_type = args[0]->get_type();
  auto right_type = args[1]->get_type();

  // If the Base Data types aren't equivalent, return false;
  if (left_type != right_type) {
    return {create_node(shaka::Data(shaka::Boolean(false)))};
  }

  auto result = false;

  // Data Type: Primitive Form
  if (left_type == Data::Type::PRIMITIVE_FORM) {
    result = args[0].get() == args[1].get();
  }
  // Data Type: Closure
  else if (left_type == Data::Type::CLOSURE) {
    result = args[0].get() == args[1].get();
  }
  // Data Type: List
  else if (left_type == Data::Type::DATA_PAIR) {
    // Make a list with the head of each pair
    Args car_args = {
        create_node(shaka::Data(*core::car(args[0]))),
        create_node(shaka::Data(*core::car(args[1]))),
    };


    // Create a permanently false list to evaluate against
    Args false_boolean = {
        create_node(shaka::Data(shaka::Boolean(false)
        ))};

    // Check the Head of the Data Pair. If not equivalent, end the recursive
    // evaluation
    if (is_equal(car_args)[0]->get<Boolean>() ==
        false_boolean[0]->get<Boolean>()) {
      return {create_node(shaka::Data(shaka::Boolean(false)))};
    }

    Args cdr_args = {
        create_node(shaka::Data(*core::cdr(args[0]))),
        create_node(shaka::Data(*core::cdr(args[1]))),
    };
    return is_equal(cdr_args);
  }
    // Data Type: Boolean
  else if (left_type == Data::Type::BOOLEAN) {
    result = args[0]->get<Boolean>() == args[1]->get<Boolean>();
  }
    // Data Type: Symbol
  else if (left_type == Data::Type::SYMBOL) {
    result = args[0]->get<Symbol>() == args[1]->get<Symbol>();
  }
    // Data Type: Number
  else if (left_type == Data::Type::NUMBER) {
    // Check if the true Number type is the same (Integer, Real, Rational)
    auto number_left_type = args[0]->get<Number>().get_type();
    auto number_right_type = args[1]->get<Number>().get_type();
    if (number_left_type != number_right_type) {
      return {create_node(shaka::Data(shaka::Boolean(result)))};
    }
    result = args[0]->get<Number>() == args[1]->get<Number>();
  }
    // Data Type: String
  else if (left_type == Data::Type::STRING) {
    result = args[0]->get<String>() == args[1]->get<String>();
  }
    // Data Type: Null List
  else if (left_type == Data::Type::NULL_LIST) {
    result = true;
  }

  return {create_node(shaka::Data(shaka::Boolean(result)))};
}

} // namespace impl

Callable eqv = impl::is_eqv;
Callable eq = impl::is_eq;
Callable equal = impl::is_equal;

} // namespace stdproc
} // namespace shaka

