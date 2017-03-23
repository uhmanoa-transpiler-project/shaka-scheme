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
#include "Procedure.h"
#include "Symbol.h"
#include "Number.h"
#include <vector>

//#include "Eval_Expression_impl.h"

TEST(Native_procedure, first){
	using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	using Args = std::vector<Value>;
	using Function = std::function<Args(Args)>;
	shaka::Number n1(1);
	shaka::Number n2(1);
	Value v1 = std::make_shared<shaka::IDataNode<shaka::Data>>(n1);
	Value v2 = std::make_shared<shaka::IDataNode<shaka::Data>>(n2);
	//fill vector
	Args a;
	a.push_back(v1);
	a.push_back(v2);

	shaka::Number answer(2);
	//shaka::Symbol s1("add");
	auto number_plus = [](Args a) -> Args {
		if((*a[0] -> get_data()).type() == typeid(shaka::Number) &&  (*a[1]->get_data()).type() == typeid(shaka::Number)){
			return{std::make_shared<shaka::IDataNode<shaka::Data>>(shaka::get<shaka::Number>(*a[0] -> get_data()) +  shaka::get<shaka::Number>(*a[1]->get_data()))}; 

		}	
	};

	std::function<Args(Args)> adder = number_plus;
	/*std::shared_ptr<DataTree> Function = std::make_shared<DataTree>(adder);

	  std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

	  env->set_value(s1, Function);
	  std::vector<shaka::Number> Arguments;
	  Arguments[0] = n1;
	  Arguments[1] = n2;
	  std::vector<shaka::Number> results;*/
	Native_Procedure b(adder, 2);
	auto result = b.call(a);

	ASSERT_EQ(shaka::get<shaka::Number>(*result[0] ->get_data()), answer);

}








int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}



















