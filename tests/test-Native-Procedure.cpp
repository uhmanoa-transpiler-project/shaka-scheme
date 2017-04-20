#include "core/base/NativeProcedure.h"
#include <functional>
#include "gtest/gtest.h"

#include <algorithm>
#include <numeric>

#include <boost/variant.hpp>
#include "core/base/Data.h"
#include "core/base/DataNode.h"
#include "core/base/Environment.h"
//#include "Evaluator.h"
//#include "Eval_Expression.h"
//#include "Procedure_impl.h"
#include <vector>
#include "core/proc/Numbers_Arithmetic_impl.h"

//#include "Eval_Expression_impl.h"

/*TEST(Native_procedure, Random_function ){
	using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<Value>;

	shaka::Number n1(1);
	shaka::Number n2(1);
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(n1);
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);

	shaka::Number answer(2);
	//shaka::Symbol s1("add");
	auto number_plus = [](Args a) -> Args {
		if((*a[0] -> get_data()).type() == typeid(shaka::Number) &&  (*a[1]->get_data()).type() == typeid(shaka::Number)){
			return {
                std::make_shared<shaka::DataNode<shaka::Data>>(
                    shaka::get<shaka::Number>(*a[0] -> get_data()) +  shaka::get<shaka::Number>(*a[1]->get_data())
                )
            }; 
		} else {
            throw std::runtime_error("number_plus: Some of the arguments are not shaka::Number");
			return {
                std::make_shared<shaka::DataNode<shaka::Data>>(
                    shaka::MetaTag::LIST
                )
            }; 

        }
	};

	std::function<Args(Args)> adder = number_plus;
	shaka::NativeProcedure b(adder, 2);
	auto result = b.call(a);

	ASSERT_EQ(shaka::get<shaka::Number>(*result[0] ->get_data()), answer);

}*/

TEST(Native_procedure, Add_function ){
	using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::Number n1(1);
	shaka::Number n2(1);
	auto v1 = std::make_shared<shaka::DataNode>(n1);
	auto v2 = std::make_shared<shaka::DataNode>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);

	auto answer = std::make_shared<shaka::DataNode>(shaka::Number(2));
	//shaka::Symbol s1("add");
	/*auto number_plus = [](Args a) -> Args {
		if((*a[0] -> get_data()).type() == typeid(shaka::Number) &&  (*a[1]->get_data()).type() == typeid(shaka::Number)){
			return{std::make_shared<shaka::DataNode<shaka::Data>>(shaka::get<shaka::Number>(*a[0] -> get_data()) +  shaka::get<shaka::Number>(*a[1]->get_data()))}; 

		}	
	};*/

	//std::function<Args(Args)> adder = number_plus;
	shaka::NativeProcedure b(shaka::stdproc::add, 2);
	auto result = b.call(a, env);

	ASSERT_EQ(*result[0] , *answer);

}


TEST(Native_procedure, Multiply_function ){
	//using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<std::shared_ptr<shaka::DataNode>>;

	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::Number n1(10);
	shaka::Number n2(20);
	auto v1 = std::make_shared<shaka::DataNode>(n1);
	auto v2 = std::make_shared<shaka::DataNode>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);

	auto answer = std::make_shared<shaka::DataNode>(shaka::Number(200));
	//shaka::Symbol s1("add");
	/*auto number_plus = [](Args a) -> Args {
		if((*a[0] -> get_data()).type() == typeid(shaka::Number) &&  (*a[1]->get_data()).type() == typeid(shaka::Number)){
			return{std::make_shared<shaka::DataNode<shaka::Data>>(shaka::get<shaka::Number>(*a[0] -> get_data()) +  shaka::get<shaka::Number>(*a[1]->get_data()))}; 

		}	
	};*/

	//std::function<Args(Args)> adder = number_plus;
	shaka::NativeProcedure b(shaka::stdproc::mul, 2);
	auto result = b.call(a, env);

	ASSERT_EQ(*result[0], *answer);

}


TEST(Native_procedure, negative_function ){

	using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::Number n1(10);
	//shaka::Number n2(20);
	auto v1 = std::make_shared<shaka::DataNode>(n1);
	//Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	//a.push_back(v2);
	
	auto answer = std::make_shared<shaka::DataNode>(shaka::Number(-10));

	//shaka::Symbol s1("add");
	/*auto number_plus = [](Args a) -> Args {
		if((*a[0] -> get_data()).type() == typeid(shaka::Number) &&  (*a[1]->get_data()).type() == typeid(shaka::Number)){
			return{std::make_shared<shaka::DataNode<shaka::Data>>(shaka::get<shaka::Number>(*a[0] -> get_data()) +  shaka::get<shaka::Number>(*a[1]->get_data()))}; 

		}	
	};*/

	//std::function<Args(Args)> adder = number_plus;
	shaka::NativeProcedure b(shaka::stdproc::neg, 2);
	auto result = b.call(a, env);

	ASSERT_EQ(*result[0], *answer);

}


TEST(Native_procedure, subtract_function ){

	using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::Number n1(20);
	shaka::Number n2(10);
	auto v1 = std::make_shared<shaka::DataNode>(n1);
	auto v2 = std::make_shared<shaka::DataNode>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);

	auto answer = std::make_shared<shaka::DataNode>(shaka::Number(10));

	//shaka::Symbol s1("add");
	/*auto number_plus = [](Args a) -> Args {
		if((*a[0] -> get_data()).type() == typeid(shaka::Number) &&  (*a[1]->get_data()).type() == typeid(shaka::Number)){
			return{std::make_shared<shaka::DataNode<shaka::Data>>(shaka::get<shaka::Number>(*a[0] -> get_data()) +  shaka::get<shaka::Number>(*a[1]->get_data()))}; 

		}	
	};*/

	//std::function<Args(Args)> adder = number_plus;
	shaka::NativeProcedure b(shaka::stdproc::sub, 2);
	auto result = b.call(a, env);

	ASSERT_EQ(*result[0] , *answer);

}

TEST(Native_procedure, reciprocal_function ){

	using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::Number n1(2);
	//shaka::Number n2(1);
	auto v1 = std::make_shared<shaka::DataNode>(n1);
	//Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	//a.push_back(v2);
	
	auto answer = std::make_shared<shaka::DataNode>(shaka::Number(1, 2));

	shaka::NativeProcedure b(shaka::stdproc::reciprocal, 1);
	//Currently this returns a float it should return a rational
	//Must fix this
	auto result = b.call(a, env);

	ASSERT_EQ(*result[0], *answer);

}

TEST(Native_procedure, divide_function ){

	using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::Number n1(2);
	shaka::Number n2(1);
	auto v1 = std::make_shared<shaka::DataNode>(n1);
	auto v2 = std::make_shared<shaka::DataNode>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);
	auto answer = std::make_shared<shaka::DataNode>(shaka::Number(2));
	shaka::NativeProcedure b(shaka::stdproc::div, 2);
	//Currently this returns a float it should return a rational
	//Must fix this
	auto result = b.call(a, env);

	ASSERT_EQ(*result[0], *answer);

}

TEST(Native_procedure, abs_value_function ){

	using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::Number n1(2);
	shaka::Number n2(-2);
	auto v1 = std::make_shared<shaka::DataNode>(n1);
	auto v2 = std::make_shared<shaka::DataNode>(n2);
	//fill vector
	Args a;
	Args c;
	a.push_back(v1);
	c.push_back(v2);
	auto answer = std::make_shared<shaka::DataNode>(shaka::Number(2));

	shaka::NativeProcedure b(shaka::stdproc::abs, 1);
	
	shaka::NativeProcedure d(shaka::stdproc::abs, 1);
	//Currently this returns a float it should return a rational
	//Must fix this
	auto result = b.call(a, env);
	auto result1 = d.call(c, env);

	ASSERT_EQ(*result[0] , *answer);

	ASSERT_EQ(*result1[0] , *answer);
}

TEST(Native_procedure, floor_div_function ){

	using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::Number n1(5);
	shaka::Number n2(2);
	auto v1 = std::make_shared<shaka::DataNode>(n1);
	auto v2 = std::make_shared<shaka::DataNode>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);
	auto answer = std::make_shared<shaka::DataNode>(shaka::Number(2));
	auto remainder = std::make_shared<shaka::DataNode>(shaka::Number(1));

	shaka::NativeProcedure b(shaka::stdproc::floor_div, 2);
	
	auto result = b.call(a, env);

	ASSERT_EQ(*result[0], *answer);

	ASSERT_EQ(*result[1], *remainder);
}

TEST(Native_procedure, floor_quotient_function ){

	using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::Number n1(5);
	shaka::Number n2(2);
	auto v1 = std::make_shared<shaka::DataNode>(n1);
	auto v2 = std::make_shared<shaka::DataNode>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);
	auto answer = std::make_shared<shaka::DataNode>(shaka::Number(2));

	shaka::NativeProcedure b(shaka::stdproc::floor_quotient, 2);
	
	auto result = b.call(a, env);

	ASSERT_EQ(*result[0], *answer);

}


TEST(Native_procedure, floor_remainder_function ){

	using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::Number n1(5);
	shaka::Number n2(2);
	auto v1 = std::make_shared<shaka::DataNode>(n1);
	auto v2 = std::make_shared<shaka::DataNode>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);
	auto answer = std::make_shared<shaka::DataNode>(shaka::Number(1));

	shaka::NativeProcedure b(shaka::stdproc::floor_remainder, 2);
	
	auto result = b.call(a, env);

	ASSERT_EQ(*result[0], *answer);

}

TEST(Native_procedure, truncate_div_function ){

	using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::Number n1(-5);
	shaka::Number n2(2);
	auto v1 = std::make_shared<shaka::DataNode>(n1);
	auto v2 = std::make_shared<shaka::DataNode>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);
	auto answer = std::make_shared<shaka::DataNode>(shaka::Number(-2));
	auto remainder = std::make_shared<shaka::DataNode>(shaka::Number(-1));

	shaka::NativeProcedure b(shaka::stdproc::truncate_div, 2);	
	auto result = b.call(a, env);

	ASSERT_EQ(*result[0], *answer);
	ASSERT_EQ(*result[1], *remainder);

}
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}



















