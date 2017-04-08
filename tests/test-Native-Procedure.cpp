#include "Native_Procedure.h"
#include <functional>
#include "gtest/gtest.h"

#include <algorithm>
#include <numeric>

#include <boost/variant.hpp>
#include "Data.h"
#include "DataNode.h"
#include "Environment.h"
//#include "Evaluator.h"
#include "Eval_Expression.h"
//#include "Procedure_impl.h"
#include <vector>
#include "stdproc/Numbers_Arithmetic_impl.h"

//#include "Eval_Expression_impl.h"

TEST(Native_procedure, Random_function ){
	using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<Value>;
	using Function = std::function<Args(Args)>;

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
			return{std::make_shared<shaka::DataNode<shaka::Data>>(shaka::get<shaka::Number>(*a[0] -> get_data()) +  shaka::get<shaka::Number>(*a[1]->get_data()))}; 

		}	
	};

	std::function<Args(Args)> adder = number_plus;
	shaka::Native_Procedure b(adder, 2);
	auto result = b.call(a);

	ASSERT_EQ(shaka::get<shaka::Number>(*result[0] ->get_data()), answer);

}

TEST(Native_procedure, Add_function ){
	using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<Value>;
	using Function = std::function<Args(Args)>;

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
	/*auto number_plus = [](Args a) -> Args {
		if((*a[0] -> get_data()).type() == typeid(shaka::Number) &&  (*a[1]->get_data()).type() == typeid(shaka::Number)){
			return{std::make_shared<shaka::DataNode<shaka::Data>>(shaka::get<shaka::Number>(*a[0] -> get_data()) +  shaka::get<shaka::Number>(*a[1]->get_data()))}; 

		}	
	};*/

	//std::function<Args(Args)> adder = number_plus;
	shaka::Native_Procedure b(shaka::stdproc::add, 2);
	auto result = b.call(a);

	ASSERT_EQ(shaka::get<shaka::Number>(*result[0] ->get_data()), answer);

}


TEST(Native_procedure, Multiply_function ){
	using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<Value>;
	using Function = std::function<Args(Args)>;

	shaka::Number n1(10);
	shaka::Number n2(20);
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(n1);
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);

	shaka::Number answer(200);
	//shaka::Symbol s1("add");
	/*auto number_plus = [](Args a) -> Args {
		if((*a[0] -> get_data()).type() == typeid(shaka::Number) &&  (*a[1]->get_data()).type() == typeid(shaka::Number)){
			return{std::make_shared<shaka::DataNode<shaka::Data>>(shaka::get<shaka::Number>(*a[0] -> get_data()) +  shaka::get<shaka::Number>(*a[1]->get_data()))}; 

		}	
	};*/

	//std::function<Args(Args)> adder = number_plus;
	shaka::Native_Procedure b(shaka::stdproc::mul, 2);
	auto result = b.call(a);

	ASSERT_EQ(shaka::get<shaka::Number>(*result[0] ->get_data()), answer);

}


TEST(Native_procedure, negative_function ){
	using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<Value>;
	using Function = std::function<Args(Args)>;

	shaka::Number n1(10);
	//shaka::Number n2(20);
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(n1);
	//Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	//a.push_back(v2);

	shaka::Number answer(-10);
	//shaka::Symbol s1("add");
	/*auto number_plus = [](Args a) -> Args {
		if((*a[0] -> get_data()).type() == typeid(shaka::Number) &&  (*a[1]->get_data()).type() == typeid(shaka::Number)){
			return{std::make_shared<shaka::DataNode<shaka::Data>>(shaka::get<shaka::Number>(*a[0] -> get_data()) +  shaka::get<shaka::Number>(*a[1]->get_data()))}; 

		}	
	};*/

	//std::function<Args(Args)> adder = number_plus;
	shaka::Native_Procedure b(shaka::stdproc::neg, 2);
	auto result = b.call(a);

	ASSERT_EQ(shaka::get<shaka::Number>(*result[0] ->get_data()), answer);

}


TEST(Native_procedure, subtract_function ){
	using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<Value>;
	using Function = std::function<Args(Args)>;

	shaka::Number n1(20);
	shaka::Number n2(10);
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(n1);
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);

	shaka::Number answer(10);
	//shaka::Symbol s1("add");
	/*auto number_plus = [](Args a) -> Args {
		if((*a[0] -> get_data()).type() == typeid(shaka::Number) &&  (*a[1]->get_data()).type() == typeid(shaka::Number)){
			return{std::make_shared<shaka::DataNode<shaka::Data>>(shaka::get<shaka::Number>(*a[0] -> get_data()) +  shaka::get<shaka::Number>(*a[1]->get_data()))}; 

		}	
	};*/

	//std::function<Args(Args)> adder = number_plus;
	shaka::Native_Procedure b(shaka::stdproc::sub, 2);
	auto result = b.call(a);

	ASSERT_EQ(shaka::get<shaka::Number>(*result[0] ->get_data()), answer);

}

TEST(Native_procedure, reciprocal_function ){
	using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<Value>;
	using Function = std::function<Args(Args)>;

	shaka::Number n1(2);
	//shaka::Number n2(1);
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(n1);
	//Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	//a.push_back(v2);

	shaka::Number answer(1, 2);
	shaka::Native_Procedure b(shaka::stdproc::reciprocal, 1);
	//Currently this returns a float it should return a rational
	//Must fix this
	auto result = b.call(a);

	ASSERT_EQ(shaka::get<shaka::Number>(*result[0] ->get_data()), answer);

}

TEST(Native_procedure, divide_function ){
	using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<Value>;
	using Function = std::function<Args(Args)>;

	shaka::Number n1(2);
	shaka::Number n2(1);
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(n1);
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);

	shaka::Number answer(2);
	shaka::Native_Procedure b(shaka::stdproc::div, 2);
	//Currently this returns a float it should return a rational
	//Must fix this
	auto result = b.call(a);

	ASSERT_EQ(shaka::get<shaka::Number>(*result[0] ->get_data()), answer);

}

TEST(Native_procedure, abs_value_function ){
	using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<Value>;
	using Function = std::function<Args(Args)>;

	shaka::Number n1(2);
	shaka::Number n2(-2);
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(n1);
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(n2);
	//fill vector
	Args a;
	Args c;
	a.push_back(v1);
	c.push_back(v2);

	shaka::Number answer(2);
	shaka::Native_Procedure b(shaka::stdproc::abs, 1);
	
	shaka::Native_Procedure d(shaka::stdproc::abs, 1);
	//Currently this returns a float it should return a rational
	//Must fix this
	auto result = b.call(a);
	auto result1 = d.call(c);

	ASSERT_EQ(shaka::get<shaka::Number>(*result[0] ->get_data()), answer);

	ASSERT_EQ(shaka::get<shaka::Number>(*result1[0] ->get_data()), answer);
}

TEST(Native_procedure, floor_div_function ){
	using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<Value>;
	using Function = std::function<Args(Args)>;

	shaka::Number n1(5);
	shaka::Number n2(2);
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(n1);
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);

	shaka::Number answer(2);
	shaka::Number remainder(1);
	shaka::Native_Procedure b(shaka::stdproc::floor_div, 2);
	
	auto result = b.call(a);

	ASSERT_EQ(shaka::get<shaka::Number>(*result[0] ->get_data()), answer);

	ASSERT_EQ(shaka::get<shaka::Number>(*result[1] ->get_data()), remainder);
}

TEST(Native_procedure, floor_quotient_function ){
	using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<Value>;
	using Function = std::function<Args(Args)>;

	shaka::Number n1(5);
	shaka::Number n2(2);
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(n1);
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);

	shaka::Number answer(2);
	shaka::Native_Procedure b(shaka::stdproc::floor_quotient, 2);
	
	auto result = b.call(a);

	ASSERT_EQ(shaka::get<shaka::Number>(*result[0] ->get_data()), answer);

}


TEST(Native_procedure, floor_remainder_function ){
	using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<Value>;
	using Function = std::function<Args(Args)>;

	shaka::Number n1(5);
	shaka::Number n2(2);
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(n1);
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);

	shaka::Number answer(1);
	shaka::Native_Procedure b(shaka::stdproc::floor_remainder, 2);
	
	auto result = b.call(a);

	ASSERT_EQ(shaka::get<shaka::Number>(*result[0] ->get_data()), answer);

}

TEST(Native_procedure, truncate_div_function ){
	using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<Value>;
	using Function = std::function<Args(Args)>;

	shaka::Number n1(-5);
	shaka::Number n2(2);
	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(n1);
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);

	shaka::Number answer(-2);
	shaka::Number remainder(-1);
	shaka::Native_Procedure b(shaka::stdproc::truncate_div, 2);	
	auto result = b.call(a);

	ASSERT_EQ(shaka::get<shaka::Number>(*result[0] ->get_data()), answer);
	ASSERT_EQ(shaka::get<shaka::Number>(*result[1] ->get_data()), remainder);

}
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}



















