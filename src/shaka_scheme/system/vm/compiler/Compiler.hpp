//
// Created by Dylan Nakahodo on 10/4/17.
//

#ifndef SHAKA_SCHEME_COMPILER_HPP
#define SHAKA_SCHEME_COMPILER_HPP

#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/core/types.hpp"
#include "shaka_scheme/system/core/lists.hpp"

namespace shaka {

/**
 * @brief Implementation of Scheme Compiler based on the Heap-Based model from
 *        R. Kent Dybvig's dissertation "Three Implementation Models for
 *        Scheme".  Translates Scheme expressions to 'assembly' instructions to
 *        be executed by the Virtual Machine.
 */

using Expression = NodePtr;

class Compiler {

public:

  /**
   * @brief Constructor for Compiler
   */
  Compiler();

  /**
   * @brief Destroys Compiler
   */
  ~Compiler();

  /**
   * @brief Compiles Shaka Scheme expressions to assembly instructions.
   * @param input The expression to compile.
   * @param next_instruction The next instruction to execute.
   * @return An assembly instruction.
   */
  Expression compile(Expression input,
                     Expression next_instruction = create_node(DataPair(Data(
                         Symbol("halt")))));

  /**
   * @brief Performs a single compile step.
   * @param input The pointer to the expression to compile one step.
   * @param output An expression list to append VM instructions onto
   */
  void compile_step(Expression input, Expression output);

};

}
#endif //SHAKA_SCHEME_COMPILER_HPP
