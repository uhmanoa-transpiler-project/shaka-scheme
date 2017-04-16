#include "core/proc/primitives.h"
#include <gtest/gtest.h>
#include <vector>
#include "core/base/NativeProcedure.h"
#include "core/base/Evaluator.h"
#include "core/eval/Define_impl.h"
#include "core/base/Data.h"
#include "core/base/DataNode.h"

using Args = std::vector<std::shared_ptr<shaka::DataNode>>;

TEST(variable, evaluator){
	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::Number num(2);
	env->set_value(shaka::Symbol("x"), num);
	auto l = std::make_shared<shaka::DataNode>(shaka::Symbol("x"));
	auto result = std::make_shared<shaka::DataNode>(shaka::Number(2));
	ASSERT_EQ(*(shaka::Evaluator(l, env).evaluate(shaka::eval::Variable())), 
		*result);


}

TEST(variable, variable_function){
	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::Number num(3);
	
	env->set_value(shaka::Symbol("x"), num);
	auto l = std::make_shared<shaka::DataNode>(shaka::Symbol("x"));
	auto R = std::make_shared<shaka::DataNode>(num);
	Args v;
	v.push_back(l);
	Args result = shaka::proc::variable(v, env);
	ASSERT_EQ(*(result[0]), *R );


}

TEST(variable, NativeProcedure_variable){
	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::Number num(3);
	env->set_value(shaka::Symbol("x"), num);
	auto l = std::make_shared<shaka::DataNode>(shaka::Symbol("x"));
	auto R = std::make_shared<shaka::DataNode>(num);
	Args v;
	v.push_back(l);
	shaka::NativeProcedure a(shaka::proc::variable, 2);
	Args result = a.call(v, env);
	ASSERT_EQ(*result[0], *R);


}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();

}


















