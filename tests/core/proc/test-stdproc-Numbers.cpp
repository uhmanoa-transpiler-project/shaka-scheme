#include <gtest/gtest.h>
//#include "core/proc/primitives.h"
#include "core/base/DataNode.h"
#include "core/base/Environment_impl.h"
#include "core/eval/Eval.h"
#include "core/proc/String_impl.h"
#include "core/proc/Numbers_impl.h"


using NodePtrs = std::shared_ptr<shaka::DataNode>;
using Args = std::vector<NodePtrs>;

TEST(Numbers, is_number){
	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::Number a(1);
	auto b = std::make_shared<shaka::DataNode>(a);
	Args c;
	c.push_back(b);
	shaka::NativeProcedure d(shaka::stdproc::is_number, 1);
	auto result = d.call(c, env);
	shaka::Boolean e(true);
	ASSERT_EQ(shaka::get<shaka::Boolean>(result[0]->get_data()), e);
    
}
TEST(String, is_string){

	auto env = std::make_shared<shaka::Environment>(nullptr);
	shaka::String a("hi");
	auto b = std::make_shared<shaka::DataNode>(a);
	Args c;
	c.push_back(b);
	shaka::NativeProcedure d(shaka::stdproc::is_string, 1);
	auto result = d.call(c, env);
	shaka::Boolean e(true);
	ASSERT_EQ(shaka::get<shaka::Boolean>(result[0]->get_data()), e);
}

/*TEST(Booleans, is_bool){

        auto expr = std::make_shared<DataNode>(DataNode::list(
            DataNode::list(
                Symbol("not"),
                Boolean(true),
            ),
        )); 

             
}*/
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
