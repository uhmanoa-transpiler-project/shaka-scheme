//
// Created by Dylan Nakahodo on 10/4/17.
//

#ifndef SHAKA_SCHEME_COMPILER_HPP
#define SHAKA_SCHEME_COMPILER_HPP

#include "shaka_scheme/system/base/Data.hpp"

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
   * @param current_expression The expression to compile
   * @param next_instruction The next assembly instruction to evaluate
   */
  Compiler(Expression current_expression, Symbol& next_instruction);

  /**
   * @brief Destroys Compiler
   */
  ~Compiler();

private:
  Expression current_expression;
  Symbol& next_instruciton;
};

}
#endif //SHAKA_SCHEME_COMPILER_HPP
