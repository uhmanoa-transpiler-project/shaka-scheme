//
// Created by Billy Wooton on 11/29/17.
//

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
// (+ z1 ...)
Args add_numbers(Args args) {

  if (args[0]->get_type() != Data::Type::NUMBER) {
    throw TypeException(117,
                        "STDPROC: Incorrect argument type to Native "
                             "Procedure: "
                          "+");
  }

  shaka::Number result = shaka::Number(0);
  for (std::size_t i = 0; i < args.size(); i++) {
    result = result + args[i]->get<shaka::Number>();
  }

  Args result_vector;
  NodePtr result_value = create_node(result);
  result_vector.push_back(result_value);

  return result_vector;
}


// (* z1 ...)
Args mul_numbers(Args args) {

  if (args[0]->get_type() != Data::Type::NUMBER) {
    throw TypeException(117,
                        "STDPROC: Incorrect argument type to Native "
                            "Procedure: "
                            "*");
  }

  shaka::Number result = shaka::Number(1);
  for (std::size_t i = 0; i < args.size(); i++) {
    result = result * shaka::get<shaka::Number>(args[i]->get_data());
  }

  Args result_vector;
  NodePtr result_value = std::make_shared<shaka::DataNode>(result);
  result_vector.push_back(result_value);

  return result_vector;
}


// (- z)
Args neg_numbers(Args args) {

  if (args[0]->get_type() != Data::Type::NUMBER) {
    throw TypeException(117,
                        "STDPROC: Incorrect argument type to Native "
                            "Procedure: "
                            "-");
  }
  shaka::Number result = shaka::Number(0);

  result = result - args[0]->get<shaka::Number>();

  Args result_vector;
  NodePtr result_value = create_node(Data(result));
  result_vector.push_back(result_value);

  return result_vector;

}


// (- z1 z2 ...)
Args sub_numbers(Args args) {

  if (args[0]->get_type() != Data::Type::NUMBER) {
    throw TypeException(117,
                        "STDPROC: Incorrect argument type to Native "
                            "Procedure: "
                            "-");
  }
  shaka::Number result = args[0]->get<shaka::Number>();

  if (args.size() == 1) {
    return neg_numbers(args);
  }

  for (std::size_t i = 1; i < args.size(); i++) {
    result = result - args[i]->get<shaka::Number>();
  }

  Args result_vector;
  NodePtr result_value = create_node(Data(result));
  result_vector.push_back(result_value);

  return result_vector;

}


// (/ z1)
Args reciprocal_numbers(Args args) {

  if (args[0]->get_type() != Data::Type::NUMBER) {
    throw TypeException(117,
                        "STDPROC: Incorrect argument type to Native "
                            "Procedure: "
                            "/");
  }
  shaka::Number result = shaka::Number(1);
  result = result / args[0]->get<shaka::Number>();
  Args result_vector;
  NodePtr result_value = create_node(Data(result));
  result_vector.push_back(result_value);

  return result_vector;

}


// (/ z1 z2 ...)
Args div_numbers(Args args) {

  if (args[0]->get_type() != Data::Type::NUMBER) {
    throw TypeException(117,
                        "STDPROC: Incorrect argument type to Native "
                            "Procedure: "
                            "/");
  }
  shaka::Number result = args[0]->get<shaka::Number>();

  for (std::size_t i = 1; i < args.size(); i++) {
    result = result / args[i]->get<shaka::Number>();
  }

  NodePtr result_value = create_node(Data(result));
  Args result_vector = {result_value};

  return result_vector;

}


// (abs x)
Args abs_numbers(Args args) {

  if (args[0]->get_type() != Data::Type::NUMBER) {
    throw TypeException(117,
                        "STDPROC: Incorrect argument type to Native "
                            "Procedure: "
                            "abs");
  }

  shaka::Number result = shaka::Number(0);

  shaka::Number input = args[0]->get<shaka::Number>();

  if (input < 0) {

    result = result - input;
  }

  else {
    result = input;
  }

  NodePtr result_value = create_node(Data(result));


  Args result_vector = {result_value};

  return result_vector;

}


// (floor/ n1 n2)
Args floor_div_numbers(Args args) {

  if (args[0]->get_type() != Data::Type::NUMBER) {
    throw TypeException(117,
                        "STDPROC: Incorrect argument type to Native "
                            "Procedure: "
                            "floor/");
  }

  shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
  shaka::Number n2 = shaka::get<shaka::Number>(args[1]->get_data());
  shaka::Number r;
  shaka::Number q;

  if (n1 > shaka::Number(0) && n2 > shaka::Number(0)) {

    r = n1 % n2;
    q = (n1 - r) / n2;
  }

  else if (n1 < shaka::Number(0) && n2 < shaka::Number(0)) {
    r = n1 % n2;
    q = (n1 - r) / n2;

  }
  else {
    r = n1 % n2 * shaka::Number(-1);
    q = (n1 - r) / n2;
  }

  NodePtr v1 = std::make_shared<shaka::DataNode>(q);
  NodePtr v2 = std::make_shared<shaka::DataNode>(r);

  Args result_vector = {v1, v2};

  return result_vector;

}


// (floor-quotient n1 n2)
Args floor_quotient_numbers(Args args) {

  if (args[0]->get_type() != Data::Type::NUMBER) {
    throw TypeException(117,
                        "STDPROC: Incorrect argument type to Native "
                            "Procedure: "
                            "floor-quotient");
  }

  shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
  shaka::Number n2 = shaka::get<shaka::Number>(args[1]->get_data());
  shaka::Number r;
  shaka::Number q;

  if (n1 > shaka::Number(0) && n2 > shaka::Number(0)) {

    r = n1 % n2;
    q = (n1 - r) / n2;
  }

  else if (n1 < shaka::Number(0) && n2 < shaka::Number(0)) {
    r = n1 % n2;
    q = (n1 - r) / n2;

  }
  else {
    r = n1 % n2 * shaka::Number(-1);
    q = (n1 - r) / n2;
  }

  NodePtr v1 = std::make_shared<shaka::DataNode>(q);

  Args result_vector = {v1};

  return result_vector;

}


// (floor-remainder n1 n2)
Args floor_remainder_numbers(Args args) {

  if (args[0]->get_type() != Data::Type::NUMBER) {
    throw TypeException(117,
                        "STDPROC: Incorrect argument type to Native "
                            "Procedure: "
                            "floor-remainder");
  }
  shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
  shaka::Number n2 = shaka::get<shaka::Number>(args[1]->get_data());
  shaka::Number r;

  if (n1 > shaka::Number(0) && n2 > shaka::Number(0)) {

    r = n1 % n2;
  }

  else if (n1 < shaka::Number(0) && n2 < shaka::Number(0)) {
    r = n1 % n2;

  }
  else {
    r = n1 % n2 * shaka::Number(-1);
  }

  NodePtr v1 = std::make_shared<shaka::DataNode>(r);

  Args result_vector = {v1};

  return result_vector;

}


// (truncate/ n1 n2)
Args truncate_div_numbers(Args args) {

  shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
  shaka::Number n2 = shaka::get<shaka::Number>(args[1]->get_data());

  shaka::Number r;
  shaka::Number q;


  r = n1 % n2;
  q = (n1 - r) / n2;

  NodePtr v1 = std::make_shared<shaka::DataNode>(q);
  NodePtr v2 = std::make_shared<shaka::DataNode>(r);

  Args result_vector = {v1, v2};

  return result_vector;


}

// (truncate-quotient n1 n2)
Args truncate_quotient_numbers(Args args) {

  shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
  shaka::Number n2 = shaka::get<shaka::Number>(args[1]->get_data());

  shaka::Number r = n1 % n2;
  shaka::Number q = (n1 - r) / n2;

  NodePtr v = std::make_shared<shaka::DataNode>(q);

  Args result_vector = {v};

  return result_vector;

}

// (truncate-remainder n1 n2)
Args truncate_remainder_numbers(Args args) {

  shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
  shaka::Number n2 = shaka::get<shaka::Number>(args[1]->get_data());

  shaka::Number r = n1 % n2;

  NodePtr v = std::make_shared<shaka::DataNode>(r);

  Args result_vector = {v};

  return result_vector;
}

// (quotient n1 n2)
Args quotient_numbers(Args args) {


  shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
  shaka::Number n2 = shaka::get<shaka::Number>(args[1]->get_data());

  shaka::Number r = n1 % n2;
  shaka::Number q = (n1 - r) / n2;

  NodePtr v = std::make_shared<shaka::DataNode>(q);

  Args result_vector = {v};

  return result_vector;

}

// (remainder n1 n2)
Args remainder_numbers(Args args) {

  shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
  shaka::Number n2 = shaka::get<shaka::Number>(args[1]->get_data());

  shaka::Number r = n1 % n2;

  NodePtr v = std::make_shared<shaka::DataNode>(r);

  Args result_vector = {v};

  return result_vector;
}

// (modulo n1 n2)
Args modulo_numbers(Args args) {


  shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
  shaka::Number n2 = shaka::get<shaka::Number>(args[1]->get_data());
  shaka::Number r;

  if (n1 > shaka::Number(0) && n2 > shaka::Number(0)) {

    r = n1 % n2;
  }
  else if (n1 < shaka::Number(0) && n2 < shaka::Number(0)) {
    r = n1 % n2;

  }
  else {
    r = n1 % n2 * shaka::Number(-1);
  }

  NodePtr v1 = std::make_shared<shaka::DataNode>(r);

  Args result_vector = {v1};

  return result_vector;
}

// (gcd n1 ...)
shaka::Number gcd_pair(shaka::Number n1, shaka::Number n2) {
  shaka::Number temp;
  while (n2 > shaka::Number(0)) {
    temp = n2;
    n2 = n1 % n2;
    n1 = temp;
  }
  return n1;
}

Args gcd_numbers(Args args, EnvPtr env) {


  shaka::Number result = shaka::get<shaka::Number>(args[0]->get_data());
  shaka::Number next;
  for (std::size_t i = 1; i < args.size(); i++) {
    next = shaka::get<shaka::Number>(args[i]->get_data());
    result = gcd_pair(result, next);
  }

  NodePtr result_value = std::make_shared<shaka::DataNode>(result);

  Args result_vector = {result_value};

  return result_vector;

}


// (lcm n1 ...)
Args lcm_numbers(Args args) {


  shaka::Number result = shaka::get<shaka::Number>(args[0]->get_data());
  shaka::Number next;
  shaka::Number gcd;
  for (std::size_t i = 1; i < args.size(); i++) {
    next = shaka::get<shaka::Number>(args[i]->get_data());
    gcd = gcd_pair(result, next);
    result = (result*next)|gcd;
  }

  NodePtr result_value = std::make_shared<shaka::DataNode>(result);

  Args result_vector = {result_value};

  return result_vector;


}

// (numerator q)
Args numerator_numbers(Args args) {

  shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());

  shaka::Number result(boost::get<shaka::Rational>(n1.get_value()).get_numerator());

  NodePtr result_value = std::make_shared<shaka::DataNode>(result);

  Args result_vector = {result_value};

  return result_vector;


}

// (denominator q)
Args denominator_numbers(Args args) {

  shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());

  shaka::Number result(boost::get<shaka::Rational>(n1.get_value()).get_denominator());

  NodePtr result_value = std::make_shared<shaka::DataNode>(result);

  Args result_vector = {result_value};

  return result_vector;
}


// (floor x)
Args floor_numbers(Args args) {

  shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
  if (n1.get_value().type() == typeid(shaka::Real)) {
    shaka::Number result(floor(boost::get<shaka::Real>(n1.get_value()).get_value()));
    NodePtr result_value = std::make_shared<shaka::DataNode>(result);
    Args result_vector = {result_value};
    return result_vector;
  }
  else if (n1.get_value().type() == typeid(shaka::Integer)) {
    shaka::Number result(floor(boost::get<shaka::Integer>(n1.get_value()).get_value()));
    NodePtr result_value = std::make_shared<shaka::DataNode>(result);
    Args result_vector = {result_value};
    return result_vector;
  }
  else {
    int numerator = boost::get<shaka::Rational>(n1.get_value()).get_numerator();
    int denominator = boost::get<shaka::Rational>(n1.get_value()).get_denominator();

    shaka::Number result(floor((double) numerator / (double) denominator));
    NodePtr result_value = std::make_shared<shaka::DataNode>(result);
    Args result_vector = {result_value};
    return result_vector;
  }

}
// (ceiling x)
Args ceiling_numbers(Args args) {

  shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
  if (n1.get_value().type() == typeid(shaka::Real)) {
    shaka::Number result(ceil(boost::get<shaka::Real>(n1.get_value()).get_value()));
    NodePtr result_value = std::make_shared<shaka::DataNode>(result);
    Args result_vector = {result_value};
    return result_vector;
  }
  else if (n1.get_value().type() == typeid(shaka::Integer)) {
    shaka::Number result(ceil(boost::get<shaka::Integer>(n1.get_value()).get_value()));
    NodePtr result_value = std::make_shared<shaka::DataNode>(result);
    Args result_vector = {result_value};
    return result_vector;
  }
  else {
    int numerator = boost::get<shaka::Rational>(n1.get_value()).get_numerator();
    int denominator = boost::get<shaka::Rational>(n1.get_value()).get_denominator();

    shaka::Number result(ceil((double) numerator / (double) denominator));
    NodePtr result_value = std::make_shared<shaka::DataNode>(result);
    Args result_vector = {result_value};
    return result_vector;
  }
}

// (truncate x)
Args truncate_numbers(Args args) {

  shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
  if (n1.get_value().type() == typeid(shaka::Real)) {
    shaka::Number result(trunc(boost::get<shaka::Real>(n1.get_value()).get_value()));
    NodePtr result_value = std::make_shared<shaka::DataNode>(result);
    Args result_vector = {result_value};
    return result_vector;
  }
  else if (n1.get_value().type() == typeid(shaka::Integer)) {
    shaka::Number result(trunc(boost::get<shaka::Integer>(n1.get_value()).get_value()));
    NodePtr result_value = std::make_shared<shaka::DataNode>(result);
    Args result_vector = {result_value};
    return result_vector;
  }
  else {
    int numerator = boost::get<shaka::Rational>(n1.get_value()).get_numerator();
    int denominator = boost::get<shaka::Rational>(n1.get_value()).get_denominator();

    shaka::Number result(trunc((double) numerator / (double) denominator));
    NodePtr result_value = std::make_shared<shaka::DataNode>(result);
    Args result_vector = {result_value};
    return result_vector;
  }
}

// (round x)
Args round_numbers(Args args) {

  shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());

  if (n1.get_value().type() == typeid(shaka::Real)) {
    shaka::Number result(round(boost::get<shaka::Real>(n1.get_value()).get_value()));
    NodePtr result_value = std::make_shared<shaka::DataNode>(result);
    Args result_vector = {result_value};
    return result_vector;
  }
  else if (n1.get_value().type() == typeid(shaka::Integer)) {
    shaka::Number result(round(boost::get<shaka::Integer>(n1.get_value()).get_value()));
    NodePtr result_value = std::make_shared<shaka::DataNode>(result);
    Args result_vector = {result_value};
    return result_vector;
  }
  else {
    int numerator = boost::get<shaka::Rational>(n1.get_value()).get_numerator();
    int denominator = boost::get<shaka::Rational>(n1.get_value()).get_denominator();
    shaka::Number result(round((double) numerator / (double) denominator));
    NodePtr result_value = std::make_shared<shaka::DataNode>(result);
    Args result_vector = {result_value};
    return result_vector;
  }

}


// (exp z)
Args exp_numbers(Args args) {

  shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());

  if (n1.get_value().type() == typeid(shaka::Integer)) {
    shaka::Number result(exp(boost::get<shaka::Integer>(n1.get_value()).get_value()));
    shaka::Number truncated_result(
        trunc(
            boost::get<shaka::Real>(
                result.get_value()).get_value() * 100000000000) / 100000000000);
    NodePtr result_value = std::make_shared<shaka::DataNode>(truncated_result);
    Args result_vector = {result_value};
    return result_vector;
  }
  else if (n1.get_value().type() == typeid(shaka::Real)) {
    shaka::Number result(exp(boost::get<shaka::Real>(n1.get_value()).get_value()));
    shaka::Number truncated_result(
        trunc(
            boost::get<shaka::Real>(
                result.get_value()).get_value() * 100000000000) / 100000000000);
    NodePtr result_value = std::make_shared<shaka::DataNode>(truncated_result);
    Args result_vector = {result_value};
    return result_vector;
  }
  else {
    int numerator = boost::get<shaka::Rational>(n1.get_value()).get_numerator();
    int denominator = boost::get<shaka::Rational>(n1.get_value()).get_denominator();
    shaka::Number result(exp((double) numerator / (double) denominator));
    shaka::Number truncated_result(
        trunc(
            boost::get<shaka::Real>(
                result.get_value()).get_value() * 100000000000) / 100000000000);
    NodePtr result_value = std::make_shared<shaka::DataNode>(truncated_result);
    Args result_vector = {result_value};
    return result_vector;
  }

}

// (log z)

Args log_numbers(Args args) {

  shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());

  if (n1.get_value().type() == typeid(shaka::Integer)) {
    shaka::Number result(log(boost::get<shaka::Integer>(n1.get_value()).get_value()));
    shaka::Number truncated_result(
        trunc(
            boost::get<shaka::Real>(
                result.get_value()).get_value() * 100000000000) / 100000000000);
    NodePtr result_value = std::make_shared<shaka::DataNode>(truncated_result);
    Args result_vector = {result_value};
    return result_vector;
  }
  else if (n1.get_value().type() == typeid(shaka::Real)) {
    shaka::Number result(log(boost::get<shaka::Real>(n1.get_value()).get_value()));
    shaka::Number truncated_result(
        trunc(
            boost::get<shaka::Real>(
                result.get_value()).get_value() * 100000000000) / 100000000000);
    NodePtr result_value = std::make_shared<shaka::DataNode>(truncated_result);
    Args result_vector = {result_value};
    return result_vector;
  }
  else {
    int numerator = boost::get<shaka::Rational>(n1.get_value()).get_numerator();
    int denominator = boost::get<shaka::Rational>(n1.get_value()).get_denominator();
    shaka::Number result(log((double) numerator / (double) denominator));
    shaka::Number truncated_result(
        trunc(
            boost::get<shaka::Real>(
                result.get_value()).get_value() * 100000000000) / 100000000000);
    NodePtr result_value = std::make_shared<shaka::DataNode>(truncated_result);
    Args result_vector = {result_value};
    return result_vector;
  }

}


// (log z1 z2)
Args log_n_numbers(Args args) {

  Args unary_log_arg1 = {args[0]};
  Args unary_log_arg2 = {args[1]};

  Args unary_log_res1 = log_numbers(unary_log_arg1, env);
  Args unary_log_res2 = log_numbers(unary_log_arg2, env);

  shaka::Number log_n1 = shaka::get<shaka::Number>(unary_log_res1[0]->get_data());
  shaka::Number log_n2 = shaka::get<shaka::Number>(unary_log_res2[0]->get_data());

  shaka::Number result = log_n1 / log_n2;

  shaka::Number truncated_result(
      trunc(
          boost::get<shaka::Real>(
              result.get_value()).get_value() * 100000000000) / 100000000000);

  NodePtr result_value = std::make_shared<shaka::DataNode>(truncated_result);
  Args result_vector = {result_value};
  return result_vector;

}
// (sin z)
// (cos z)
// (tan z)
// (asin z)
// (acos z)
// (atan z)
// (atan y x)

// (square z)
// (sqrt z)
Args sqrt_numbers(Args args) {


  shaka::Number num = shaka::get<shaka::Number>(args[0]->get_data());
  double inter = 0;

  // First, convert our numbers into double.
  if (num.get_value().type() == typeid(shaka::Integer)) {
    inter = shaka::get<shaka::Integer>(num.get_value()).get_value();
  }
  else if (num.get_value().type() == typeid(shaka::Rational)) {
    auto rat = shaka::get<shaka::Rational>(num.get_value());
    inter = static_cast<double>(rat.get_numerator()) /
        static_cast<double>(rat.get_denominator());
  }
  else if (num.get_value().type() == typeid(shaka::Real)) {
    inter = shaka::get<shaka::Real>(num.get_value()).get_value();
  }

  // Then, square root the double.
  inter = std::sqrt(inter);

  // Rewrap it in a NodePtr
  return {make_node(shaka::Number(inter))};
}

// (exact-integer-sqrt k)
// (expt z1 z2)

// DON'T DO THE COMPLEX LIBRARY PROCEDURES

// (inexact z)
// (exact z)

} // namespace impl

Callable add = impl::add_numbers;
Callable mul = impl::mul_numbers;
//Function neg = impl::neg_numbers;
Callable sub = impl::sub_numbers;
Callable reciprocal = impl::reciprocal_numbers;
Callable div = impl::div_numbers;
Callable abs = impl::abs_numbers;
Callable floor_div = impl::floor_div_numbers;
Callable floor_quotient = impl::floor_quotient_numbers;
Callable floor_remainder = impl::floor_remainder_numbers;
Callable truncate_div = impl::truncate_div_numbers;
Callable truncate_quotient = impl::truncate_quotient_numbers;
Callable truncate_remainder = impl::truncate_remainder_numbers;
Callable quotient = impl::quotient_numbers;
Callable remainder = impl::remainder_numbers;
Callable modulo = impl::modulo_numbers;
Callable gcd = impl::gcd_numbers;
Callable lcm = impl::lcm_numbers;
Callable numerator = impl::numerator_numbers;
Callable denominator = impl::denominator_numbers;
Callable floor = impl::floor_numbers;
Callable ceiling = impl::ceiling_numbers;
Callable truncate = impl::truncate_numbers;
Callable round = impl::round_numbers;
Callable exp = impl::exp_numbers;
Callable log = impl::log_numbers;
Callable logn = impl::log_n_numbers;
Callable sqrt = impl::sqrt_numbers;
} // namespace stdproc
} // namespace shaka

