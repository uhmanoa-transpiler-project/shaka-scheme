//
// Created by Kayla Kwock on 3/26/2018.
//

#include "shaka_scheme/runtime/stdproc/pairs_and_lists.hpp"

namespace shaka {
namespace stdproc {

using Args = std::deque<NodePtr>;

using Callable = std::function<std::deque<NodePtr>(std::deque<NodePtr>)>;

namespace impl {

//(pair? ...)
Args is_pair(Args args) {
  if (args.size() != 1) {
    throw InvalidInputException(1,
                                "pair?: Invalid number of arguments for "
                                    "procedure");
  }
  return {create_node(Data(Boolean(
      args[0]->get_type() == Data::Type::DATA_PAIR)))};
}

//(cons ...)
Args cons(Args args) {
  if (args.size() != 2) {
    throw InvalidInputException(2,
                                "cons: Invalid number of arguments for "
                                    "procedure");
  }
  return {create_node(Data(DataPair(Data(*args[0]),
                               Data(*args[1]))))
  };
}

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

  return {create_node(*args[0]->get<DataPair>().car())};
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

  return {create_node(*args[0]->get<DataPair>().cdr())};
}

//(set-car! ...)
Args set_car(Args args) {
  if (args[0]->get_type() != Data::Type::DATA_PAIR) {
    throw InvalidInputException(10,
                                "set-car!: Type of given argument is not "
                                    "DATA_PAIR");
  }
  if (args.size() != 2) {
    throw InvalidInputException(11,
                                "set-car!: Invalid number of arguments given");
  }
  args[0]->get<DataPair>().set_car(args[1]);
  return {create_unspecified()};
}

//(set-cdr! ...)
Args set_cdr(Args args) {
  if (args[0]->get_type() != Data::Type::DATA_PAIR) {
    throw InvalidInputException(12,
                                "set-cdr!: Type of given argument is not "
                                    "DATA_PAIR");
  }
  if (args.size() != 2) {
    throw InvalidInputException(13,
                                "set-cdr!: Invalid number of arguments given");
  }
  args[0]->get<DataPair>().set_cdr(args[1]);
  return {create_unspecified()};
}

//(null? ...)
Args is_null(Args args) {
  if (args.size() != 1) {
    throw InvalidInputException(7,
                                "null?: Invalid number of arguments for "
                                    "procedure");
  }
  return {create_node(Data(Boolean(
      args[0]->get_type() == Data::Type::NULL_LIST)
  ))};
}

//(list? ...)
Args is_list(Args args) {
  if (args.size() != 1) {
    throw InvalidInputException(8,
                                "list?: Invalid number of arguments for "
                                    "procedure");
  }

  if (args[0]->get_type() != Data::Type::DATA_PAIR) {
    throw InvalidInputException(27,
                                "list?: Invalid number of arguments for "
                                    "procedure");
  }
  return {create_node(Data(Boolean(core::is_proper_list(args[0]))))};
}

//(make-list ...)
Args make_list(Args args) {
  // If the args given are either empty or have too many arguments
  //  Throw an error
  if (args.size() > 2 || args.empty()) {
    throw InvalidInputException(9,
                                "make-list: Invalid number of arguments for"
                                    " procedure");
  }
  // Create an args to hold arguments for list
  Args list_args;
  // If a single argument is given
  if (args.size() == 1) {
    // If the type of the given argument is not a number
    //  Throw an error
    if (args[0]->get_type() != Data::Type::NUMBER) {
      throw InvalidInputException(15,
                                  "make-list: Given argument is not of type "
                                      "NUMBER");
    }

    // For the value of the given number
    //  Add a null list at the end
    for (int i = 0; i < args[0]->get<Number>(); i++) {
      list_args.push_back(create_node(Data()));
    }
  }
    // Else when 2 arguments are given
  else {
    // Set the list head to the second argument given
    // For the value of the first argument
    //  Append the value of the second argument
    for (int i = 0; i < args[0]->get<Number>(); i++) {
      list_args.push_back(args[1]);
    }
  }
  // Return the resulting list as type Args
  Args result{list(list_args)};
  return result;
}

//(list ...)
Args list(Args args) {
  // If the amount of given arguments exeedes the maximum capacity
  //  Throw an error
  if (args.size() == sizeof(std::size_t)) {
    throw InvalidInputException(14,
                                "list: Size of given argument exceeds "
                                    "maximum size");
  }

  // If args is empty, return null list
  if (args.size() == 0) {
    return {create_node(Data())};
  }
    // Otherwise, args is not empty
  else {
    // Starting from the end, for each item in the args, the accumulated list
    // starting as a null list
    NodePtr list = core::list();
    for (std::size_t i = args.size(); i > 0; i--) {
      // Take the item, cons it with the accumulated list
      list = core::cons(args[i - 1], list);
      // Iterate
    }
    // Result: the args turned into a list
    Args result{list};
    // Then, return the list
    return result;
  }
}

//(length ...)
Args length(Args args) {

  // If the given argument isn't a list
  //   Throw an error
  if (args[0]->get_type() != Data::Type::DATA_PAIR) {
    throw InvalidInputException(15,
                                "length:Type of given argument is "
                                    "not DATA_PAIR");
  }
  // Create a variable set to the head of the given list
  NodePtr head = create_node(*args[0]);
  // Call (length) on list
  std::size_t length = core::length(head);
  // Create a variable of type Args to hold the length of the list
  Args result{create_node(Number(Integer(length)))};
  // Return the Args variable
  return result;
}

//(append ...)
Args append(Args args) {
  // Create a NodePtr at the given list
  NodePtr list;
  // If no args are given
  if (args.empty()) {
    // Set the list to an empty list
    list = core::append();
  }
  // Else if one arg is given
  else if (args.size() == 1) {
    // Set the list to itself
    list = core::append(args[0]);
  }
  // Else
  else {
    // Set list to the list provided
    list = args[0];
    // For each item given in the argument
    for (std::size_t i = 1; i < args.size(); i++) {
      // Add the item as a data pair at the end of the list
      list = core::append(list, core::list(args[i]));
    }
  }
  Args result{list};
  // Return the new list
  return result;
}

//(reverse ...)
Args reverse(Args args) {
  // If anything but a single argument is given
  //  Throw an error
  if(args.size() != 1){
    throw InvalidInputException(17,
                                "reverse: Invalid number of arguments given");
  }
  // If the argument is not of type DATA_PAIR
  //  Throw an error
  if(args[0]->get_type() != Data::Type::DATA_PAIR){
    throw InvalidInputException(18,
                            "reverse: Given argument is not of type "
                                "DATA_PAIR");
  }
  // Return the reverse of the list
  return {core::reverse(args[0])};
}

//(list-tail ...)
Args list_tail(Args args) {
  // If exactly 2 arguments are not given
  //  Throw an error
  if (args.size() != 2) {
    throw InvalidInputException(19,
                                "list_tail: Invalid number of arguments given");

  }
  // If the first argument is not a DataPair
  //  Throw an error
  if (args[0]->get_type() != Data::Type::DATA_PAIR){
    throw InvalidInputException(20,
                                "list_tail: First argument must be of type "
                                    "DATA_PAIR");
  }
  // If the second argument is not a number
  //  Throw an error
  if (args[1]->get_type() != Data::Type::NUMBER){
    throw InvalidInputException(21,
                                "list_tail: Second argument must be of type "
                                    "NUMBER");
  }
//if the second argument is not an integer or above 0 throw error

  // Create a node at the head of the list
  NodePtr list {args[0]};
  // For the number of times given by the second argument
  for(int i = 0; i < args[1]->get<Number>(); i++){
    // If the number argument's value exceeds the length of the list argument
    //  Throw an error
    if(list->get<DataPair>().cdr()->get_type() == Data::Type::NULL_LIST)
      throw InvalidInputException(22,
                                  "list_tail: Given index is not within "
                                      "bounds of the list");
    // Set the head to the rhs of the DataPair
    list = list->get<DataPair>().cdr();
  }
  // Return the new head of the list
  Args result {list};
  return result;
}

//(list-ref ...)
Args list_ref(Args args) {
  if(args.size() > 2 || args.empty()){
    throw InvalidInputException(16,
                                "list-ref: Invalid number of arguments");
  }
  NodePtr place = args[0];
  for(int i = 0; i < args[1]->get<Number>(); i++){
    place = place->get<DataPair>().cdr();
  }
  Args result {place->get<DataPair>().car()};
  return result;
}

//(list-set! ...)
Args list_set(Args args) {
  // If exactly 3 arguments are not given
  //  Throw an error
  if (args.size() != 3) {
    throw InvalidInputException(23,
                                "list_set: Invalid number of arguments given");

  }
  // If the first argument is not a DataPair
  //  Throw an error
  if (args[0]->get_type() != Data::Type::DATA_PAIR){
    throw InvalidInputException(24,
                                "list_set: First argument must be of type "
                                    "DATA_PAIR");
  }
  // If the second argument is not a number
  //  Throw an error
  if (args[1]->get_type() != Data::Type::NUMBER){
    throw InvalidInputException(25,
                                "list_set: Second argument must be of type "
                                    "NUMBER");
  }
//if the second argument is not an integer or above 0 throw error

  // Create a node at the head of the list
  NodePtr list {args[0]};
  // For the number of times given by the second argument
  for(int i = 0; i < args[1]->get<Number>() - 1; i++){
    // If the number argument's value exceeds the length of the list argument
    //  Throw an error
    if(list->get<DataPair>().cdr()->get_type() == Data::Type::NULL_LIST)
      throw InvalidInputException(26,
                                  "list_set: Given index is not within "
                                      "bounds of the list");
    // Set the head to the rhs of the DataPair
    list = list->get<DataPair>().cdr();
  }
  // Set the car of the head to the desired value given in args
  list->get<DataPair>().set_car(args[2]);
  // Return the new list
  Args result {args[0]};
  return result;
}

/*
//(memq ...)
Args memq(Args args) {}

//(memv ...)
Args memv(Args args) {}

//(member ...)
Args member(Args args) {}

//(assq ...)
Args assq(Args args) {}

//(assv ...)
Args assv(Args args) {}

//(assoc ...)
Args assoc(Args args) {}
*/
//(list-copy ...)
Args list_copy(Args args) {
  /**
   * implement circular list error handling
   */

  // If something else besides a list is given
  //  Return a copy of the argument given
  if(args[0]->get_type() != Data::Type::DATA_PAIR){
    Args result {shaka::create_node(*args[0])};
    return result;
  }
  // Create a variable at the head of the list and an Args list
  NodePtr head {args[0]};
  Args list_args;

  // While the cdr of the head is a DataPair
  //  Push a copy of the car value of head onto the Args list
  //  Set the new head to the cdr of the current head
  while (head->get<DataPair>().cdr()->get_type() == Data::Type::DATA_PAIR) {
    list_args.push_back(create_node(Data(*head->get<DataPair>().car())));
    head = head->get<DataPair>().cdr();
  }
  // If the final cdr is a NullList (proper list)
  //  Push a copy of the car value of head onto the Args list
  if(head->get<DataPair>().cdr()->get_type() == Data::Type::NULL_LIST){
    list_args.push_back(create_node(Data(*head->get<DataPair>().car())));
  }
  // Else push a copy of the head onto the Args list (improper list)
  else {
    list_args.push_back(create_node(Data(*head)));
  }
  // Return a list of the Args list
  return {stdproc::list(list_args)};
}

} // namespace impl

Callable is_pair = impl::is_pair;
Callable cons = impl::cons;
Callable car = impl::car;
Callable cdr = impl::cdr;
Callable set_car = impl::set_car;
Callable set_cdr = impl::set_cdr;
Callable is_null = impl::is_null;
Callable is_list = impl::is_list;
Callable make_list = impl::make_list;
Callable list = impl::list;
Callable length = impl::length;
Callable append = impl::append;
Callable reverse = impl::reverse;
Callable list_tail = impl::list_tail;
Callable list_ref = impl::list_ref;
Callable list_set = impl::list_set;
//Callable memq = impl::memq;
//Callable memv = impl::memv;
//Callable member = impl::member;
//Callable assq = impl::assq;
//Callable assv = impl::assv;
//Callable assoc = impl::assoc;
Callable list_copy = impl::list_copy;

} // namespace stdproc
} // namespace shaka