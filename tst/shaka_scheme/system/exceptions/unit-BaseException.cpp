//
// Created by aytas on 8/5/2017.
//
#include <gmock/gmock.h>
#include "shaka_scheme/system/exceptions/BaseException.hpp"

#include <stdexcept>

/**
 * @brief Test: Constructor for BaseException.
 */
TEST(BaseExceptionUnitTest, constructor_success) {
  EXPECT_THROW(throw shaka::BaseException(1, "Hello world"),
               shaka::BaseException);
}

/**
 * @brief Test: Verify Unicode character data can still be extracted
 * correctly.
 */
TEST(BaseExceptionUnitTest, constructor_utf8_success) {
  // Given: the exception string is UTF-8
  const std::size_t TEST_EXCEPTION_ID = 23094183428038290;
  const char* TEST_EXCEPTION_STRING = u8"汉字";

  // When: a shaka::BaseException is thrown with the UTF-8 string
  try {
    throw shaka::BaseException(TEST_EXCEPTION_ID, TEST_EXCEPTION_STRING);
  } catch (const shaka::BaseException& e) {
    // Then: the internal string data should remain preserved
    ASSERT_EQ(e.get_id(), TEST_EXCEPTION_ID);
    ASSERT_EQ(std::string(e.what()), std::string(TEST_EXCEPTION_STRING));
  }
}
