//
// Created by aytas on 8/6/2017.
//
#include <gmock/gmock.h>
#include <shaka_scheme/system/base/Data.hpp>

/**
 * @brief Test: Constructing Data with Symbol
 */
TEST(SymbolUnitTest, data_constructor) {
  // Given: a Symbol
  shaka::Symbol symbol("Hello world");

  // When: a Data is constructed with a Symbol
  shaka::Data data(symbol);

  // Then: it should succeed
}

/**
 * @brief Test: Symbol -> std::string -> Symbol
 */
TEST(SymbolUnitTest, symbol_get_value) {
  // Given: a Symbol
  shaka::Symbol symbol("asdf");

  // When: you get the string value from it
  auto string = symbol.get_value();

  // Then: it should be re-constructable back into the equivalent Symbol
  ASSERT_EQ(shaka::Symbol(string), symbol);
}

/**
 * @brief Test: Symbol to Symbol comparison
 */
TEST(SymbolUnitTest, symbol_comparison) {
  // Given: Three symbols, from least to greatest, with lexigraphical order
  shaka::Symbol symbol1("abc");
  shaka::Symbol symbol2("abhgf");
  shaka::Symbol symbol2_dup("abhgf");
  shaka::Symbol symbol3("b");

  // When: you compare them
  // Then: expect lexigraphical ordering in comparison
  ASSERT_TRUE(symbol1 < symbol2);
  ASSERT_TRUE(symbol2 < symbol3);

  ASSERT_FALSE(symbol1 < symbol1);
  ASSERT_FALSE(symbol1 > symbol1);
  ASSERT_FALSE(symbol3 < symbol1);

  ASSERT_FALSE(symbol2 < symbol2_dup);
  ASSERT_FALSE(symbol2 != symbol2_dup);
  ASSERT_TRUE(symbol2 == symbol2_dup);
  ASSERT_TRUE(symbol2 <= symbol2_dup);
}

TEST(SymbolUnitTest, printing) {
  // Given: a Symbol
  shaka::Symbol sym("Hello world");

  // When: you try to trigger the std::ostream& operator<<
  std::cout << sym << '\n';
  // Then: it should work.
}