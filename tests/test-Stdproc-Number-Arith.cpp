#include <gtest/gtest.h>
#include "stdproc/Numbers_Arithmetic_impl.h"

TEST(Numbers_Arithmetic_impl, add_numbers_f) {
    using namespace shaka::stdproc;

	shaka::stdproc::Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(10));
	shaka::stdproc::Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(10));

	shaka::stdproc::Args args;
	args.push_back(v1);
	args.push_back(v2);

	shaka::stdproc::Args result = add_numbers_f(args);

	ASSERT_EQ(result.size(), 1);

	ASSERT_EQ(shaka::Number(30), shaka::get<shaka::Number>(*result[0]->get_data()));

}

TEST(Numbers_Arithmetic_impl, add_numbers_f2) {
    using namespace shaka::stdproc;

	shaka::stdproc::Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(1));
	shaka::stdproc::Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(2));
	shaka::stdproc::Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(3));
	shaka::stdproc::Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(4));

	shaka::stdproc::Args args = {v1, v2, v3, v4};
	
	shaka::stdproc::Args result = add_numbers_f(args);

	ASSERT_EQ(shaka::Number(10), shaka::get<shaka::Number>(*result[0]->get_data()));
}

TEST(Numbers_Arithmetic_impl, mul_numbers_f) {
    using namespace shaka::stdproc;

	shaka::stdproc::Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(1));
	shaka::stdproc::Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(2));
	shaka::stdproc::Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(3));
	shaka::stdproc::Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(4));

	shaka::stdproc::Args args = {v1, v2, v3, v4};

	shaka::stdproc::Args result = mul_numbers_f(args);

	ASSERT_EQ(shaka::Number(24), shaka::get<shaka::Number>(*result[0]->get_data()));
}

TEST(Numbers_Arithmetic_impl, neg_numbers_f) {
    using namespace shaka::stdproc;

	shaka::stdproc::Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(22));

	shaka::stdproc::Args args = {v1};

	shaka::stdproc::Args result = neg_numbers_f(args);

	ASSERT_EQ(shaka::Number(-22), shaka::get<shaka::Number>(*result[0]->get_data()));

}

TEST(Numbers_Arithmetic_impl, sub_numbers_f) {
    using namespace shaka::stdproc;

	shaka::stdproc::Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(100));
	shaka::stdproc::Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(50));
	shaka::stdproc::Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(25));
	shaka::stdproc::Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(5));

	shaka::stdproc::Args args = {v1, v2, v3, v4};

	shaka::stdproc::Args result = sub_numbers_f(args);

	ASSERT_EQ(shaka::Number(20), shaka::get<shaka::Number>(*result[0]->get_data()));

}

TEST(Numbers_Arithmetic_impl, reciprocal_numbers_f) {
    using namespace shaka::stdproc;

	shaka::stdproc::Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(1, 2));
	shaka::stdproc::Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(3)   );
	shaka::stdproc::Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(0.5) );

	shaka::stdproc::Args args1 = {v1};
	shaka::stdproc::Args args2 = {v2};
	shaka::stdproc::Args args3 = {v3};

	shaka::stdproc::Args result1 = reciprocal_numbers_f(args1);
	shaka::stdproc::Args result2 = reciprocal_numbers_f(args2);
	shaka::stdproc::Args result3 = reciprocal_numbers_f(args3);

	ASSERT_EQ(shaka::Number(2), shaka::get<shaka::Number>(*result1[0]->get_data()));
	ASSERT_EQ(shaka::Number(1, 3), shaka::get<shaka::Number>(*result2[0]->get_data()));
	ASSERT_EQ(shaka::Number(2.0), shaka::get<shaka::Number>(*result3[0]->get_data()));

}

TEST(Numbers_Arithmetic_impl, div_numbers_f) {
    using namespace shaka::stdproc;

	shaka::stdproc::Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(20));
	shaka::stdproc::Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(10));
	shaka::stdproc::Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(5) );

	shaka::stdproc::Args args = {v1, v2, v3};

	shaka::stdproc::Args result = div_numbers_f(args);

	ASSERT_EQ(shaka::Number(2, 5), shaka::get<shaka::Number>(*result[0]->get_data()));

}


int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
