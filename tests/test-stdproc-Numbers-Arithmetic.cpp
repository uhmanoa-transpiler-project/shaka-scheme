#include <gtest/gtest.h>
#include "stdproc/Numbers_Arithmetic_impl.h"

TEST(Numbers_Arithmetic_impl, add_numbers_f) {
    using namespace shaka::stdproc;

	shaka::stdproc::Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(10));
	shaka::stdproc::Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(10));

	shaka::stdproc::Args args;
	args.push_back(v1);
	args.push_back(v2);

	shaka::stdproc::Args result = add(args);

	ASSERT_EQ(result.size(), 1);

	ASSERT_EQ(shaka::Number(20), shaka::get<shaka::Number>(*result[0]->get_data()));

}

TEST(Numbers_Arithmetic_impl, add_numbers_f2) {
    using namespace shaka::stdproc;

	shaka::stdproc::Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(1));
	shaka::stdproc::Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(2));
	shaka::stdproc::Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(3));
	shaka::stdproc::Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(4));

	shaka::stdproc::Args args = {v1, v2, v3, v4};
	
	shaka::stdproc::Args result = add(args);

	ASSERT_EQ(shaka::Number(10), shaka::get<shaka::Number>(*result[0]->get_data()));
}

TEST(Numbers_Arithmetic_impl, mul_numbers_f) {
    using namespace shaka::stdproc;

	shaka::stdproc::Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(1));
	shaka::stdproc::Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(2));
	shaka::stdproc::Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(3));
	shaka::stdproc::Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(4));

	shaka::stdproc::Args args = {v1, v2, v3, v4};

	shaka::stdproc::Args result = mul(args);

	ASSERT_EQ(shaka::Number(24), shaka::get<shaka::Number>(*result[0]->get_data()));
}

TEST(Numbers_Arithmetic_impl, neg_numbers_f) {
    using namespace shaka::stdproc;

	shaka::stdproc::Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(22));

	shaka::stdproc::Args args = {v1};

	shaka::stdproc::Args result = neg(args);

	ASSERT_EQ(shaka::Number(-22), shaka::get<shaka::Number>(*result[0]->get_data()));

}

TEST(Numbers_Arithmetic_impl, sub_numbers_f) {
    using namespace shaka::stdproc;

	shaka::stdproc::Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(100));
	shaka::stdproc::Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(50));
	shaka::stdproc::Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(25));
	shaka::stdproc::Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(5));

	shaka::stdproc::Args args = {v1, v2, v3, v4};

	shaka::stdproc::Args result = sub(args);

	ASSERT_EQ(shaka::Number(20), shaka::get<shaka::Number>(*result[0]->get_data()));

}

TEST(Numbers_Arithmetic_impl, reciprocal_numbers_f) {
    using namespace shaka::stdproc;

	shaka::stdproc::Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(1, 2));
	shaka::stdproc::Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(3));
	shaka::stdproc::Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(0.5) );

	shaka::stdproc::Args args1 = {v1};
	shaka::stdproc::Args args2 = {v2};
	shaka::stdproc::Args args3 = {v3};

	shaka::stdproc::Args result1 = reciprocal(args1);
	shaka::stdproc::Args result2 = reciprocal(args2);
	shaka::stdproc::Args result3 = reciprocal(args3);

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

	shaka::stdproc::Args result = shaka::stdproc::div(args);

	ASSERT_EQ(shaka::Number(2, 5), shaka::get<shaka::Number>(*result[0]->get_data()));

}



TEST(Numbers_Arithmetic_impl, abs_numbers_f) {
	using namespace shaka::stdproc;
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(-5));
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(20));
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(-3, 4));
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(-1, -2));

	Args args = {v1};
	Args result = shaka::stdproc::abs(args);

	Args args2 = {v2};
	Args result2 = shaka::stdproc::abs(args2);

	Args args3 = {v3};
	Args result3 = shaka::stdproc::abs(args3);
	
	Args args4 = {v4};
	Args result4 = shaka::stdproc::abs(args4);

	ASSERT_EQ(shaka::Number(5), shaka::get<shaka::Number>(*result[0]->get_data()));
	ASSERT_EQ(shaka::Number(20), shaka::get<shaka::Number>(*result2[0]->get_data()));
	ASSERT_EQ(shaka::Number(3, 4), shaka::get<shaka::Number>(*result3[0]->get_data()));
	ASSERT_EQ(shaka::Number(1, 2), shaka::get<shaka::Number>(*result4[0]->get_data()));
}

TEST(Numbers_Arithmetic_impl, floor_div_numbers_f) {
	using namespace shaka::stdproc;
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(5));
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(2));
	
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(-5));
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(2));

	Value v5 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(-2));

	Args args = {v1, v2};
	Args args2 = {v3, v4};
	Args args3 = {v1, v5};
	Args args4 = {v3, v5};	

	Args result = floor_div(args);
	Args result2 = floor_div(args2);
	Args result3 = floor_div(args3);
	Args result4 = floor_div(args4);

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
	using namespace shaka::stdproc;
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(5));
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(2));
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(-5));
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(-2));

	Args args1 = {v1, v2};
	Args args2 = {v3, v2};
	Args args3 = {v1, v4};
	Args args4 = {v3, v4};

	Args result1 = floor_quotient(args1);
	Args result2 = floor_quotient(args2);
	Args result3 = floor_quotient(args3);
	Args result4 = floor_quotient(args4);

	ASSERT_EQ(shaka::Number(2), shaka::get<shaka::Number>(*result1[0]->get_data()));
	ASSERT_EQ(shaka::Number(-3), shaka::get<shaka::Number>(*result2[0]->get_data()));
	ASSERT_EQ(shaka::Number(-3), shaka::get<shaka::Number>(*result3[0]->get_data()));
	ASSERT_EQ(shaka::Number(2), shaka::get<shaka::Number>(*result4[0]->get_data()));

}


TEST(Numbers_Arithmetic_impl, floor_remainder_numbers_f) {
	using namespace shaka::stdproc;

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(5));
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(2));
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(-5));
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(-2));

	Args args1 = {v1, v2};
	Args args2 = {v3, v2};
	Args args3 = {v1, v4};
	Args args4 = {v3, v4};

	Args result1 = floor_remainder(args1);
	Args result2 = floor_remainder(args2);
	Args result3 = floor_remainder(args3);
	Args result4 = floor_remainder(args4);

	ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*result1[0]->get_data()));
	ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*result2[0]->get_data()));
	ASSERT_EQ(shaka::Number(-1), shaka::get<shaka::Number>(*result3[0]->get_data()));
	ASSERT_EQ(shaka::Number(-1), shaka::get<shaka::Number>(*result4[0]->get_data()));

}


TEST(Numbers_Arithmetic_impl, truncate_div_numbers_f) {
	using namespace shaka::stdproc;

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(5));
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(2));
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(-5));
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(-2));

	Args args1 = {v1, v2};
	Args args2 = {v3, v2};
	Args args3 = {v1, v4};
	Args args4 = {v3, v4};

	Args result1 = truncate_div(args1);
	Args result2 = truncate_div(args2);
	Args result3 = truncate_div(args3);
	Args result4 = truncate_div(args4);

	ASSERT_EQ(shaka::Number(2), shaka::get<shaka::Number>(*result1[0]->get_data()));
	ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*result1[1]->get_data()));

	ASSERT_EQ(shaka::Number(-2), shaka::get<shaka::Number>(*result2[0]->get_data()));
	ASSERT_EQ(shaka::Number(-1), shaka::get<shaka::Number>(*result2[1]->get_data()));

	ASSERT_EQ(shaka::Number(-2), shaka::get<shaka::Number>(*result3[0]->get_data()));
	ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*result3[1]->get_data()));

	ASSERT_EQ(shaka::Number(2), shaka::get<shaka::Number>(*result4[0]->get_data()));
	ASSERT_EQ(shaka::Number(-1), shaka::get<shaka::Number>(*result4[1]->get_data()));

}


TEST(Numbers_Arithmetic_impl, truncate_quotient_numbers_f) {
	using namespace shaka::stdproc;

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(5));
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(2));
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(-5));
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(-2));

	Args args1 = {v1, v2};
	Args args2 = {v3, v2};
	Args args3 = {v1, v4};
	Args args4 = {v3, v4};

	Args result1 = truncate_quotient(args1);
	Args result2 = truncate_quotient(args2);
	Args result3 = truncate_quotient(args3);
	Args result4 = truncate_quotient(args4);

	ASSERT_EQ(shaka::Number(2), shaka::get<shaka::Number>(*result1[0]->get_data()));

	ASSERT_EQ(shaka::Number(-2), shaka::get<shaka::Number>(*result2[0]->get_data()));

	ASSERT_EQ(shaka::Number(-2), shaka::get<shaka::Number>(*result3[0]->get_data()));

	ASSERT_EQ(shaka::Number(2), shaka::get<shaka::Number>(*result4[0]->get_data()));

}


TEST(Numbers_Arithmetic_impl, truncate_remainder_numbers_f) {
	using namespace shaka::stdproc;

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(5));
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(2));
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(-5));
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(-2));

	Args args1 = {v1, v2};
	Args args2 = {v3, v2};
	Args args3 = {v1, v4};
	Args args4 = {v3, v4};

	Args result1 = truncate_remainder(args1);
	Args result2 = truncate_remainder(args2);
	Args result3 = truncate_remainder(args3);
	Args result4 = truncate_remainder(args4);

	ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*result1[0]->get_data()));

	ASSERT_EQ(shaka::Number(-1), shaka::get<shaka::Number>(*result2[0]->get_data()));

	ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*result3[0]->get_data()));

	ASSERT_EQ(shaka::Number(-1), shaka::get<shaka::Number>(*result4[0]->get_data()));

}

TEST(Numbers_Arithmetic_impl, quotient_numbers_f) {
	using namespace shaka::stdproc;

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(5));
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(2));
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(-5));
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(-2));

	Args args1 = {v1, v2};
	Args args2 = {v3, v2};
	Args args3 = {v1, v4};
	Args args4 = {v3, v4};

	Args result1 = quotient(args1);
	Args result2 = quotient(args2);
	Args result3 = quotient(args3);
	Args result4 = quotient(args4);

	ASSERT_EQ(shaka::Number(2), shaka::get<shaka::Number>(*result1[0]->get_data()));

	ASSERT_EQ(shaka::Number(-2), shaka::get<shaka::Number>(*result2[0]->get_data()));

	ASSERT_EQ(shaka::Number(-2), shaka::get<shaka::Number>(*result3[0]->get_data()));

	ASSERT_EQ(shaka::Number(2), shaka::get<shaka::Number>(*result4[0]->get_data()));

}

TEST(Numbers_Arithmetic_impl, remainder_numbers_f) {
	using namespace shaka::stdproc;

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(5));
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(2));
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(-5));
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(-2));

	Args args1 = {v1, v2};
	Args args2 = {v3, v2};
	Args args3 = {v1, v4};
	Args args4 = {v3, v4};

	Args result1 = shaka::stdproc::remainder(args1);
	Args result2 = shaka::stdproc::remainder(args2);
	Args result3 = shaka::stdproc::remainder(args3);
	Args result4 = shaka::stdproc::remainder(args4);

	ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*result1[0]->get_data()));

	ASSERT_EQ(shaka::Number(-1), shaka::get<shaka::Number>(*result2[0]->get_data()));

	ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*result3[0]->get_data()));

	ASSERT_EQ(shaka::Number(-1), shaka::get<shaka::Number>(*result4[0]->get_data()));

}

TEST(Numbers_Arithmetic_impl, modulo_numbers_f) {
	using namespace shaka::stdproc;

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(5));
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(2));
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(-5));
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(-2));

	Args args1 = {v1, v2};
	Args args2 = {v3, v2};
	Args args3 = {v1, v4};
	Args args4 = {v3, v4};

	Args result1 = modulo(args1);
	Args result2 = modulo(args2);
	Args result3 = modulo(args3);
	Args result4 = modulo(args4);

	ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*result1[0]->get_data()));
	ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*result2[0]->get_data()));
	ASSERT_EQ(shaka::Number(-1), shaka::get<shaka::Number>(*result3[0]->get_data()));
	ASSERT_EQ(shaka::Number(-1), shaka::get<shaka::Number>(*result4[0]->get_data()));

}

TEST(Numbers_Arithmetic_impl, gcd_numbers_f) {
	using namespace shaka::stdproc;

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(20));
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(10));
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(100));
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(5));

	Args args = {v1, v2, v3, v4};
	Args args2 = {v1, v2, v3};

	Args result = shaka::stdproc::gcd(args);
	Args result2 = shaka::stdproc::gcd(args2);

	ASSERT_EQ(shaka::Number(5), shaka::get<shaka::Number>(*result[0]->get_data()));
	ASSERT_EQ(shaka::Number(10), shaka::get<shaka::Number>(*result2[0]->get_data()));

}

TEST(Numbers_Arithmetic_impl, lcm_numbers_f) {
	using namespace shaka::stdproc;

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(5));
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(70));
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(29));
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(31));

	Args args = {v1, v2, v3, v4};

	Args result = shaka::stdproc::lcm(args);

	ASSERT_EQ(shaka::Number(62930), shaka::get<shaka::Number>(*result[0]->get_data()));

}

TEST(Numbers_Arithmetic_impl, numerator_numbers_f) {
	using namespace shaka::stdproc;

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(1, 2));
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(3, 4));

	Args args1 = {v1};
	Args args2 = {v2};

	Args result1 = shaka::stdproc::numerator(args1);
	Args result2 = shaka::stdproc::numerator(args2);

	ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*result1[0]->get_data()));
	ASSERT_EQ(shaka::Number(3), shaka::get<shaka::Number>(*result2[0]->get_data()));
}

TEST(Numbers_Arithmetic_impl, denominator_numbers_f) {
	using namespace shaka::stdproc;

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(1, 2));
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(3, 4));

	Args args1 = {v1};
	Args args2 = {v2};

	Args result1 = shaka::stdproc::denominator(args1);
	Args result2 = shaka::stdproc::denominator(args2);

	ASSERT_EQ(shaka::Number(2), shaka::get<shaka::Number>(*result1[0]->get_data()));
	ASSERT_EQ(shaka::Number(4), shaka::get<shaka::Number>(*result2[0]->get_data()));

}

TEST(Numbers_Arithmetic_impl, floor_numbers_f) {
	using namespace shaka::stdproc;
	
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(50, 20));
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(7.54));

	Args args1 = {v1};
	Args args2 = {v2};

	Args result1 = shaka::stdproc::floor(args1);
	Args result2 = shaka::stdproc::floor(args2);

	ASSERT_EQ(shaka::Number(2), shaka::get<shaka::Number>(*result1[0]->get_data()));
	ASSERT_EQ(shaka::Number(7), shaka::get<shaka::Number>(*result2[0]->get_data()));
}

TEST(Numbers_Arithmetic_impl, ceiling_numbers_f) {
	using namespace shaka::stdproc;

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(5, 20));
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(8.0001));
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(20));
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(50, 20));

	Args args1 = {v1};
	Args args2 = {v2};
	Args args3 = {v3};
	Args args4 = {v4};

	Args result1 = shaka::stdproc::ceiling(args1);
	Args result2 = shaka::stdproc::ceiling(args2);
	Args result3 = shaka::stdproc::ceiling(args3);
	Args result4 = shaka::stdproc::ceiling(args4);

	ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*result1[0]->get_data()));
	ASSERT_EQ(shaka::Number(9.0), shaka::get<shaka::Number>(*result2[0]->get_data()));
	ASSERT_EQ(shaka::Number(20), shaka::get<shaka::Number>(*result3[0]->get_data()));
	ASSERT_EQ(shaka::Number(3), shaka::get<shaka::Number>(*result4[0]->get_data()));
}

TEST(Numbers_Arithmetic_impl, truncate_numbers_f) {
	using namespace shaka::stdproc;

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(5, 20));
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(6.549));
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(19));
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(50, 20));

	Args args1 = {v1};
	Args args2 = {v2};
	Args args3 = {v3};
	Args args4 = {v4};

	Args result1 = shaka::stdproc::truncate(args1);
	Args result2 = shaka::stdproc::truncate(args2);
	Args result3 = shaka::stdproc::truncate(args3);
	Args result4 = shaka::stdproc::truncate(args4);

	ASSERT_EQ(shaka::Number(0), shaka::get<shaka::Number>(*result1[0]->get_data()));
	ASSERT_EQ(shaka::Number(6.0), shaka::get<shaka::Number>(*result2[0]->get_data()));
	ASSERT_EQ(shaka::Number(19), shaka::get<shaka::Number>(*result3[0]->get_data()));
	ASSERT_EQ(shaka::Number(2), shaka::get<shaka::Number>(*result4[0]->get_data()));

}

TEST(Numbers_Arithmetic_impl, round_numbers_f) {
	using namespace shaka::stdproc;

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(5, 20));
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(7, 10));
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(5));
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(6.75));
	Value v5 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(6.25));

	Args args1 = {v1};
	Args args2 = {v2};
	Args args3 = {v3};
	Args args4 = {v4};
	Args args5 = {v5};

	Args result1 = shaka::stdproc::round(args1);
	Args result2 = shaka::stdproc::round(args2);
	Args result3 = shaka::stdproc::round(args3);
	Args result4 = shaka::stdproc::round(args4);
	Args result5 = shaka::stdproc::round(args5);

	ASSERT_EQ(shaka::Number(0), shaka::get<shaka::Number>(*result1[0]->get_data()));
	ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*result2[0]->get_data()));
	ASSERT_EQ(shaka::Number(5), shaka::get<shaka::Number>(*result3[0]->get_data()));
	ASSERT_EQ(shaka::Number(7.0), shaka::get<shaka::Number>(*result4[0]->get_data()));
	ASSERT_EQ(shaka::Number(6.0), shaka::get<shaka::Number>(*result5[0]->get_data()));

}

TEST(Numbers_Arithmetic_impl, exp_numbers_f) {
	using namespace shaka::stdproc;

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(5));
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(3, 4));
	Value v3 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(0.75));
	Value v4 = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(1.0));

	Args args1 = {v1};
	Args args2 = {v2};
	Args args3 = {v3};
	Args args4 = {v4};

	Args result1 = shaka::stdproc::exp(args1);
	Args result2 = shaka::stdproc::exp(args2);
	Args result3 = shaka::stdproc::exp(args3);
	Args result4 = shaka::stdproc::exp(args4);

	ASSERT_EQ(shaka::Number(148.41315910257), shaka::get<shaka::Number>(*result1[0]->get_data()));
	ASSERT_EQ(shaka::Number(2.11700001661), shaka::get<shaka::Number>(*result2[0]->get_data()));
	ASSERT_EQ(shaka::Number(2.11700001661), shaka::get<shaka::Number>(*result3[0]->get_data()));
	ASSERT_EQ(shaka::Number(2.71828182845), shaka::get<shaka::Number>(*result4[0]->get_data()));
}
int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
