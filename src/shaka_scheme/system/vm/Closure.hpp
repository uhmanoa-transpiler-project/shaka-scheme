//
// Created by Billy Wooton on 10/8/17.
//

#ifndef SHAKA_SCHEME_CLOSURE_HPP
#define SHAKA_SCHEME_CLOSURE_HPP

#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/base/DataPair.hpp"
#include "shaka_scheme/system/base/Environment.hpp"
#include "shaka_scheme/system/vm/CallFrame.hpp"
#include <vector>

namespace shaka {

class Callable;

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
          Callable cl, FramePtr frame);

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



private:

  EnvPtr env;
  NodePtr func_body;
  VarableList variable_list;
  Callable callable;
  FramePtr frame;

};

}

#endif //SHAKA_SCHEME_CLOSURE_HPP
