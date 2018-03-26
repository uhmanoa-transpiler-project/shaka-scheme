//
// Created by Kayla Kwock on 3/18/18.
//

#ifndef SHAKA_SCHEME_STDPROC_PAIRS_AND_LISTS_HPP
#define SHAKA_SCHEME_STDPROC_PAIRS_AND_LISTS_HPP

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

//(pair? ...)
Args is_pair(Args args){
  if (args.size() != 1) {
    throw InvalidInputException(1,
                                "pair?: Invalid number of arguments for "
                                    "procedure");
  }
  return {shaka::create_node(shaka::Data(shaka::Boolean(
      args[0]->get_type() == Data::Type::DATA_PAIR)))};
}

//(cons ...)
Args cons(Args args) {
  if (args.size() != 2) {
    throw InvalidInputException(2,
                                "cons: Invalid number of arguments for "
                                    "procedure");
  }
  return {shaka::create_node(shaka::DataPair(shaka::Data(*args[0]),
                                             shaka::Data(*args[1])))
  };
};

//(car ...)
Args car(Args args) {

  if (args[0]->get_type() != Data::Type::DATA_PAIR) {
    throw InvalidInputException(3,
                                "car: Type of given argument is not "
                                    "DATA_PAIR");
  }
  if (args[0]->get_type() == Data::Type::NULL_LIST) {
    throw InvalidInputException(4,
                                "car: Cannot return the car of"
                                    "an empty list");
  }
  shaka::DataPair dp {shaka::create_node(shaka::Data(
      shaka::DataPair(args[0])))};
  return {shaka::create_node(shaka::Data(dp.car()))};
}

//(cdr ...)
Args cdr(Args args) {

  if (args[0]->get_type() != Data::Type::DATA_PAIR) {
    throw InvalidInputException(5,
                                "cdr: Type of given argument is not "
                                    "DATA_PAIR");
  }
  if (args[0]->get_type() == Data::Type::NULL_LIST) {
    throw InvalidInputException(6,
                                "cdr: Cannot return the cdr of"
                                    "an empty list");
  }
  shaka::DataPair dp {shaka::create_node(shaka::Data(
      shaka::DataPair(args[0])))};
  return {shaka::create_node(shaka::Data(dp.cdr()))};
}
//(set-car! ...)
Args set_car(Args args){
  if(args[0]->get_type() != Data::Type::DATA_PAIR){
    throw InvalidInputException(10,
                                "set-car!: Type of given argument is not "
                                    "DATA_PAIR");
  }
  if(args.size() != 2){
    throw InvalidInputException(11,
                                "set-car!: Invalid number of arguments given");
  }
  args[0]->get<DataPair>().set_car(args[1]);
  return {create_unspecified()};
}

//(set-cdr! ...)
Args set_cdr(Args args){
  if(args[0]->get_type() != Data::Type::DATA_PAIR){
    throw InvalidInputException(12,
                                "set-cdr!: Type of given argument is not "
                                    "DATA_PAIR");
  }
  if(args.size() != 2){
    throw InvalidInputException(13,
                                "set-cdr!: Invalid number of arguments given");
  }
  args[0]->get<DataPair>().set_cdr(args[1]);
  return {create_unspecified()};
}
} // namespace impl

Callable is_pair = impl::is_pair;
Callable cons = impl::cons;
Callable car = impl::car;
Callable cdr = impl::cdr;
Callable set_car = impl::set_car;
Callable set_cdr = impl::set_cdr;
} // namespace stdproc
} // namespace shaka



#endif //SHAKA_SCHEME_STDPROCS_PAIRS_AND_LISTS_HPP
