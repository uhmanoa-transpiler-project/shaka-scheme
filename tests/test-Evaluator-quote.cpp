#include "gtest/gtest.h"

#include "DataNode.h"
#include "Environment.h"
#include "Evaluator.h"
#include "Procedure.h"

#include "Eval_Quote.h"

#include "Eval_Expression_impl.h"

using Data = shaka::Data;
using DataTree = shaka::DataNode<Data>;
using IDataTree = shaka::IDataNode<Data>;

using Environment = shaka::Environment<shaka::Symbol, std::shared_ptr<IDataTree>>;

TEST(Quote, initialize_and_test_quote){
	std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::QUOTE);

	std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);
	root->push_child(shaka::Symbol("a"));

	// /* constructing evaluator */
	shaka::Evaluator evaluator(root, env);

	auto result = evaluator.evaluate(shaka::eval::Quote());

	ASSERT_EQ(shaka::Symbol("a"), shaka::get<shaka::Symbol>(*result->get_data()));

}

int main(int argc, char* argv[]) {

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
