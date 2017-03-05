#include "gtest/gtest.h"
#include "DataNode.h"
#include "Environment.h"

#include <functional>
#include <algorithm>
#include <numeric>
using Environment = shaka::Environment<std::string, int *>;
TEST(Environment, constructor_null) {
    Environment e(nullptr);
    ASSERT_EQ(nullptr, e.get_parent()); 
}

TEST(Environment, define_find_key) {
    Environment e(nullptr);
    int num =1;
    int *value = &num;
    e.set_value("first", value);
    ASSERT_EQ(value, e.get_value("first"));
}

TEST(Environment, contains_key) {
    Environment e(nullptr);
    int num =1;
    int *value = &num;
    e.set_value("first", value);
    ASSERT_TRUE(e.contains("first"));
}

TEST(Environment, set_parent){
    Environment parent(nullptr);
    Environment child(nullptr);
    child.set_parent(&parent);
    ASSERT_EQ(child.get_parent(), &parent);
}
TEST(Environment, get_keys){
    Environment e(nullptr);
    int num =1;
    int *value = &num;
    e.set_value("first", value);

    ASSERT_EQ(static_cast<std::size_t>(1), e.get_keys().size());

}

TEST(Environment, contains_key_in_parent_check){

    /* Construct an environment */
    Environment parent(nullptr);

    /* Construct a child environment with a parent environment */
    Environment kid(&parent);
    int num =1;
    int *value = &num;

    /* Store a value with the key "first" in the parent environment */
    parent.set_value("first", value);

    /* Parent and child environment should return the same value */
    ASSERT_EQ(kid.get_value("first"), parent.get_value("first"));
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
