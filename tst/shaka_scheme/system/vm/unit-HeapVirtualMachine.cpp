//
// Created by Billy Wooton on 10/2/17.
//

#include <gmock/gmock.h>
#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/vm/HeapVirtualMachine.hpp"
#include "shaka_scheme/system/base/Environment.hpp"

using namespace shaka;

/**
 * @brief Test: evaluate_assembly_instruction() with (halt) as exp
 */
TEST(HeapVirtualMachineUnitTest, evaluate_halt) {

  // Given: An accumulator that holds a NodePtr with symbol 'result
  Symbol acc_value("result");
  NodePtr accumulator = std::make_shared<Data>(acc_value);

  // Given: An assembly instruction of the form (halt)
  Symbol instruction("halt");
  Data instruction_data(instruction);
  DataPair instruction_pair(instruction_data);
  NodePtr expression = std::make_shared<Data>(instruction_pair);

  // Given: A pointer to an Environment with a null parent pointer
  EnvPtr env = std::make_shared<Environment>(nullptr);

  // Given: An empty ValueRib
  ValueRib vr;

  // Given: A HeapVirtualMachine instance constructed with these items
  HeapVirtualMachine hvm (accumulator, expression, env, vr, nullptr);

  // When: You invoke the evaluate_assembly_instruction() method
  auto result = hvm.evaluate_assembly_instruction();

  // Then: It will return the contents of the accumulator register
  ASSERT_EQ(result->get<Symbol>(), Symbol("result"));

}

/**
 * @brief Test: evaluate_assembly_instruction() with (refer var x) as exp
 */
TEST(HeapVirtualMachineUnitTest, evaluate_refer) {
  // Given: An assembly instruction of the form (refer a (halt))
  Symbol instruction("refer");
  Symbol var("a");
  Symbol next_instr("halt");

  Data next_instr_data(next_instr);
  DataPair next_instr_pair(next_instr_data);

  Data var_data(var);
  DataPair var_x_pair(var, next_instr_pair);

  Data instruction_data(instruction);
  DataPair refer_var_x(instruction_data, var_x_pair);

  NodePtr expression = std::make_shared<Data>(refer_var_x);

  // Given: A pointer to Environment containing a binding for the symbol 'a
  EnvPtr env = std::make_shared<Environment>(nullptr);
  env->set_value(Symbol("a"), create_node(String("test")));

  // Given: An empty value rib
  ValueRib vr;

  // Given: A HeapVirtualMachine instance constructed with these items
  HeapVirtualMachine hvm(nullptr, expression, env, vr, nullptr);

  // When: You invoke the evaluate_assembly_instruction() method
  hvm.evaluate_assembly_instruction();

  // Then: The string "test" which was bound to 'a will be in the accumulator
  ASSERT_EQ(hvm.get_accumulator(), env->get_value(Symbol("a")));

  // Then: The next_expression will be (halt)
  ASSERT_EQ(hvm.get_expression()->get<DataPair>().car()->get<Symbol>(),
            Symbol("halt"));

  // When: You then invoke the evaluate_assembly_instruction() method again
  auto result = hvm.evaluate_assembly_instruction();

  // Then: It will return the contents of the accumulator
  ASSERT_EQ(result, env->get_value(Symbol("a")));
}