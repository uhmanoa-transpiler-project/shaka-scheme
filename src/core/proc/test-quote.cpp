#include "core/proc/primitives.h"
#include <gtest/gtest.h>
#include <vector>
#include "core/base/NativeProcedure.h"
#include "core/base/Evaluator.h"
#include "core/eval/Define_impl.h"
#include "core/eval/Quote_impl.h"
#include "core/base/Data.h"
#include "core/base/DataNode.h"

using Args = std::vector<std::shared_ptr<shaka::DataNode>>;

TEST(quote, evaluator){
	auto env = std::make_shared<shaka::Environment>(nullptr);
	auto l = std::make_shared<shaka::DataNode>(shaka::DataNode::list(
				shaka::Symbol("quote"),
				shaka::DataNode::list(
				shaka::Symbol("define"),
				shaka::Symbol("x"),
				shaka::Number(1))));
	auto result = std::make_shared<shaka::DataNode>(shaka::DataNode::list(
					shaka::Symbol("define"),
					shaka::Symbol("x"),
					shaka::Number(1)));
	auto actual_result = shaka::Evaluator(l, env).evaluate(shaka::eval::Quote());
	ASSERT_EQ(*actual_result, *result);


}

TEST(define, quote_function){
	auto env = std::make_shared<shaka::Environment>(nullptr);
	auto l = std::make_shared<shaka::DataNode>(shaka::DataNode::list(
				shaka::Symbol("quote"),
				shaka::DataNode::list(
				shaka::Symbol("define"),
				shaka::Symbol("x"),
				shaka::Number(1))));

	auto R =  shaka::DataNode::list(
				shaka::Symbol("define"),
				shaka::Symbol("x"),
				shaka::Number(1));

	Args v;
	v.push_back(l);
	Args result = shaka::proc::quote(v, env);
	ASSERT_EQ(*result[0], R);


}

TEST(define, NativeProcedure_quote){
	auto env = std::make_shared<shaka::Environment>(nullptr);
	auto l = std::make_shared<shaka::DataNode>(shaka::DataNode::list(
				shaka::Symbol("quote"),
				shaka::DataNode::list(
				shaka::Symbol("define"),
				shaka::Symbol("x"),
				shaka::Number(1))));
	auto R = shaka::DataNode::list(
				shaka::Symbol("define"),
				shaka::Symbol("x"),
				shaka::Number(1));

	Args v;
	v.push_back(l);
	shaka::NativeProcedure a(shaka::proc::quote, 2);
	Args result = a.call(v, env);
	ASSERT_EQ(*result[0], R);


}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();

}


















