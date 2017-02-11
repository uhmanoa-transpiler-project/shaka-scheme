#include "gtest/gtest.h"
#include "DataNode.h"
#include "Environment.h"
#include <functional>
#include <algorithm>
#include <numeric>

#ifdef env_char_map
TEST(Environment, constructor_default) {
    shaka::Environment e;
    ASSERT_EQ(nullptr, e.getParentPtr());
}
TEST(Environment, define_find_key) {
    shaka::Environment e;
    e.define("first", '1');
    ASSERT_EQ('1', *e.find("first"));
}
TEST(Environment, costructor_overload){
    shaka::Environment parent;
    shaka::Environment kid(&parent);
    ASSERT_EQ(kid.getParentPtr(), &parent);
}
TEST(Environment, set_parent){
    shaka::Environment parent;
    shaka::Environment child;
    child.setParent(&parent);
    ASSERT_EQ(child.getParentPtr(), &parent);
}
TEST(Environment, find_key_in_parent){
    shaka::Environment parent;
    shaka::Environment kid(&parent);
    parent.define("first", 'a');
    ASSERT_EQ(*kid.find("first"),'a');
}
TEST(Environment, find_key_in_parent_check){
    shaka::Environment parent;
    shaka::Environment kid(&parent);
    parent.define("first", 'a');
    ASSERT_EQ(kid.find("first"),parent.find("first"));
}
TEST(Environment, find_key_in_parent_2children){
    shaka::Environment parent;
    shaka::Environment kid(&parent);
    shaka::Environment kid2(&parent);
    parent.define("first", 'a');
    ASSERT_EQ(kid.find("first"),kid2.find("first"));
}
TEST(Environment, find_key_not_found){
    shaka::Environment e;
    ASSERT_EQ(e.find("first"), nullptr);
}
TEST(Environment, find_in_grandparent){
    shaka::Environment grandparent;
    shaka::Environment parent(&grandparent);
    shaka::Environment kid(&parent);
    grandparent.define("first", 'a');
    ASSERT_EQ(kid.find("first"),parent.find("first"));
}
#endif
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
