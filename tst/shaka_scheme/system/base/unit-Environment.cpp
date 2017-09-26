//
// Created by dylan on 9/20/17.
//

#include <gmock/gmock.h>
#include "shaka_scheme/system/base/Environment.hpp"
#include "shaka_scheme/system/base/Data.hpp"

using namespace shaka;

TEST(EnvironmentUnitTest, parent_constructor) {
  // Given: an environment with parent as null pointer.
  Environment e(nullptr);

  // When: you try to get the parent
  // Then: it will return a null pointer.
  ASSERT_EQ(e.get_parent(), nullptr);

  // Given: a pointer to a parent Environment
  //        an Environment with parent as pointer to parent Environment.
  auto parent = std::make_shared<Environment>(nullptr);
  e.set_parent(parent);

  // When: you try to get the parent.
  // Then: it will return the pointer to the parent Environment.
  ASSERT_EQ(e.get_parent(), parent);
}

TEST(EnvironmentUnitTest, get_parent) {
  // Given: a pointer to a parent Environment
  //        environment with parent as null pointer.
  Environment e(nullptr);
  auto parent = std::make_shared<Environment>(nullptr);

  // When: you try to get the parent
  // Then: it will return the pointer to the null pointer.
  ASSERT_EQ(e.get_parent(), nullptr);

  // Given: environment with parent set to pointer to parent Environment.
  e.set_parent(parent);

  // When: you try to get the parent
  // Then: it will return the pointer to the parent Environment.
  ASSERT_EQ(e.get_parent(), parent);

}

TEST(EnvironmentUnitTest, set_parent) {
  // Given: a pointer to a parent Environment.
  //        a child Environment with parent initialized to null pointer.
  auto parent = std::make_shared<Environment>(nullptr);
  Environment child(nullptr);

  // When: you set the child's parent to the parent pointer.
  child.set_parent(parent);

  // Then: the child's parent will be changed to the parent pointer.
  ASSERT_EQ(child.get_parent(), parent);
}

TEST(EnvironmentUnitTest, set_value) {
  // Given: an environment with parent initialized to the null pointer.
  //        a Symbol
  //        a Value
  Environment e(nullptr);
  Symbol key("x");
  auto value = create_node(String("test"));

  // When: you set the key to the specified value
  e.set_value(key, value);

  // Then: the key will have the correct value
  ASSERT_EQ(e.get_value(key), value);
}
TEST(EnvironmentUnitTest, get_value_success) {
  // Given: an environment, key and value
  Environment e(nullptr);
  Symbol key1("x");
  auto value1 = create_node(String("test"));

  // When: you set the key to the specified value
  e.set_value(key1, value1);

  // Then: the correct value will be set
  ASSERT_EQ(e.get_value(key1), value1);

  // Given: an environment with parent set to pointer to parent environment,
  //        key and value
  auto parent = std::make_shared<Environment>(nullptr);
  e.set_parent(parent);
  Symbol key2("y");
  auto value2 = create_node(String("parent test"));

  // When: you set the key to the specified value in only the parent
  parent->set_value(key2, value2);

  // Then: the correct value will be returned
  ASSERT_EQ(e.get_value(key2), value2);
}
TEST(EnvironmentUnitTest, get_value_invalid_key_failure) {
  // Given: an environment and key
  Environment e(nullptr);
  Symbol key("x");

  // When: you try to get a key with no binding in the environment
  // Then: an InvalidInputException is thrown
  ASSERT_THROW(e.get_value(key), InvalidInputException);

}

TEST(EnvironmentUnitTest, contains) {

}

TEST(EnvironmentUnitTest, is_defined) {
  // Given: a child environment, parent environment, different symbols and
  //        values
  Environment child(nullptr);
  auto parent = std::make_shared<Environment>(nullptr);

  Symbol child_key("x");
  Symbol parent_key("y");
  auto x_value = create_node(String("x test"));
  auto y_value = create_node(String("y test"));

  // When: you define some key to be a specific value in the current environment
  child.set_value(child_key, x_value);

  // Then: the correct key will be found
  ASSERT_TRUE(child.is_defined(child_key));

  // When: you define some other key to be a different value in the parent
  //       environment and the parent to be the child's parent
  parent->set_value(parent_key, y_value);
  child.set_parent(parent);

  // Then: the correct key will be found
  ASSERT_TRUE(child.is_defined(parent_key));

  // When: a key is not defined in an environment
  // Then: the key will not be found
  ASSERT_FALSE(parent->is_defined(child_key));
}
TEST(EnvironmentUnitTest, get_keys) {
  // Given: an environment with defined symbols and values
  Environment e(nullptr);
  Symbol key1("x");
  Symbol key2("y");
  auto value1 = create_node(String("test"));
  auto value2 = create_node(String("test 2"));
  e.set_value(key1, value1);
  e.set_value(key2, value2);

  // When: you get the keys from the environment
  std::vector<Symbol> local_keys = e.get_keys();
  Symbol first_key = local_keys.at(0);
  Symbol second_key = local_keys.at(1);

  // Then: the correct keys will be returned
  ASSERT_EQ(key1, first_key);
  ASSERT_EQ(key2, second_key);
  ASSERT_EQ(static_cast<std::size_t>(2), e.get_keys().size());
}

TEST(EnvironmentUnitTest, get_bindings) {
  // Given: an environment with a symbol/data binding
  Environment e(nullptr);
  Symbol key1("x");
  Symbol key2("y");
  auto value1 = create_node(String("x test"));
  auto value2 = create_node(String("y test"));
  e.set_value(key1, value1);
  e.set_value(key2, value2);

  // When: you get the current environment bindings
  std::map<Symbol, NodePtr> local_bindings = e.get_bindings();

  // Then: the correct bindings will be returned
  ASSERT_EQ(local_bindings.at(key1), value1);
  ASSERT_EQ(local_bindings.at(key2), value2);
  ASSERT_EQ(static_cast<std::size_t >(2), e.get_bindings().size());
}



