//
// Created by Billy Wooton on 10/2/17.
//

#include <gmock/gmock.h>
#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/vm/HeapVirtualMachine.hpp"
#include "shaka_scheme/system/core/lists.hpp"
#include "shaka_scheme/system/core/strings.hpp"

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
  hvm.evaluate_assembly_instruction();

  // Then: The accumulator register will contain the symbol 'result
  ASSERT_EQ(hvm.get_accumulator()->get<Symbol>(), Symbol("result"));

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
  hvm.evaluate_assembly_instruction();

  // Then: The accumulator will contain the string "test"
  ASSERT_EQ(hvm.get_accumulator()->get<String>(),
            env->get_value(Symbol("a"))->get<String>());
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

  hvm.evaluate_assembly_instruction();

  // Then: The accumulator register will contain the string "Hello"

  ASSERT_EQ(hvm.get_accumulator()->get<String>(), String("Hello"));
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

/**
 * @brief Test: evaluate_assembly_instruction() with (assign var x) as exp
 */
TEST(HeapVirtualMachineUnitTest, evaluate_assign) {

  // Given: An Accumulator with the Symbol("accumulator");

  Accumulator acc = std::make_shared<Data>(Symbol("accumulator"));

  // Given: An assembly instruction of the form (assign a (halt))
  Symbol instruction("assign");
  Data instruction_data(instruction);

  Symbol halt("halt");
  Data halt_data(halt);
  DataPair halt_pair(halt_data);

  Symbol var("a");
  Data var_data(var);
  DataPair var_halt_pair(var_data, *core::list(create_node(halt_pair)));

  DataPair assign_var_halt(instruction_data, var_halt_pair);

  NodePtr expression = std::make_shared<Data>(assign_var_halt);

  // Given: An EnvPtr that points to an empty environment

  EnvPtr env = std::make_shared<Environment>(nullptr);

  // Given: An empty ValueRib

  ValueRib vr;

  // Given: A HeapVirtualMachine instance constructed with these items

  HeapVirtualMachine hvm(acc, expression, env, vr, nullptr);

  // When: You invoke the evaluate_assembly_instruction() method

  hvm.evaluate_assembly_instruction();

  // Then: The environment register will contain the binding [a : accumulator]

  ASSERT_EQ(hvm.get_environment()->get_value(Symbol("a"))->get<Symbol>(),
            Symbol("accumulator"));

  // Then: The next expression will be (halt)

  ASSERT_EQ(hvm.get_expression()->get<DataPair>().car()->get<Symbol>(),
            Symbol("halt"));
}

/**
 * @brief Test: evaluate_assembly_instruction() with (frame x ret) as exp
 */
TEST(HeapVirtualMachineUnitTest, evaluate_frame) {

  // Given: An Accumulator containing the Symbol("finale")

  Accumulator accumulator = std::make_shared<Data>(Symbol("finale"));

  // Given: An assembly instruction of the form (frame (halt) (halt))

  Symbol halt("halt");

  Data halt_data(halt);

  DataPair halt_pair(halt_data);

  DataPair halt_halt(halt_pair, *core::list(create_node(halt_pair)));

  Symbol frame("frame");
  Data frame_data(frame);

  DataPair frame_halt_halt(frame_data, halt_halt);

  NodePtr expression = std::make_shared<Data>(frame_halt_halt);

  // Given: An EnvPtr with bindings [a : "Hello", b : "World"]

  EnvPtr env = std::make_shared<Environment>(nullptr);

  env->set_value(Symbol("a"), std::make_shared<Data>(String("Hello")));
  env->set_value(Symbol("b"), std::make_shared<Data>(String("World")));

  // Given: A ValueRib containing strings "RVal1" "RVal2" "RVal3"

  ValueRib vr = {create_node(String("RVal1")),
                 create_node(String("RVal2")),
                 create_node(String("RVal3"))};

  // Given: A HeapVirtualMachine instance constructed with these items

  HeapVirtualMachine hvm(accumulator, expression, env, vr, nullptr);

  // When: You invoke the evaluate_assembly_instruction() method

  hvm.evaluate_assembly_instruction();

  // Then: The control stack register has a new CallFrame

  ASSERT_NE(hvm.get_call_frame(), nullptr);

  // Then: The new CallFrame has an environment with bindings for a and b

  ASSERT_EQ(
      hvm.get_call_frame()->
          get_environment_pointer()->
          get_value(Symbol("a"))->get<String>(),
      String("Hello"));

  ASSERT_EQ(
    hvm.get_call_frame()->
        get_environment_pointer()->
        get_value(Symbol("b"))->get<String>(),
    String("World")
  );

  // Then: The new CallFrame has a ValueRib with "RVal1" "RVal2" "RVal3"

  ASSERT_EQ(
    hvm.get_call_frame()->
        get_value_rib()[0]->get<String>(),
    String("RVal1")
  );

  ASSERT_EQ(
    hvm.get_call_frame()->
        get_value_rib()[1]->get<String>(),
    String("RVal2")
  );

  ASSERT_EQ(
    hvm.get_call_frame()->
        get_value_rib()[2]->get<String>(),
    String("RVal3")
  );

  // Then: The new CallFrame has a next expression that is (halt)

  ASSERT_EQ(hvm.get_call_frame()->
      get_next_expression()->
      get<DataPair>().car()->get<Symbol>(),
  Symbol("halt"));

  // Then: The new CallFrame has a next reference that is nullptr

  ASSERT_EQ(hvm.get_call_frame()->get_next_frame(), nullptr);

  // Then: The HVM instance will have an empty ValueRib register

  ASSERT_EQ(hvm.get_value_rib().size(), 0);

  // Then: The HVM instance's Expression register will contain (halt)

  ASSERT_EQ(hvm.get_expression()->get<DataPair>().car()->get<Symbol>(),
  Symbol("halt"));

  // When: You invoke the evaluate_assembly_instruction() method again

  hvm.evaluate_assembly_instruction();

  // Then: The accumulator will hold the symbol 'finale

  ASSERT_EQ(hvm.get_accumulator()->get<Symbol>(), Symbol("finale"));

}

/**
 * @brief Test: evaluate_assembly_instruction() with (argument x) as exp
 */
TEST(HeapVirtualMachineUnitTest, evaluate_argument) {

  // Given: An Accumulator containing the symbol 'banana

  Symbol banana("banana");

  Accumulator accumulator = create_node(banana);

  // Given: An assembly instruction of the form (argument (halt))

  Symbol halt("halt");
  Data halt_data(halt);
  DataPair halt_pair(halt_data);

  Symbol argument("argument");
  Data argument_data(argument);
  DataPair argument_halt(argument, *core::list(create_node(halt_pair)));

  NodePtr expression = create_node(argument_halt);

  // Given: An EnvPtr to an empty Environment

  EnvPtr env = std::make_shared<Environment>(nullptr);

  // Given: An empty ValueRib

  ValueRib vr;

  // Given: An instance of the VM constructed with these items

  HeapVirtualMachine hvm(accumulator, expression, env, vr, nullptr);

  // When: You invoke the evaluate_assembly_instruction() method on hvm

  hvm.evaluate_assembly_instruction();

  // Then: The ValueRib register will hold the Symbol("banana");

  ASSERT_EQ(hvm.get_value_rib()[0]->get<Symbol>(), Symbol("banana"));

  // Then: The Expression register will hold the instruction (halt)

  ASSERT_EQ(hvm.get_expression()->get<DataPair>().car()->get<Symbol>(),
  Symbol("halt"));

  // When: You invoke the evaluate_assembly_instruction() method again

  hvm.evaluate_assembly_instruction();

  // Then: The accumulator register will hold the symbol 'banana

  ASSERT_EQ(hvm.get_accumulator()->get<Symbol>(), Symbol("banana"));

}

/**
 * @brief Test: evaluate_assembly_instruction() with (return) as exp
 */
TEST(HeapVirtualMachineUnitTest, evaluate_return) {

  // Given: An Accumulator containing the symbol 'finale

  Accumulator accumulator = create_node(Symbol("finale"));

  // Given: An assembly instruction of the form (return)

  Symbol ret("return");
  Data return_data(ret);
  DataPair return_pair(return_data);

  NodePtr expression = create_node(return_pair);

  // Given: An EnvPtr to an empty Environment

  EnvPtr env = std::make_shared<Environment>(nullptr);

  // Given: An empty ValueRib

  ValueRib vr;

  // Given: A CallFrame constructed as follows

  EnvPtr call_frame_env = std::make_shared<Environment>(nullptr);
  call_frame_env->set_value(Symbol("a"), create_node(String("Hello")));
  call_frame_env->set_value(Symbol("b"), create_node(String("World")));

  ValueRib call_frame_vr = {
      create_node(String("VR1")),
      create_node(String("VR2"))
  };

  Symbol halt("halt");
  Data halt_data(halt);
  DataPair halt_pair(halt_data);

  NodePtr call_frame_exp = create_node(halt_pair);

  FramePtr frame =
      std::make_shared<CallFrame>(call_frame_exp, call_frame_env,
                                  call_frame_vr, nullptr);

  // Given: An instance of the HVM constructed with these items

  HeapVirtualMachine hvm(accumulator, expression, env, vr, frame);

  // When: You invoke the evaluate_assembly_instruction() method on hvm

  hvm.evaluate_assembly_instruction();

  // Then: The HVM's Environment register will have the bindings for a & b

  ASSERT_EQ(hvm.get_environment()->get_value(Symbol("a"))->get<String>(),
  String("Hello"));

  ASSERT_EQ(hvm.get_environment()->get_value(Symbol("b"))->get<String>(),
  String("World"));

  // Then: The HVM's ValueRib register will contain "VR1" and "VR2"

  ASSERT_EQ(hvm.get_value_rib()[0]->get<String>(), String("VR1"));

  ASSERT_EQ(hvm.get_value_rib()[1]->get<String>(), String("VR2"));

  // Then: The HVM's ControlStack (FramePtr) register will be nullptr

  ASSERT_EQ(hvm.get_call_frame(), nullptr);

  // Then: The HVM's Expression register will contain (halt)

  ASSERT_EQ(hvm.get_expression()->get<DataPair>().car()->get<Symbol>(),
  Symbol("halt"));

  // When: You invoke the evaluate_assembly_instruction method again

  hvm.evaluate_assembly_instruction();

  // Then: The accumulator will hold the symbol 'finale

  ASSERT_EQ(hvm.get_accumulator()->get<Symbol>(), Symbol("finale"));

}

/**
 * @brief Test: evaluate_assembly_instruction() w/ (close vars body x) as expr
 */
TEST(HeapVirtualMachineUnitTest, evaluate_close) {

  // Given: An empty accumulator

  Accumulator acc = std::make_shared<Data>();

  // Given: An assembly instruction of the form...
  // (close (a) (refer a (halt)) (halt))

  Data close_data = shaka::Data(shaka::Symbol("close"));
  Data halt_data = shaka::Data(shaka::Symbol("halt"));
  DataPair halt_pair = shaka::DataPair(halt_data);
  Data symbol_a = shaka::Data(shaka::Symbol("a"));
  Data refer_data = shaka::Data(shaka::Symbol("refer"));

  DataPair a_halt_pair = shaka::DataPair(symbol_a,
                                         *core::list(create_node(halt_pair)));

  DataPair refer_a_halt = shaka::DataPair(
      refer_data,
      a_halt_pair
  );

  DataPair a_pair = shaka::DataPair(symbol_a);

  NodePtr expression = core::list(
      create_node(close_data),
      create_node(a_pair),
      create_node(refer_a_halt),
      create_node(halt_pair)
  );

  //std::cout << *expression << std::endl;

  // Given: An EnvPtr to an environment with a binding for [a : "hello"]
  EnvPtr env = std::make_shared<Environment>(nullptr);
  env->set_value(shaka::Symbol("a"), create_node(shaka::String("hello")));

  // Given: An empty value rib

  ValueRib vr;

  // Given: A null FramePtr

  FramePtr frame = nullptr;

  // Given: An instance of the HVM constructed with these items

  HeapVirtualMachine hvm(acc, expression, env, vr, frame);

  // When: You invoke the evaluate assembly instruction method on the hvm

  hvm.evaluate_assembly_instruction();

  // Then: The accumulator register will contain a new Closure object

  ASSERT_EQ(hvm.get_accumulator()->get_type(), shaka::Data::Type::CLOSURE);

  // Then: The closure will have a variable list with Symbol("a")

  ASSERT_EQ(
      hvm.get_accumulator()->get<Closure>().get_variable_list()[0],
      shaka::Symbol("a")
  );

  // Then: The closure's environment will have the top-level binding for 'a

  ASSERT_EQ(
      hvm.get_accumulator()->
          get<Closure>().get_environment()->get_value(shaka::Symbol("a"))
          ->get<String>(),
      shaka::String("hello")
  );

  // Then: The closure will have a function body that is (refer a (halt))

  hvm.set_expression(hvm.get_accumulator()->get<Closure>().get_function_body());

  hvm.evaluate_assembly_instruction();

  ASSERT_EQ(hvm.get_accumulator()->get<String>(), shaka::String("hello"));

}


/**
 * @brief Test: evaluate_assembly_instruction() with (conti x) as expr
 */
TEST(HeapVirtualMachineUnitTest, evaluate_conti) {

  // Given: An assembly instruction of the form (conti (halt))

  Data halt_data = Data(Symbol("halt"));
  Data conti_data = Data(Symbol("conti"));
  DataPair halt_pair = DataPair(halt_data);
  NodePtr expression = core::list(
      create_node(conti_data),
      create_node(halt_pair)
  );

  //std::cout << *expression << std::endl;

  // Given: An emtpy value rib

  ValueRib vr;

  // Given: A pointer to an empty environment

  EnvPtr env = std::make_shared<Environment>(nullptr);

  // Given: A pointer to a CallFrame constructed as follows

  EnvPtr call_frame_env = std::make_shared<Environment>(nullptr);
  call_frame_env->set_value(Symbol("a"), create_node(String("Hello")));
  call_frame_env->set_value(Symbol("b"), create_node(String("World")));

  ValueRib call_frame_vr = {
      create_node(String("VR1")),
      create_node(String("VR2"))
  };

  NodePtr call_frame_exp = create_node(halt_pair);

  FramePtr frame =
      std::make_shared<CallFrame>(call_frame_exp, call_frame_env,
                                  call_frame_vr, nullptr);

  // Given: An instance of the HeapVirtualMachine constructed with these items

  HeapVirtualMachine hvm(nullptr, expression, env, vr, frame);

  // When: You invoke the evaluate_assembly_instruction_method on the hvm

  hvm.evaluate_assembly_instruction();

  // Then: The accumulator will contain a continuation closure

  ASSERT_EQ(hvm.get_accumulator()->get_type(), shaka::Data::Type::CLOSURE);

  ASSERT_TRUE(hvm.get_accumulator()->get<Closure>().is_continuation_closure());

  // Then: The continuation will hold a reference to the CallFrame

  ASSERT_EQ(hvm.get_accumulator()->get<Closure>().get_call_frame(), frame);

  ASSERT_EQ(hvm.get_accumulator()->
      get<Closure>().get_call_frame()->
      get_environment_pointer()->get_value(Symbol("a"))->get<String>(),
            String("Hello"));

  // Then: The body of the continuation will be (nuate s kont_v000)

  ASSERT_EQ(hvm.get_accumulator()->
      get<Closure>().get_function_body()->get<DataPair>().car()->
            get<Symbol>(),
            Symbol("nuate")
  );

  ASSERT_EQ(hvm.get_accumulator()->
      get<Closure>().get_function_body()->get<DataPair>().cdr()->
            get<DataPair>().car()->
      get<CallFrame>().get_environment_pointer()->get_value(Symbol("b"))->
            get<String>(),
            String("World")
  );

  ASSERT_EQ(hvm.get_accumulator()->
            get<Closure>().get_function_body()->get<DataPair>().cdr()->
            get<DataPair>().cdr()->
            get<DataPair>().car()->get<Symbol>(),
            Symbol("kont_v000")
  );
}

/**
 * @brief Test: evaluate_assembly_instruction() with (apply) as expr
 */
TEST(HeapVirtualMachineUnitTest, eval_apply) {

  // Given: A native-closure to wrap the append method for strings

  Closure str_append(
      nullptr,
      nullptr,
      std::vector<Symbol>(0),
      std::make_shared<Callable>(string_append),
      nullptr,
      true
  );

  // Given: A function body of the form...
  // (refer s2 (argument (refer s1 (argument (refer string-append (apply))))))

  NodePtr apply = core::list(create_node(Data(Symbol("apply"))));
  NodePtr refer_string_append = core::list(
      create_node(Data(Symbol("refer"))),
      create_node(Data(Symbol("string-append"))),
      apply
  );

  NodePtr arg1 = core::list(
      create_node(Data(Symbol("argument"))),
      refer_string_append
  );

  NodePtr refer_s1 = core::list(
      create_node(Data(Symbol("refer"))),
      create_node(Data(Symbol("s1"))),
      arg1
  );

  NodePtr arg2 = core::list(
      create_node(Data(Symbol("argument"))),
      refer_s1
  );

  NodePtr func_body = core::list(
      create_node(Data(Symbol("refer"))),
      create_node(Data(Symbol("s2"))),
      arg2
  );

  //std::cout << *func_body << std::endl;

  // Given: A pointer to an environment that has a binding for string-append

  EnvPtr env = std::make_shared<Environment>(nullptr);
  env->set_value(Symbol("string-append"), create_node(str_append));



  // Given: A closure constructed with the above function body and environment


  Closure string_closure(
      env,
      func_body,
      std::vector<Symbol>{Symbol("s1"), Symbol("s2")},
      nullptr,
      nullptr,
      false
  );


  env->set_value(Symbol("my-procedure"), create_node(string_closure));


  // Given: An assembly instruction of the form...
  // (frame (args... apply) (return))

  Data frame_data(Symbol("frame"));
  Data string1_data(String("Hello"));
  Data string2_data(String("World"));
  Data constant_data(Symbol("constant"));
  Data return_data(Symbol("return"));
  Data apply_data(Symbol("apply"));
  Data argument_data(Symbol("argument"));
  Data procedure_data(Symbol("my-procedure"));
  Data refer_data(Symbol("refer"));

  NodePtr return_list = core::list(create_node(return_data));

  NodePtr args_apply_list = core::list(
      create_node(constant_data),
      create_node(string2_data),
      core::list(
          create_node(argument_data),
          core::list(
              create_node(constant_data),
              create_node(string1_data),
              core::list(
                  create_node(argument_data),
                  core::list(
                      create_node(refer_data),
                      create_node(procedure_data),
                      core::list(
                          create_node(apply_data)
                      )
                  )
              )
          )
      )
  );

  //std::cout << *args_apply_list << std::endl;

  NodePtr expression = core::list(
      create_node(frame_data),
      return_list,
      args_apply_list
  );

  //std::cout << *expression << std::endl;

  // Given: An empty ValueRib

  ValueRib vr;

  // Given: An instance of the HeapVirtualMachine constructed with these items

  HeapVirtualMachine hvm(nullptr, expression, env, vr, nullptr);

  // When: You invoke the evaluate assembly instruction method

  hvm.evaluate_assembly_instruction();

  // Then: A new call frame will have been created for the procedure call

  ASSERT_NE(hvm.get_call_frame(), nullptr);

  // Then: The call frame will have a return expression that is (return)

  ASSERT_EQ(
      hvm.get_call_frame()->
          get_next_expression()->get<DataPair>().car()->get<Symbol>(),
      Symbol("return")
  );

  // Then: The expression register of the VM will contain the (args..apply)

  ASSERT_EQ(
      hvm.get_expression()->get<DataPair>().car()->get<Symbol>(),
      Symbol("constant")
  );

  // When: You invoke the evaluate assembly instruction method again

  hvm.evaluate_assembly_instruction();

  // Then: The accumulator register will contain the string "World"

  ASSERT_EQ(hvm.get_accumulator()->get<String>(), String("World"));

  // When: You invoke the evaluate assembly instruction method again

  hvm.evaluate_assembly_instruction();

  // Then: The string "World" will have been moved into the value rib

  ASSERT_EQ(hvm.get_value_rib()[0]->get<String>(), String("World"));

  // When: You invoke the evaluate assembly instruction method again

  hvm.evaluate_assembly_instruction();

  // Then: The string "Hello" will have been placed in the accumulator

  ASSERT_EQ(hvm.get_accumulator()->get<String>(), String("Hello"));

  // When: You invoke the evaluate assembly instruction method again

  hvm.evaluate_assembly_instruction();

  // Then: The string "Hello" will have been moved to the value rib

  ASSERT_EQ(hvm.get_value_rib()[0]->get<String>(), String("Hello"));

  // When: You invoke the evaluate assembly instruction method again

  hvm.evaluate_assembly_instruction();

  // Then: The closure bound to "my-procedure" will be in the accumulator

  ASSERT_EQ(hvm.get_accumulator()->get_type(), shaka::Data::Type::CLOSURE);

  ASSERT_EQ(
      hvm.get_accumulator()->get<Closure>().get_variable_list()[0],
      Symbol("s1")
  );

  // When: You invoke the evaluate assembly instruction method again

  hvm.evaluate_assembly_instruction();


  // Then: The environment will have the bindings [s1 : "Hello", s2 : "World]

  ASSERT_EQ(
      hvm.get_environment()->get_value(Symbol("s1"))->get<String>(),
      String("Hello")
  );

  ASSERT_EQ(
      hvm.get_environment()->get_value(Symbol("s2"))->get<String>(),
      String("World")
  );

  // Then: The expression register should contain the body of my-procedure

  ASSERT_EQ( hvm.get_expression(), string_closure.get_function_body());

  // When: You evaluate the function body

  hvm.evaluate_assembly_instruction(); // refer s2
  hvm.evaluate_assembly_instruction(); // argument
  hvm.evaluate_assembly_instruction(); // refer s1
  hvm.evaluate_assembly_instruction(); // argument
  hvm.evaluate_assembly_instruction(); // refer string-append
  hvm.evaluate_assembly_instruction(); // apply

  // Then: The string "HelloWorld" is in the ValueRib

  ASSERT_EQ(hvm.get_value_rib()[0]->get<String>(), String("HelloWorld"));

}

/**
 * @brief Test: evaluate_assembly_instruction method with (nuate s var) as expr
 */
TEST(HeapVirtualMachineUnitTest, eval_nuate) {

  // Given: A closure that represents the procedure (lambda (k) (k 'a) 'b)

  EnvPtr env = std::make_shared<Environment>(nullptr);


  DataPair apply_pair(Data(Symbol("apply")));

  NodePtr refer_k_apply = core::list(
      create_node(Symbol("refer")),
      create_node(Symbol("k")),
      create_node(apply_pair)
  );

  DataPair a_rest(
      Data(Symbol("a")),
      *core::list(create_node(DataPair(Data(Symbol("argument")), *core::list
          (refer_k_apply))))
  );
  DataPair constant_a_rest(Data(Symbol("constant")), a_rest);

  NodePtr constant_b_halt = core::list(
      create_node(Symbol("constant")),
      create_node(Symbol("b")),
      core::list(create_node(Symbol("halt")))
  );

  NodePtr x = core::list(constant_b_halt,
                         create_node(constant_a_rest));

  DataPair func_body(Data(Symbol("frame")), *x);

  std::vector<Symbol> vars{Symbol("k")};

  Closure f(env, create_node(func_body), vars, nullptr, nullptr, false);

  std::cout << func_body << std::endl;

  // Given: An environment that has a binding for that Closure to 'f
  env->set_value(Symbol("f"), create_node(f));

  // Given: An assembly instruction of the form
  // (conti (argument (refer f (apply))))

  NodePtr expression = core::list(
      create_node(Symbol("conti")),
      core::list(
          create_node(Symbol("argument")),
          core::list(
              create_node(Symbol("refer")),
              create_node(Symbol("f")),
              create_node(DataPair(Data(Symbol("apply"))))
          )
      )
  );

  //std::cout << *expression << std::endl;

  // Given: An empty ValueRib

  ValueRib vr;

  // Given: A default constructed CallFrame

  FramePtr frame = std::make_shared<CallFrame>(
      core::list(create_node(Symbol("halt"))),
      env,
      vr,
      nullptr
  );

  // Given: An instance of the HeapVirtualMachine constructed with these items

  HeapVirtualMachine hvm(nullptr, expression, env, vr, frame);

  // When: You invoke the evaluate assembly instruction method

  hvm.evaluate_assembly_instruction();

  // Then: The accumulator register will contain a continuation closure

  ASSERT_EQ(hvm.get_accumulator()->get_type(), shaka::Data::Type::CLOSURE);

  ASSERT_TRUE(hvm.get_accumulator()->get<Closure>().is_continuation_closure());

  // Then: The expression register will have the expression...
  // (argument (refer f (apply)))

  ASSERT_EQ(
      hvm.get_expression()->get<DataPair>().car()->get<Symbol>(),
      Symbol("argument")
  );

  // When: You invoke the evaluate assembly instruction method through apply

  hvm.evaluate_assembly_instruction(); // argument
  hvm.evaluate_assembly_instruction(); // refer
  hvm.evaluate_assembly_instruction(); // apply

  // Then: The expression register will hold the function body of the Closure f

  ASSERT_EQ(hvm.get_expression(), f.get_function_body());

  // Then: The environment will hold a binding for the continuation to k

  ASSERT_EQ(
      hvm.get_environment()->get_value(Symbol("k"))->get_type(),
      shaka::Data::Type::CLOSURE
  );

  ASSERT_TRUE(
      hvm.get_environment()->get_value(Symbol("k"))->get<Closure>()
          .is_continuation_closure()
  );


  // When: You invoke the evaluate assembly instruction method

  hvm.evaluate_assembly_instruction();

  // Then: The expression register will contain...
  // (constant a (argument (refer k (apply))))

  ASSERT_EQ(
      hvm.get_expression()->get<DataPair>().car()->get<Symbol>(),
      Symbol("constant")
  );

  // When: You invoke the evaluate assembly instruction method until (apply)

  hvm.evaluate_assembly_instruction(); // constant a
  hvm.evaluate_assembly_instruction(); // argument
  hvm.evaluate_assembly_instruction(); // refer k
  hvm.evaluate_assembly_instruction(); // apply

  // Then: The environment will have a binding for [kont_v000 : a]
  ASSERT_EQ(
      hvm.get_environment()->get_value(Symbol("kont_v000"))->get<Symbol>(),
      Symbol("a")
  );

  // Then: The next expression will be (nuate s kont_v000)

  ASSERT_EQ(
      hvm.get_expression()->get<DataPair>().car()->get<Symbol>(),
      Symbol("nuate")
  );

  // When: You invoke the evaluate assembly instruction method again

  hvm.evaluate_assembly_instruction(); // nuate

  // Then: The symbol 'a will be in the accumulator

  ASSERT_EQ(
      hvm.get_accumulator()->get<Symbol>(),
      Symbol("a")
  );

  // Then: The expression register will contain the instruction (return)

  ASSERT_EQ(
      hvm.get_expression()->get<DataPair>().car()->get<Symbol>(),
      Symbol("return")
  );

  // Then: The top CallFrame on the stack will be the original frame

  ASSERT_EQ(
      hvm.get_call_frame()->get_next_expression()->get<DataPair>().car()
          ->get<Symbol>(), Symbol("halt")
  );



}

/**
 * @brief Test: The difference between standard closure vs. continuation
 */
TEST(HeapVirtualMachineUnitTest, closure_vs_continuation) {
  // Given: A closure that represents the procedure (lambda (k) (k 'a) 'b)

  EnvPtr env = std::make_shared<Environment>(nullptr);


  DataPair apply_pair(Data(Symbol("apply")));

  NodePtr refer_k_apply = core::list(
      create_node(Symbol("refer")),
      create_node(Symbol("k")),
      create_node(apply_pair)
  );

  DataPair a_rest(
      Data(Symbol("a")),
      *core::list(create_node(DataPair(Data(Symbol("argument")), *core::list
          (refer_k_apply))))
  );
  DataPair constant_a_rest(Data(Symbol("constant")), a_rest);

  NodePtr constant_b_halt = core::list(
      create_node(Symbol("constant")),
      create_node(Symbol("b")),
      core::list(create_node(Symbol("halt")))
  );

  NodePtr x = core::list(constant_b_halt,
                         create_node(constant_a_rest));

  DataPair func_body(Data(Symbol("frame")), *x);

  std::vector<Symbol> vars{Symbol("k")};

  Closure f(env, create_node(func_body), vars, nullptr, nullptr, false);

  //std::cout << func_body << std::endl;


  // Given: An environment that has a binding for that Closure to 'f
  env->set_value(Symbol("f"), create_node(f));

  // Given: A closure representing the identity procedure (lambda (x) x)

  NodePtr func_body_two = core::list(
      create_node(Symbol("refer")),
      create_node(Symbol("x")),
      core::list(create_node(Symbol("return")))
  );

  //std::cout << *func_body_two << std::endl;

  std::vector<Symbol> vars_two{Symbol("x")};
  Closure identity(env, func_body_two, vars_two, nullptr, nullptr, false);

  // Given: An environment binding for the identity closure to 'identity

  env->set_value(Symbol("identity"), create_node(identity));

  // Given: An assembly instruction of the form...
  // (refer identity (argument (refer f (apply))))

  Data refer(Symbol("refer"));
  Data id(Symbol("identity"));
  Data argument(Symbol("argument"));
  Data fsymbol(Symbol("f"));
  Data apply(Symbol("apply"));

  NodePtr expression = core::list(
      create_node(refer),
      create_node(id),
      core::list(
          create_node(argument),
          core::list(
              create_node(refer),
              create_node(fsymbol),
              core::list(
                  create_node(apply)
              )
          )
      )
  );

  //std::cout << *expression << std::endl;

  // Given: An empty ValueRib

  ValueRib vr;

  // Given: An instance of the HeapVirtualMachine constructed with these items

  HeapVirtualMachine hvm(nullptr, expression, env, vr, nullptr);

  // When: You invoke the evaluate assembly instruction method

  hvm.evaluate_assembly_instruction();

  // Then: The identity closure will be in the accumulator

  ASSERT_EQ(hvm.get_accumulator(), env->get_value(Symbol("identity")));

  // When: You invoke the evaluate assembly instruction method until apply

  hvm.evaluate_assembly_instruction(); // argument
  hvm.evaluate_assembly_instruction(); // refer f
  hvm.evaluate_assembly_instruction(); // apply

  // Then: The environment will have the binding [k : identity]

  ASSERT_EQ(
      hvm.get_environment()->get_value(Symbol("k")),
      env->get_value(Symbol("identity"))
  );

  // Then: The expression register will contain the body of f

  ASSERT_EQ(
      hvm.get_expression(), f.get_function_body()
  );

  // When: You invoke the evaluate_assembly_instruction() method until (apply)

  hvm.evaluate_assembly_instruction(); // frame

  // Then: The expression register will contain...
  // (constant a (argument (refer k (apply))))

  ASSERT_EQ(
    hvm.get_expression()->get<DataPair>().car()->get<Symbol>(),
    Symbol("constant")
  );

  // When: You invoke the evaluate_assembly_instruction method until (apply)

  hvm.evaluate_assembly_instruction(); // constant a
  hvm.evaluate_assembly_instruction(); // argument
  hvm.evaluate_assembly_instruction(); // refer k
  hvm.evaluate_assembly_instruction(); // apply

  // Then: The environment will have a binding for [x : 'a]

  ASSERT_EQ(
    hvm.get_environment()->get_value(Symbol("x"))->get<Symbol>(),
    Symbol("a")
  );

  // Then: The expression register will have (refer x (return))

  ASSERT_EQ(
    hvm.get_expression(), identity.get_function_body()
  );

  // When: You invoke the evaluate assembly instruction method through (return)

  hvm.evaluate_assembly_instruction(); // refer x
  hvm.evaluate_assembly_instruction(); // return

  // Then: The expression register will hold '(constant b (return))

  ASSERT_EQ(
    hvm.get_expression()->get<DataPair>().car()->get<Symbol>(),
    Symbol("constant")
  );

  // When: You invoke the evaluate assembly instruction method until (halt)

  hvm.evaluate_assembly_instruction(); // constant b
  hvm.evaluate_assembly_instruction(); // halt

  // Then: The symbol 'b will be in the accumulator

  ASSERT_EQ(
      hvm.get_accumulator()->get<Symbol>(),
      Symbol("b")
  );
}
