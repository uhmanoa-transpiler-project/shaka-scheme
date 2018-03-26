//
// Created by Herman on 3/23/2018.
//

#include "gmock/gmock.h"
#include "shaka_scheme/system/base/Character.hpp"

TEST(Character, test_comparisons) {
  shaka::Character c1('a');
  shaka::Character c2('b');
  shaka::Character c3(97);
  shaka::Character c4('\0');
  shaka::Character c5(54235);
  shaka::Character c6('a');

  ASSERT_EQ(c1 == c3, true);
  ASSERT_EQ(c1 == c6, true);
  ASSERT_EQ(c1 == c4, false);
  ASSERT_EQ(c4 < c1, true);
  ASSERT_EQ(c1 < c4, false);
  ASSERT_EQ(c2 > c1, true);
  ASSERT_EQ(c1 > c2, false);
  ASSERT_EQ(c1 <= c1, true);
  ASSERT_EQ(c1 <= c2, true);
  ASSERT_EQ(c4 >= c1, false);
}

