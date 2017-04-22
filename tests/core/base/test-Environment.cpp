#include "gtest/gtest.h"
#include "core/base/Core.h"
#include "core/base/Environment.h"

#include <functional>
#include <algorithm>
#include <numeric>

using namespace shaka;

TEST(Environment, test_environment_default_constructor) {
	shaka::Environment e(nullptr);

	ASSERT_EQ(e.get_parent(), nullptr);
}

TEST(Environment, constructor_null) {
    Environment e(nullptr);
    ASSERT_EQ(nullptr, e.get_parent()); 
}

TEST(Environment, define_find_key) {
    Environment e(nullptr);
    shaka::Symbol key("first");
    auto value = make_node(Number(1));
    e.set_value(key, value);
    ASSERT_EQ(value, e.get_value(key));
}

TEST(Environment, contains_key) {
    Environment e(nullptr);
    shaka::Symbol key("first");
    auto value = make_node(Number(1));
    e.set_value(key, value);
    ASSERT_TRUE(e.contains(key));
}

TEST(Environment, set_parent){
    auto parent = std::make_shared<Environment>(nullptr);
    Environment child(nullptr);
    child.set_parent(parent);
    ASSERT_EQ(child.get_parent().get(), parent.get());
}

TEST(Environment, get_keys){
    Environment e(nullptr);
    shaka::Symbol key("first");
    auto value = make_node(Number(1));
    e.set_value(key, value);

    ASSERT_EQ(static_cast<std::size_t>(1), e.get_keys().size());
}

TEST(Environment, contains_key_in_parent_check){

    // Construct an environment
    auto parent = std::make_shared<Environment>(nullptr);

    // Construct a child environment with a parent environment
    Environment kid(parent);
    shaka::Symbol key("first");
    auto value = make_node(Number(1));

    // Store a value with the key "first" in the parent environment
    parent->set_value(key, value);

    // Parent and child environment should return the same value
    ASSERT_EQ(kid.get_value(key), parent->get_value(key));
}

TEST(Environment, print_bindings) {
    // Construct an environment
    auto env = std::make_shared<Environment>(nullptr);
    env->set_value(Symbol("a"), make_node(Number(1)));
    env->set_value(Symbol("b"), make_node(String("asdf")));
    env->set_value(Symbol("c"), make_node(Boolean(true)));
    env->set_value(Symbol("d"), make_node(DataNode::list()));
    env->set_value(Symbol("e"), make_node(DataNode::list(
        Number(1),
        Number(2.123),
        Number(1, 2)
    )));

    env->print_bindings(std::cout);
    
    // Create bindings of all types.
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
