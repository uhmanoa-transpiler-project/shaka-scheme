#include <gtest/gtest.h>

#include "core/base/Core.h"
#include "core/eval/Proccall_impl.h"
#include "core/eval/Define_impl.h"
#include "core/eval/Eval.h"

#include <sstream>

using namespace shaka;

TEST(Proccall, initialization) {
    using namespace shaka;
    auto lambda_list = std::make_shared<DataNode>(DataNode::list(
        Symbol("lambda"),
        DataNode::list(Symbol("x")),
        Symbol("x")
    ));

    auto define_expr = std::make_shared<DataNode>(DataNode::list(
        Symbol("define"),
        Symbol("asdf")
    ));
    define_expr->append(*lambda_list);

    auto list = std::make_shared<DataNode>(DataNode::list(
        Symbol("define"),
        Symbol("asdf"),
	    DataNode(Number(1))
    ));

}

TEST(Proccall, multi_argument_lambda) {
	using namespace shaka;
	auto lambda_list = std::make_shared<DataNode>(DataNode::list(
		DataNode(Symbol("lambda")),
		DataNode::list(DataNode(Symbol("x")), DataNode(Symbol("y"))),
		DataNode::list(DataNode(Symbol("+")), DataNode(Symbol("x")), DataNode(Symbol("y")))
	));

	std::cout << *lambda_list << std::endl;	

	EnvPtr env = std::make_shared<shaka::Environment>(nullptr);
	env->set_value(Symbol("+"), make_node(NativeProcedure(stdproc::add, 1, true)));
	
	Evaluator lambda_evaluator(lambda_list->cdr(), env);
	
	auto proc = lambda_evaluator.evaluate(eval::Lambda());
	
	ASSERT_EQ(proc->is_procedure(), true);
	ASSERT_EQ(get<Procedure>(proc->get_data()).get_fixed_arity(), 2);
	ASSERT_EQ(get<Procedure>(proc->get_data()).is_variable_arity(), false);

	auto procedure_application_list = std::make_shared<DataNode>(DataNode::list(
		DataNode(proc),
		DataNode(Number(1)),
		DataNode(Number(2))
	));

	std::cout << *procedure_application_list << std::endl;

	Evaluator proccall_evaluator(procedure_application_list, env);

	auto result = proccall_evaluator.evaluate(eval::ProcCall());

	ASSERT_EQ(get<Number>(result->get_data()), Number(3));

}

TEST(Proccall, three_argument_lambda) {

	using namespace shaka;
	auto lambda_list = std::make_shared<DataNode>(DataNode::list(
		DataNode(Symbol("lambda")),
		DataNode::list(DataNode(Symbol("x")), DataNode(Symbol("y")), DataNode(Symbol("z"))),
		DataNode::list(DataNode(Symbol("+")), DataNode(Symbol("x")), DataNode(Symbol("y")),
			DataNode(Symbol("z")))
	));

	std::cout << *lambda_list << std::endl;	

	EnvPtr env = std::make_shared<shaka::Environment>(nullptr);
	env->set_value(Symbol("+"), make_node(NativeProcedure(stdproc::add, 1, true)));
	
	Evaluator lambda_evaluator(lambda_list->cdr(), env);
	
	auto proc = lambda_evaluator.evaluate(eval::Lambda());
	
	ASSERT_EQ(proc->is_procedure(), true);
	ASSERT_EQ(get<Procedure>(proc->get_data()).get_fixed_arity(), 3);
	ASSERT_EQ(get<Procedure>(proc->get_data()).is_variable_arity(), false);

	auto procedure_application_list = std::make_shared<DataNode>(DataNode::list(
		DataNode(proc),
		DataNode(Number(1)),
		DataNode(Number(2)),
		DataNode(Number(3))
	));

	std::cout << *procedure_application_list << std::endl;

	Evaluator proccall_evaluator(procedure_application_list, env);

	auto result = proccall_evaluator.evaluate(eval::ProcCall());

	ASSERT_EQ(get<Number>(result->get_data()), Number(6));

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
