//
// Created by Billy Wooton on 10/8/17.
//

#ifndef SHAKA_SCHEME_CLOSURE_HPP
#define SHAKA_SCHEME_CLOSURE_HPP

#include "shaka_scheme/system/base/Environment.hpp"
#include <vector>
#include <functional>

namespace shaka {

class Data;
class CallFrame;

using EnvPtr = std::shared_ptr<Environment>;
using FramePtr = std::shared_ptr<CallFrame>;
using ValueRib = std::vector<NodePtr>;
using Callable = std::function<std::vector<NodePtr>(std::vector<NodePtr>)>;
using CallablePtr = std::shared_ptr<Callable>;

using VariableList = std::vector<Symbol>;

class Closure {
public:

  /**
   * @brief Standard constructor for Closure class
   * @param env Pointer to the lexical environment of the closure
   * @param fb The compiled expression representing the body of the function
   * @param vl The list of the variables that are the formal parameters
   * @param cl A callable function object, needed for primitive procedures
   * @param frame A pointer to a CallFrame, needed for continuations
   */
  Closure(EnvPtr env, NodePtr fb, VariableList vl,
          CallablePtr cl, FramePtr frame);

  /**
   * @brief Default constructor for Closure class
   * Initializes environment to be an empty environment
   * Initializes function body to be the empty list
   * Initializes the variable list to be an empty vector
   * Initializes the callable to be a nullptr
   * Initializes the FramePtr to point to a default frame
   */
  Closure();

  /**
   * @brief Method to get the body of the function
   * @return NodePtr to the compiled body expression
   */
  NodePtr get_function_body();

  /**
   * @brief Extends the closures environment with the contents of ValueRib
   * @param vr The contents of the ValueRib register from the VM
   */
  void extend_environment(ValueRib vr);

  /**
   * @brief A getter method for accessing the lexical enviroment of the closure
   * @return A pointer to the lexical environment of the closure
   */
  EnvPtr get_environment();

  /**
   * @brief A procedure to invoke the callable object on arguments
   * @param args The arguments to the procedure
   * @return A vector containing the result(s) of the procedure call
   */
  std::vector<NodePtr> call(std::vector<NodePtr> args);

  /**
   * @brief A procedure to retrieve the CallFrame from a continuation closure
   * @return The pointer to the CallFrame held by the continuation
   */
  FramePtr get_call_frame();

  /**
   * @brief A procedure to retrieve the parameter variable list
   * @return The vector of symbols comprising the variable list
   */
  VariableList get_variable_list();

  /**
   * @brief Method to determine whether or not this is a Native Closure
   * @return true if the CallablePtr is not null, false otherwise
   */
  bool is_native_closure();

  /**
   * @brief Method to determine wheter or not this is a Continuation Closure
   * @return true if the FramePtr is not null, false otherwise
   */
  bool is_continuation_closure();



private:

  EnvPtr env;
  NodePtr func_body;
  VariableList variable_list;
  CallablePtr callable;
  FramePtr frame;

};

}

#endif //SHAKA_SCHEME_CLOSURE_HPP
