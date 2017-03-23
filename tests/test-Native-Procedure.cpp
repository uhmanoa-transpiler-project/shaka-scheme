#include "Native_Procedure.h"
#include <functional>

#include "gtest/gtest.h"

#include <algorithm>
#include <numeric>

#include <boost/variant.hpp>

#include "DataNode.h"
#include "Environment.h"
//#include "Evaluator.h"
#include "Eval_Expression.h"
#include "Procedure.h"
#include "Symbol.h"
#include "Number.h"
#include <vector>

#include "Eval_Expression_impl.h"

TEST(Native_procedure, first){
using Value = std::shared_ptr<IDataNode<Data>>>
using Args = std::vector<Value>;
using Function = std::function<Args(Args)>;
using DataTree = shaka::DataNode<shaka::Data>;
using Environment = shaka::Environment<shaka::Symbol, std::shared_ptr<DataTree>>;
shaka::Number n1(1);
shaka::Number n2(1);
shaka::Number answer(2);
//shaka::Symbol s1("add");

Args number_plus(Args a){
	if(shaka::get<shaka::Number>(*a[0] -> get_data()) == typeid(shaka::Number) &&  shaka::get<shaka::Number>(*a[1]->get_data()) == typeid(shaka::Number)){
		return{std::make_shared<IDataNode<Data>>>(shaka::get<shaka::Number>(*a[0] -> get_data()) +  shaka::get<shaka::Number>(*a[1]->get_data()))}; 
	
}	
}

std::function<Args> adder = number_plus;
/*std::shared_ptr<DataTree> Function = std::make_shared<DataTree>(adder);

std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

env->set_value(s1, Function);
std::vector<shaka::Number> Arguments;
Arguments[0] = n1;
Arguments[1] = n2;
std::vector<shaka::Number> results;*/
Native_Procedure b(adder, 2);
auto result
//results = b.call(Arguments);


}








int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}



















