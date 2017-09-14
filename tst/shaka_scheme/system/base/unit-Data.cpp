//
// Created by aytas on 8/6/2017.
//
#include <gmock/gmock.h>
#include <shaka_scheme/system/base/Data.hpp>

TEST(DataUnitTest, constructor_null_list) {
  // Given: Data default constructed (which means it holds a null list)
  shaka::Data data;

  ASSERT_EQ(data.get_type(), shaka::Data::Type::NULL_LIST);

  // When: Data is written to std::stringstream
  std::stringstream ss;
  ss << data;

  // Then: the output string should be the expected: "()"
  ASSERT_EQ(ss.str(), "()");
}


/**
 * @brief Test: Data with String
 */
TEST(DataUnitTest, constructor_string) {
    // Given: Data initialized to a String
    shaka::String str("Hello world");
    shaka::Data data(str);

    // When: Data is written to a std::stringstream
    std::stringstream ss;
    ss << data;

    // Then: the output string should match "Hello world"
    ASSERT_EQ(ss.str(), "\"Hello world\"");
}

/**
 * @brief Test: Data with Symbol
 */
TEST(DataUnitTest, constructor_symbol) {
  // Given: Data initialized to a Symbol
  shaka::Symbol symbol("foo");
  shaka::Data data(symbol);

  // When: Data is written to a std::stringstream
  std::stringstream ss;
  ss << data;

  // Then: the output string should be convertable back into a symbol
  ASSERT_EQ(shaka::Symbol(ss.str()), symbol);
}

TEST(DataUnitTest, constructor_boolean) {
  // Given: Data initialized to a Boolean
  shaka::Boolean boolean(false);
  shaka::Data data(boolean);

  // When: Data is written to a std::stringstream
  std::stringstream ss;
  ss << data;

  // Then: the output string should be comparable to that of a Boolean
  ASSERT_EQ(ss.str(), "#f");
}


