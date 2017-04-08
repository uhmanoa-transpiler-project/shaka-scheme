#include <gtest/gtest.h>
#include "stdproc/Numbers_Arithmetic_impl.h"

TEST(Numbers_Arithmetic_impl, add_numbers_f) {
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>();
	v1->set_data(shaka::Number(10));
	v2->set_data(shaka::Number(20));

	Args args;
	args.push_back(v1);
	args.push_back(v2);

	Args result = add_numbers_f(args);

	ASSERT_EQ(result.size(), 1);

	ASSERT_EQ(shaka::Number(30), shaka::get<shaka::Number>(*result[0]->get_data()));

}

TEST(Numbers_Arithmetic_impl, add_numbers_f2) {
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>();

	v1->set_data(shaka::Number(1));
	v2->set_data(shaka::Number(2));
	v3->set_data(shaka::Number(3));
	v4->set_data(shaka::Number(4));

	Args args = {v1, v2, v3, v4};
	
	Args result = add_numbers_f(args);

	ASSERT_EQ(shaka::Number(10), shaka::get<shaka::Number>(*result[0]->get_data()));
}

TEST(Numbers_Arithmetic_impl, mul_numbers_f) {
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>();

	v1->set_data(shaka::Number(1));
	v2->set_data(shaka::Number(2));
	v3->set_data(shaka::Number(3));
	v4->set_data(shaka::Number(4));

	Args args = {v1, v2, v3, v4};

	Args result = mul_numbers_f(args);

	ASSERT_EQ(shaka::Number(24), shaka::get<shaka::Number>(*result[0]->get_data()));
}

TEST(Numbers_Arithmetic_impl, neg_numbers_f) {
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>();

	v1->set_data(shaka::Number(22));

	Args args = {v1};

	Args result = neg_numbers_f(args);

	ASSERT_EQ(shaka::Number(-22), shaka::get<shaka::Number>(*result[0]->get_data()));

}

TEST(Numbers_Arithmetic_impl, sub_numbers_f) {
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>();

	v1->set_data(shaka::Number(100));
	v2->set_data(shaka::Number(50));
	v3->set_data(shaka::Number(25));
	v4->set_data(shaka::Number(5));

	Args args = {v1, v2, v3, v4};

	Args result = sub_numbers_f(args);

	ASSERT_EQ(shaka::Number(20), shaka::get<shaka::Number>(*result[0]->get_data()));

}

TEST(Numbers_Arithmetic_impl, reciprocal_numbers_f) {
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>();

	v1->set_data(shaka::Number(1, 2));
	v2->set_data(shaka::Number(3));
	v3->set_data(shaka::Number(0.5));

	Args args1 = {v1};
	Args args2 = {v2};
	Args args3 = {v3};

	Args result1 = reciprocal_numbers_f(args1);
	Args result2 = reciprocal_numbers_f(args2);
	Args result3 = reciprocal_numbers_f(args3);

	ASSERT_EQ(shaka::Number(2), shaka::get<shaka::Number>(*result1[0]->get_data()));
	ASSERT_EQ(shaka::Number(1, 3), shaka::get<shaka::Number>(*result2[0]->get_data()));
	ASSERT_EQ(shaka::Number(2.0), shaka::get<shaka::Number>(*result3[0]->get_data()));

}

TEST(Numbers_Arithmetic_impl, div_numbers_f) {
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>();

	v1->set_data(shaka::Number(20));
	v2->set_data(shaka::Number(10));
	v3->set_data(shaka::Number(5));

	Args args = {v1, v2, v3};

	Args result = div_numbers_f(args);

	ASSERT_EQ(shaka::Number(2, 5), shaka::get<shaka::Number>(*result[0]->get_data()));

}

TEST(Numbers_Arithmetic_impl, abs_numbers_f) {
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>();

	v1->set_data(shaka::Number(-5));
	v2->set_data(shaka::Number(20));
	v3->set_data(shaka::Number(-3, 4));
	v4->set_data(shaka::Number(-1, -2));

	Args args = {v1};
	Args result = abs_numbers_f(args);

	Args args2 = {v2};
	Args result2 = abs_numbers_f(args2);

	Args args3 = {v3};
	Args result3 = abs_numbers_f(args3);
	
	Args args4 = {v4};
	Args result4 = abs_numbers_f(args4);

	ASSERT_EQ(shaka::Number(5), shaka::get<shaka::Number>(*result[0]->get_data()));
	ASSERT_EQ(shaka::Number(20), shaka::get<shaka::Number>(*result2[0]->get_data()));
	ASSERT_EQ(shaka::Number(3, 4), shaka::get<shaka::Number>(*result3[0]->get_data()));
	ASSERT_EQ(shaka::Number(1, 2), shaka::get<shaka::Number>(*result4[0]->get_data()));
}

TEST(Numbers_Arithmetic_impl, floor_div_numbers_f) {
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>();
	
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>();

	Value v5 = std::make_shared<shaka::DataNode<shaka::Data>>();

	v1->set_data(shaka::Number(5));
	v2->set_data(shaka::Number(2));

	v3->set_data(shaka::Number(-5));
	v4->set_data(shaka::Number(2));
	
	v5->set_data(shaka::Number(-2));

	Args args = {v1, v2};
	Args args2 = {v3, v4};
	Args args3 = {v1, v5};
	Args args4 = {v3, v5}; 

	Args result = floor_div_numbers_f(args);
	Args result2 = floor_div_numbers_f(args2);
	Args result3 = floor_div_numbers_f(args3);
	Args result4 = floor_div_numbers_f(args4);

	ASSERT_EQ(shaka::Number(2), shaka::get<shaka::Number>(*result[0]->get_data()));
	ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*result[1]->get_data()));

	ASSERT_EQ(shaka::Number(-3), shaka::get<shaka::Number>(*result2[0]->get_data()));
	ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*result2[1]->get_data()));
	
	ASSERT_EQ(shaka::Number(-3), shaka::get<shaka::Number>(*result3[0]->get_data()));
	ASSERT_EQ(shaka::Number(-1), shaka::get<shaka::Number>(*result3[1]->get_data()));
	
	ASSERT_EQ(shaka::Number(2), shaka::get<shaka::Number>(*result4[0]->get_data()));
	ASSERT_EQ(shaka::Number(-1), shaka::get<shaka::Number>(*result4[1]->get_data()));
}

TEST(Numbers_Arithmetic_impl, floor_quotient_numbers_f) {
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>();

	v1->set_data(shaka::Number(5));
	v2->set_data(shaka::Number(2));
	v3->set_data(shaka::Number(-5));
	v4->set_data(shaka::Number(-2));

	Args args1 = {v1, v2};
	Args args2 = {v3, v2};
	Args args3 = {v1, v4};
	Args args4 = {v3, v4};

	Args result1 = floor_quotient_numbers_f(args1);
	Args result2 = floor_quotient_numbers_f(args2);
	Args result3 = floor_quotient_numbers_f(args3);
	Args result4 = floor_quotient_numbers_f(args4);

	ASSERT_EQ(shaka::Number(2), shaka::get<shaka::Number>(*result1[0]->get_data()));
	ASSERT_EQ(shaka::Number(-3), shaka::get<shaka::Number>(*result2[0]->get_data()));
	ASSERT_EQ(shaka::Number(-3), shaka::get<shaka::Number>(*result3[0]->get_data()));
	ASSERT_EQ(shaka::Number(2), shaka::get<shaka::Number>(*result4[0]->get_data()));

}


TEST(Numbers_Arithmetic_impl, floor_remainder_numbers_f) {
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>();

	v1->set_data(shaka::Number(5));
	v2->set_data(shaka::Number(2));
	v3->set_data(shaka::Number(-5));
	v4->set_data(shaka::Number(-2));

	Args args1 = {v1, v2};
	Args args2 = {v3, v2};
	Args args3 = {v1, v4};
	Args args4 = {v3, v4};

	Args result1 = floor_remainder_numbers_f(args1);
	Args result2 = floor_remainder_numbers_f(args2);
	Args result3 = floor_remainder_numbers_f(args3);
	Args result4 = floor_remainder_numbers_f(args4);

	ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*result1[0]->get_data()));
	ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*result2[0]->get_data()));
	ASSERT_EQ(shaka::Number(-1), shaka::get<shaka::Number>(*result3[0]->get_data()));
	ASSERT_EQ(shaka::Number(-1), shaka::get<shaka::Number>(*result4[0]->get_data()));

}


TEST(Numbers_Arithmetic_impl, truncate_div_numbers_f) {
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>();

	v1->set_data(shaka::Number(5));
	v2->set_data(shaka::Number(2));
	v3->set_data(shaka::Number(-5));
	v4->set_data(shaka::Number(-2));

	Args args1 = {v1, v2};
	Args args2 = {v3, v2};
	Args args3 = {v1, v4};
	Args args4 = {v3, v4};

	Args result1 = truncate_div_numbers_f(args1);
	Args result2 = truncate_div_numbers_f(args2);
	Args result3 = truncate_div_numbers_f(args3);
	Args result4 = truncate_div_numbers_f(args4);

	ASSERT_EQ(shaka::Number(2), shaka::get<shaka::Number>(*result1[0]->get_data()));
	ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*result1[1]->get_data()));

	ASSERT_EQ(shaka::Number(-2), shaka::get<shaka::Number>(*result2[0]->get_data()));
	ASSERT_EQ(shaka::Number(-1), shaka::get<shaka::Number>(*result2[1]->get_data()));

	ASSERT_EQ(shaka::Number(-2), shaka::get<shaka::Number>(*result3[0]->get_data()));
	ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*result3[1]->get_data()));

	ASSERT_EQ(shaka::Number(2), shaka::get<shaka::Number>(*result4[0]->get_data()));
	ASSERT_EQ(shaka::Number(-1), shaka::get<shaka::Number>(*result4[1]->get_data()));

}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
