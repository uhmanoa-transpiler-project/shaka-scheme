#include <gtest/gtest.h>
#include "core/proc/primitives.h"
#include "core/proc/Booleans_impl.h"


using NodePtrs = std::shared_ptr<shaka::DataNode>;
using Args = std::vector<NodePtrs>;

TEST(Booleans, not_booleans){
    
        auto expr = std::make_shared<DataNode>(DataNode::list(
            DataNode::list(
                Symbol("not"),
                Boolean(true),
            ),
        ));
        auto env = std::make_shared<Environment>(nullptr);
        auto res = nots(expr, env);
        ASSERT_EQ(false, res);

        auto expr1 = std::make_shared<DataNode>(DataNode::list(
            DataNode::list(
                Symbol("not"),
                Boolean(false),
            ),
        ));        
        auto res = nots(expr1, env);
        ASSERT_EQ(true, res); 
}

TEST(Booleans, is_bool){

        auto expr = std::make_shared<DataNode>(DataNode::list(
            DataNode::list(
                Symbol("not"),
                Boolean(true),
            ),
        )); 

             
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
