//
// Created by Billy Wooton on 10/2/17.
//

#include <gmock/gmock.h>
#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/vm/HeapVirtualMachine.hpp"
#include "shaka_scheme/system/base/Environment.hpp"
#include "shaka_scheme/system/core/lists.hpp"

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
  DataPair var_x_pair(var_data, *core::list(create_node(next_instr_pair)));

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

/**
 * @brief Test: evaluate_assembly_instruction() with (constant obj x) as exp
 */
TEST(HeapVirtualMachineUnitTest, evaluate_constant) {
  // Given: An assembly instruction of the form (constant "Hello" (halt))

  Symbol instruction("constant");
  String obj("Hello");
  Symbol next_instr("halt");

  Data next_instr_data(next_instr);
  DataPair next_instr_pair(next_instr_data);

  Data obj_data(obj);
  DataPair constant_obj_pair(obj_data,
                             *core::list(create_node(next_instr_pair)));

  Data instruction_data(instruction);
  DataPair constant_obj_x(instruction_data, constant_obj_pair);

  NodePtr expression = std::make_shared<Data>(constant_obj_x);

  // Given: A pointer to an empty environment frame

  EnvPtr env = std::make_shared<Environment>(nullptr);

  // Given: An empty ValueRib

  ValueRib vr;

  // Given: A HeapVirtualMachine instance constructed with these items

  HeapVirtualMachine hvm(nullptr, expression, env, vr, nullptr);

  // When: You invoke the evaluate_assembly_instruction method on hvm

  hvm.evaluate_assembly_instruction();

  // Then: The accumulator will hold the string "Hello"
  ASSERT_EQ(hvm.get_accumulator()->get<String>(), String("Hello"));

  // Then: The next expression will be (halt)
  ASSERT_EQ(hvm.get_expression()->get<DataPair>().car()->get<Symbol>(),
            Symbol("halt"));

  // When: You then invoke the evaluate_assembly_instruction method again

  auto result = hvm.evaluate_assembly_instruction();

  // Then: The result you get back is the String("Hello")

  ASSERT_EQ(result->get<String>(), String("Hello"));
}

/**
 * @brief Test: evaluate_assembly_instruction() with (test then else) as exp
 */
TEST(HeapVirtualMachineUnitTest, evaluate_test_else) {

  // Given: An Accumulator that is the symbol #f

  NodePtr accumulator = std::make_shared<Data>(Symbol("#f"));

  // Given: A then expression of the form (constant "then" (halt))
  Symbol then_inst("constant");
  Data then_inst_data(then_inst);


  String then_obj("then");
  Data then_obj_data(then_obj);

  Symbol halt_inst("halt");
  Data halt_data(halt_inst);
  DataPair halt_pair(halt_data);

  DataPair obj_halt_pair(then_obj_data,
                         *core::list(create_node(halt_pair)));

  DataPair const_obj_halt(then_inst_data, obj_halt_pair);

  NodePtr expr = std::make_shared<Data>(const_obj_halt);

  // Given: An else expression of the form (constant "else" (halt))

  Symbol else_inst("constant");
  Data else_inst_data(then_inst);

  String else_obj("else");
  Data else_obj_data(else_obj);

  DataPair else_obj_halt_pair(else_obj_data,
                              *core::list(create_node(halt_pair)));

  DataPair const_else_obj_halt(else_inst_data, else_obj_halt_pair);

  NodePtr expr2 = std::make_shared<Data>(const_else_obj_halt);

  // Given: An assembly instruction of the form (test then else)

  Symbol instruction("test");

  Data instruction_data(instruction);

  DataPair then_else_pair(expr, create_node(DataPair(*expr2)));

  DataPair test_then_else(instruction_data, then_else_pair);

  NodePtr expression = std::make_shared<Data>(test_then_else);

  // Given: An EnvPtr that points to an empty environment

  EnvPtr env = std::make_shared<Environment>(nullptr);

  // Given: An empty ValueRib

  ValueRib vr;

  // Given: An instance of the HeapVirtualMachine constructed with these items

  HeapVirtualMachine hvm(accumulator, expression, env, vr, nullptr);

  // When: You invoke the evaluate_assembly_instruction_method

  hvm.evaluate_assembly_instruction();

  // Then: The next expression will be (constant "else" (halt))

  ASSERT_EQ(hvm.get_expression()->get<DataPair>().cdr()->get<DataPair>().car
      ()->get<String>(), String("else"));

  // When: You invoke the evaluate_assembly_instruction_method again

  hvm.evaluate_assembly_instruction();

  // Then: The accumulator will hold the string "else"

  ASSERT_EQ(hvm.get_accumulator()->get<String>(), String("else"));

  // Then: The next expression will be (halt)

  ASSERT_EQ(hvm.get_expression()->get<DataPair>().car()->get<Symbol>(),
  Symbol("halt"));

}

/**
 * @brief Test: evaluate_assembly_instruction() with (test then else) as exp
 */
TEST(HeapVirtualMachineUnitTest, evaluate_test_then) {

  // Given: An Accumulator that is the symbol #t

  NodePtr accumulator = std::make_shared<Data>(Symbol("#t"));

  // Given: A then expression of the form (constant "then" (halt))
  Symbol then_inst("constant");
  Data then_inst_data(then_inst);


  String then_obj("then");
  Data then_obj_data(then_obj);

  Symbol halt_inst("halt");
  Data halt_data(halt_inst);
  DataPair halt_pair(halt_data);

  DataPair obj_halt_pair(then_obj_data,
                         *core::list(create_node(halt_pair)));

  DataPair const_obj_halt(then_inst_data, obj_halt_pair);

  NodePtr expr = std::make_shared<Data>(const_obj_halt);

  // Given: An else expression of the form (constant "else" (halt))

  Symbol else_inst("constant");
  Data else_inst_data(then_inst);

  String else_obj("else");
  Data else_obj_data(else_obj);

  DataPair else_obj_halt_pair(else_obj_data,
                              *core::list(create_node(halt_pair)));

  DataPair const_else_obj_halt(else_inst_data, else_obj_halt_pair);

  NodePtr expr2 = std::make_shared<Data>(const_else_obj_halt);

  // Given: An assembly instruction of the form (test then else)

  Symbol instruction("test");

  Data instruction_data(instruction);

  DataPair then_else_pair(expr, create_node(DataPair(*expr2)));

  DataPair test_then_else(instruction_data, then_else_pair);

  NodePtr expression = std::make_shared<Data>(test_then_else);

  // Given: An EnvPtr that points to an empty environment

  EnvPtr env = std::make_shared<Environment>(nullptr);

  // Given: An empty ValueRib

  ValueRib vr;

  // Given: An instance of the HeapVirtualMachine constructed with these items

  HeapVirtualMachine hvm(accumulator, expression, env, vr, nullptr);

  // When: You invoke the evaluate_assembly_instruction_method

  hvm.evaluate_assembly_instruction();

  // Then: The next expression will be (constant "then" (halt))

  ASSERT_EQ(hvm.get_expression()->get<DataPair>().cdr()->get<DataPair>().car
      ()->get<String>(), String("then"));

  // When: You invoke the evaluate_assembly_instruction_method again

  hvm.evaluate_assembly_instruction();

  // Then: The accumulator will hold the string "then"

  ASSERT_EQ(hvm.get_accumulator()->get<String>(), String("then"));

  // Then: The next expression will be (halt)

  ASSERT_EQ(hvm.get_expression()->get<DataPair>().car()->get<Symbol>(),
            Symbol("halt"));

}