#include <gtest/gtest.h>
#include "core/proc/Numbers_impl.h"
#include "core/base/Core.h"
#include "core/eval/Eval.h"

using NodePtrs = std::shared_ptr<shaka::DataNode>;
using Args = std::vector<NodePtrs>;
using namespace shaka;

TEST(Numbers, equals){
    Args args;
    args.push_back(std::make_shared<DataNode>(DataNode(Number(1))));
    args.push_back(std::make_shared<DataNode>(DataNode(Number(1))));
    args.push_back(std::make_shared<DataNode>(DataNode(Number(1))));    
    EnvPtr env = std::make_shared<Environment>(nullptr);
    Args result = stdproc::impl::num_equals(args, env);
    ASSERT_EQ(get<Boolean>(result[0]->get_data()),Boolean(true));
    Args result1 = stdproc::impl::num_greater_than_or_eq(args, env);
    ASSERT_EQ(get<Boolean>(result1[0]->get_data()),Boolean(true));
    Args result2 = stdproc::impl::num_less_than_or_eq(args, env);
    ASSERT_EQ(get<Boolean>(result2[0]->get_data()),Boolean(true));
    Args result3 = stdproc::impl::num_greater_than(args, env);
    ASSERT_EQ(get<Boolean>(result3[0]->get_data()),Boolean(false));
    Args result4 = stdproc::impl::num_less_than(args, env);
    ASSERT_EQ(get<Boolean>(result4[0]->get_data()),Boolean(false));    
}
TEST(Numbers, not_equals){
    Args args;
    args.push_back(std::make_shared<DataNode>(DataNode(Number(1))));
    args.push_back(std::make_shared<DataNode>(DataNode(Number(1))));
    args.push_back(std::make_shared<DataNode>(DataNode(Number(3))));    
    EnvPtr env = std::make_shared<Environment>(nullptr);
    Args result = stdproc::impl::num_equals(args, env);
    ASSERT_EQ(get<Boolean>(result[0]->get_data()),Boolean(false));
    Args result1 = stdproc::impl::num_less_than_or_eq(args, env);
    ASSERT_EQ(get<Boolean>(result1[0]->get_data()),Boolean(true));
    Args result2 = stdproc::impl::num_greater_than_or_eq(args, env);
    ASSERT_EQ(get<Boolean>(result2[0]->get_data()),Boolean(false));
    Args result3 = stdproc::impl::num_greater_than(args, env);
    ASSERT_EQ(get<Boolean>(result3[0]->get_data()),Boolean(false));
    Args result4 = stdproc::impl::num_less_than(args, env);
    ASSERT_EQ(get<Boolean>(result4[0]->get_data()),Boolean(false));    
}
TEST(Numbers, less){
    Args args;
    args.push_back(std::make_shared<DataNode>(DataNode(Number(1))));
    args.push_back(std::make_shared<DataNode>(DataNode(Number(2))));
    args.push_back(std::make_shared<DataNode>(DataNode(Number(3))));    
    EnvPtr env = std::make_shared<Environment>(nullptr);
    Args result = stdproc::impl::num_less_than(args, env);
    ASSERT_EQ(get<Boolean>(result[0]->get_data()),Boolean(true));

    Args result1 = stdproc::impl::num_less_than_or_eq(args, env);
    ASSERT_EQ(get<Boolean>(result1[0]->get_data()),Boolean(true));
    Args result2 = stdproc::impl::num_greater_than_or_eq(args, env);
    ASSERT_EQ(get<Boolean>(result2[0]->get_data()),Boolean(false));
    Args result3 = stdproc::impl::num_greater_than(args, env);
    ASSERT_EQ(get<Boolean>(result3[0]->get_data()),Boolean(false));
    Args result4 = stdproc::impl::num_equals(args, env);
    ASSERT_EQ(get<Boolean>(result4[0]->get_data()),Boolean(false));       
}
TEST(Numbers, not_less){
    Args args;
    args.push_back(std::make_shared<DataNode>(DataNode(Number(1))));
    args.push_back(std::make_shared<DataNode>(DataNode(Number(2))));
    args.push_back(std::make_shared<DataNode>(DataNode(Number(3))));  
    args.push_back(std::make_shared<DataNode>(DataNode(Number(2))));  
    args.push_back(std::make_shared<DataNode>(DataNode(Number(2))));    
    EnvPtr env = std::make_shared<Environment>(nullptr);
    Args result = stdproc::impl::num_less_than(args, env);
    ASSERT_EQ(get<Boolean>(result[0]->get_data()),Boolean(false));

    Args result1 = stdproc::impl::num_less_than_or_eq(args, env);
    ASSERT_EQ(get<Boolean>(result1[0]->get_data()),Boolean(false));
    Args result2 = stdproc::impl::num_greater_than_or_eq(args, env);
    ASSERT_EQ(get<Boolean>(result2[0]->get_data()),Boolean(false));
    Args result3 = stdproc::impl::num_greater_than(args, env);
    ASSERT_EQ(get<Boolean>(result3[0]->get_data()),Boolean(false));
    Args result4 = stdproc::impl::num_equals(args, env);
    ASSERT_EQ(get<Boolean>(result4[0]->get_data()),Boolean(false));   
}
TEST(Numbers, greater){
    Args args;
    args.push_back(std::make_shared<DataNode>(DataNode(Number(4))));   
    args.push_back(std::make_shared<DataNode>(DataNode(Number(3))));
    args.push_back(std::make_shared<DataNode>(DataNode(Number(2))));
    args.push_back(std::make_shared<DataNode>(DataNode(Number(1))));    
    EnvPtr env = std::make_shared<Environment>(nullptr);
    Args result = stdproc::impl::num_greater_than(args, env);
    ASSERT_EQ(get<Boolean>(result[0]->get_data()),Boolean(true));

    Args result1 = stdproc::impl::num_less_than_or_eq(args, env);
    ASSERT_EQ(get<Boolean>(result1[0]->get_data()),Boolean(false));
    Args result2 = stdproc::impl::num_greater_than_or_eq(args, env);
    ASSERT_EQ(get<Boolean>(result2[0]->get_data()),Boolean(true));
    Args result3 = stdproc::impl::num_equals(args, env);
    ASSERT_EQ(get<Boolean>(result3[0]->get_data()),Boolean(false));
      
}
TEST(Numbers, not_greater){
    Args args;
    args.push_back(std::make_shared<DataNode>(DataNode(Number(1))));  
    args.push_back(std::make_shared<DataNode>(DataNode(Number(3))));
    args.push_back(std::make_shared<DataNode>(DataNode(Number(2))));
    args.push_back(std::make_shared<DataNode>(DataNode(Number(1))));  

    EnvPtr env = std::make_shared<Environment>(nullptr);
    Args result = stdproc::impl::num_greater_than(args, env);
    ASSERT_EQ(get<Boolean>(result[0]->get_data()),Boolean(false));

    Args result1 = stdproc::impl::num_less_than_or_eq(args, env);
    ASSERT_EQ(get<Boolean>(result1[0]->get_data()),Boolean(false));
    Args result2 = stdproc::impl::num_greater_than_or_eq(args, env);
    ASSERT_EQ(get<Boolean>(result2[0]->get_data()),Boolean(false));
    Args result4 = stdproc::impl::num_equals(args, env);
    ASSERT_EQ(get<Boolean>(result4[0]->get_data()),Boolean(false));   
}
TEST(Numbers, greater_than_or_eq){
    Args args;
    args.push_back(std::make_shared<DataNode>(DataNode(Number(3))));
    args.push_back(std::make_shared<DataNode>(DataNode(Number(2))));
    args.push_back(std::make_shared<DataNode>(DataNode(Number(2))));  
    args.push_back(std::make_shared<DataNode>(DataNode(Number(2))));  
    args.push_back(std::make_shared<DataNode>(DataNode(Number(1))));    
    EnvPtr env = std::make_shared<Environment>(nullptr);
    Args result = stdproc::impl::num_greater_than_or_eq(args, env);
    ASSERT_EQ(get<Boolean>(result[0]->get_data()),Boolean(true));
    Args result1 = stdproc::impl::num_greater_than(args, env);
    ASSERT_EQ(get<Boolean>(result1[0]->get_data()),Boolean(false));

    Args result2 = stdproc::impl::num_less_than_or_eq(args, env);
    ASSERT_EQ(get<Boolean>(result2[0]->get_data()),Boolean(false));
    Args result3 = stdproc::impl::num_less_than(args, env);
    ASSERT_EQ(get<Boolean>(result3[0]->get_data()),Boolean(false));
    Args result4 = stdproc::impl::num_equals(args, env);
    ASSERT_EQ(get<Boolean>(result4[0]->get_data()),Boolean(false));   
}
TEST(Numbers, less_than_or_eq){
    Args args;
    args.push_back(std::make_shared<DataNode>(DataNode(Number(3))));
    args.push_back(std::make_shared<DataNode>(DataNode(Number(3))));
    args.push_back(std::make_shared<DataNode>(DataNode(Number(5)))); 
    args.push_back(std::make_shared<DataNode>(DataNode(Number(10))));    
    EnvPtr env = std::make_shared<Environment>(nullptr);
    Args result = stdproc::impl::num_less_than_or_eq(args, env);
    ASSERT_EQ(get<Boolean>(result[0]->get_data()),Boolean(true));
    Args result1 = stdproc::impl::num_less_than(args, env);
    ASSERT_EQ(get<Boolean>(result1[0]->get_data()),Boolean(false));
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
