#include <functional>
#include "core/base/NativeProcedure.h"

#include "gtest/gtest.h"

#include <algorithm>
#include <numeric>

#include <boost/variant.hpp>
#include "core/base/Data.h"
#include "core/base/DataNode.h"
#include "core/base/Environment.h"
//#include "Evaluator.h"
//#include "Eval_Expression.h"
#include "core/base/Procedure_impl.h"
#include "core/base/Symbol.h"
#include "core/base/Number.h"
#include "core/base/String.h"
#include <vector>
#include "core/proc/EquivalencePredicates_impl.h"

//#include "Eval_Expression_impl.h"
TEST(equal_function, Numbers_equal){

	//using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
	//using Function = std::function<Args(Args)>;

	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::Number n1(1);
	shaka::Number n2(1);
	auto v1 = std::make_shared<shaka::DataNode>(n1);
	auto v2 = std::make_shared<shaka::DataNode>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);
	shaka::NativeProcedure b(shaka::stdproc::equal, 2);
	//auto result = b.call(a);
	shaka::Boolean c(true);
	auto answer = std::make_shared<shaka::DataNode>(c);
	auto result = b.call(a, env);
	
	ASSERT_EQ(*answer, *result[0]);

}
TEST(equal_function, Symbols_equal){

	//using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
	//using Function = std::function<Args(Args)>;

	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::Symbol n1("a");
	shaka::Symbol n2("a");
	auto v1 = std::make_shared<shaka::DataNode>(n1);
	auto v2 = std::make_shared<shaka::DataNode>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);
	shaka::NativeProcedure b(shaka::stdproc::equal, 2);
	//auto result = b.call(a);
	shaka::Boolean c(true);
	auto answer = std::make_shared<shaka::DataNode>(c);
	auto result = b.call(a, env);
	
	ASSERT_EQ(*answer, *result[0]);

}
TEST(equal_function, Boolean_equal){

	//using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
	//using Function = std::function<Args(Args)>;

	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::Boolean n1("a");
	shaka::Boolean n2("a");
	auto v1 = std::make_shared<shaka::DataNode>(n1);
	auto v2 = std::make_shared<shaka::DataNode>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);
	shaka::NativeProcedure b(shaka::stdproc::equal, 2);
	//auto result = b.call(a);
	shaka::Boolean c(true);
	auto answer = std::make_shared<shaka::DataNode>(c);
	auto result = b.call(a, env);
	
	ASSERT_EQ(*answer, *result[0]);

}
TEST(equal_function, null_list_equal){

	//using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
	//using Function = std::function<Args(Args)>;

	auto env = std::make_shared<shaka::Environment>(nullptr);
	auto v1 = std::make_shared<shaka::DataNode>(shaka::DataNode::list());
	auto v2 = std::make_shared<shaka::DataNode>(shaka::DataNode::list());
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);
	shaka::NativeProcedure b(shaka::stdproc::equal, 2);
	//auto result = b.call(a);
	shaka::Boolean c(true);
	auto answer = std::make_shared<shaka::DataNode>(c);
	auto result = b.call(a, env);
	
	ASSERT_EQ(*answer, *result[0]);

}
TEST(equal_function, string_equal){

	//using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
	//using Function = std::function<Args(Args)>;

	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::String n1("a");
	shaka::String n2("a");
	auto v1 = std::make_shared<shaka::DataNode>(n1);
	auto v2 = std::make_shared<shaka::DataNode>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);
	shaka::NativeProcedure b(shaka::stdproc::equal, 2);
	//auto result = b.call(a);
	shaka::Boolean c(true);
	auto answer = std::make_shared<shaka::DataNode>(c);
	auto result = b.call(a, env);
	
	ASSERT_EQ(*answer, *result[0]);

}

TEST(eqv_function, numbers_eqv){

	//using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
	//using Function = std::function<Args(Args)>;

	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::Number n1(1, 2);
	shaka::Number n2(1, 2);
	auto v1 = std::make_shared<shaka::DataNode>(n1);
	auto v2 = std::make_shared<shaka::DataNode>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);
	shaka::NativeProcedure b(shaka::stdproc::eqv, 2);
	//auto result = b.call(a);
	shaka::Boolean c(true);
	auto answer = std::make_shared<shaka::DataNode>(c);
	auto result = b.call(a, env);
	
	ASSERT_EQ(*answer, *result[0]);

}
TEST(eqv_function, symbol_eqv){

	//using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
	//using Function = std::function<Args(Args)>;

	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::Symbol n1("a");
	shaka::Symbol n2("a");
	auto v1 = std::make_shared<shaka::DataNode>(n1);
	auto v2 = std::make_shared<shaka::DataNode>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);
	shaka::NativeProcedure b(shaka::stdproc::eqv, 2);
	//auto result = b.call(a);
	shaka::Boolean c(true);
	auto answer = std::make_shared<shaka::DataNode>(c);
	auto result = b.call(a, env);
	
	ASSERT_EQ(*answer, *result[0]);

}
TEST(eqv_function, boolean_eqv){

	//using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
	//using Function = std::function<Args(Args)>;

	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::Boolean n1(true);
	shaka::Boolean n2(true);
	auto v1 = std::make_shared<shaka::DataNode>(n1);
	auto v2 = std::make_shared<shaka::DataNode>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);
	shaka::NativeProcedure b(shaka::stdproc::eqv, 2);
	//auto result = b.call(a);
	shaka::Boolean c(true);
	auto answer = std::make_shared<shaka::DataNode>(c);
	auto result = b.call(a, env);
	
	ASSERT_EQ(*answer, *result[0]);

}
TEST(eqv_function, string_eqv){

	//using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
	//using Function = std::function<Args(Args)>;

	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::String n1("a");
	//shaka::String n2("a");
	auto v1 = std::make_shared<shaka::DataNode>(n1);
	//auto v2 = std::make_shared<shaka::DataNode>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v1);
	shaka::NativeProcedure b(shaka::stdproc::eqv, 2);
	//auto result = b.call(a);
	shaka::Boolean c(true);
	auto answer = std::make_shared<shaka::DataNode>(c);
	auto result = b.call(a, env);
	
	ASSERT_EQ(*answer, *result[0]);

}
/*TEST(Native_procedure, first ){
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

}*/








int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}





















