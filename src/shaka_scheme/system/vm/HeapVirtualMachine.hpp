//
// Created by Billy Wooton on 9/8/17.
//

#ifndef SHAKA_SCHEME_HEAPVIRTUALMACHINE_HPP
#define SHAKA_SCHEME_HEAPVIRTUALMACHINE_HPP


#include <vector>
#include "shaka_scheme/system/base/Data.hpp"

namespace shaka {


/**
 * @note Forward declaration of CallFrame class that will need to
 * be implemented to augment the design of the VM
 */

class CallFrame;

/**
 * @note These are type aliases to assist in maintaining uniformity
 * of VM design in preparation for later design changes to other parts
 * of the system. These aliases can be changed later without the
 * entire code base for the VM needing to be modified
 */

using Accumulator = NodePtr;
using Expression = NodePtr;
using EnvPtr = std::shared_ptr<Environment>;
using ValueRib = std::vector<NodePtr>;
using FramePtr = std::shared_ptr<CallFrame>;


/**
 * @brief The class implementation for the Virtual Machine.
 * Lays out the specification of the Heap Based Virtual Machine
 * Based on R. Kent Dybvig's PhD dissertation
 */
class HeapVirtualMachine {

  HeapVirtualMachine(
      Accumulator a,
      Expression x,
      EnvPtr e,
      ValueRib r,
      FramePtr s) : acc(a), exp(x), env(e), rib(r), frame(s) {}

   ~HeapVirtualMachine();

  /**
    * @brief The method that actually processes the 12 assembly instructions
    * Changes the contents of each register in place
    */
  NodePtr evaluate_assembly_instruction();

  /**
  * @brief Returns the current contents of the Accumulator register
  * @return The contents of the Accumulator
  */
  Accumulator get_accumulator() const;

  /**
   * @brief Returns the contents of the Expression register
   * @return The next expression to be evaluated
   */
  Expression get_expression() const;

  /**
   * @brief Returns the contents of the Environment register
   * @return The EnvPtr which points to the immediate Environment frame
   */
  EnvPtr get_environment() const;

  /**
   * @brief Returns the contents of the ValueRib register
   * @return The std::vector of arguments (NodePtr) evaluated thus far
   */
  ValueRib get_value_rib() const;

  /**
   * @brief Returns the contents of the CurrentStack register
   * @return The pointer to the top CallFrame on the stack
   */
  FramePtr get_call_frame() const;

  /**
   * @brief Sets the value of the Accumulator register
   * @param a The new value to be placed in the Accumulator
   */
  void set_accumulator(Accumulator a);

  /**
   * @brief Sets the value of the Expression register
   * @param x The new contents of the Expression register
   */
  void set_expression(Expression x);

  /**
   * @brief Restores parameter s to be the CurrentStack
   * @param s The pointer to a CallFrame to represent the new CurrentStack
   */
  void push_call_frame(FramePtr s);

  /**
   * @brief Sets the value of the Environment register to be the parameter e
   * @param e The new contents of the Environment register
   */
  void set_environment(EnvPtr e);

  /**
   * @brief Sets the ValueRib register to be the parameter r
   * @param r The new contents of the ValueRib register
   */
  void set_value_rib(ValueRib r);

private:
  Accumulator acc;
  Expression exp;
  EnvPtr env;
  ValueRib rib;
  FramePtr frame;
};

}// namespace shaka
#endif //SHAKA_SCHEME_HEAPVIRTUALMACHINE_HPP
