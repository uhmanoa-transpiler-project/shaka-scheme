#include <gtest/gtest.h>
#include <vector>

#include "core/base/Core.h"
#include "core/base/NativeProcedure.h"
#include "core/base/Evaluator.h"
#include "core/eval/Define_impl.h"

#include "core/proc/primitives.h"

using Args = std::vector<std::shared_ptr<shaka::DataNode>>;

TEST(define, evaluator){
	auto env = std::make_shared<shaka::Environment>(nullptr);
	auto l = std::make_shared<shaka::DataNode>(shaka::DataNode::list(
				shaka::Symbol("define"),
				shaka::Symbol("x"),
				shaka::Number(1)));
	Args v;
	v.push_back(l);
	ASSERT_EQ(shaka::Evaluator(l, env).evaluate(shaka::eval::Define()), 
			nullptr);

	ASSERT_EQ((shaka::get<shaka::Number>(env->get_value(shaka::Symbol("x")))), shaka::Number(1)); 

}

TEST(define, define_function){
	auto env = std::make_shared<shaka::Environment>(nullptr);
	auto l = std::make_shared<shaka::DataNode>(shaka::DataNode::list(
				shaka::Symbol("define"),
				shaka::Symbol("x"),
				shaka::Number(1)));
	Args v;
	v.push_back(l);
	Args result = shaka::proc::define(v, env);
	ASSERT_EQ(result[0], nullptr);

	ASSERT_EQ((shaka::get<shaka::Number>(env->get_value(shaka::Symbol("x")))), shaka::Number(1)); 

}

TEST(define, NativeProcedure_define){
	auto env = std::make_shared<shaka::Environment>(nullptr);
	auto l = std::make_shared<shaka::DataNode>(shaka::DataNode::list(
				shaka::Symbol("define"),
				shaka::Symbol("x"),
				shaka::Number(1)));
	Args v;
	v.push_back(l);
	shaka::NativeProcedure a(shaka::proc::define, 2);
	Args result = a.call(v, env);
	ASSERT_EQ(result[0], nullptr);
	ASSERT_EQ((shaka::get<shaka::Number>(env->get_value(shaka::Symbol("x")))), shaka::Number(1)); 


}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();

}


















