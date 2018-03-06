#include <gmock/gmock.h>
#include <shaka_scheme/system/base/Bytevector.hpp>

/**
 * @brief Test: Constructors for Bytevector.
 */
TEST(BytevectorUnitTest, constructors) {
  // Given: a size k and an element fill to construct with.
  std::size_t k       = 8;
  unsigned char fill  = 0xab;

  // When: a Bytevector is constructed with a size
  shaka::Bytevector bv0(k);
  // When: a Bytevector is constructed with a size and a fill element
  shaka::Bytevector bv1(k, fill);
  // When: a Bytevector is constructed with a brace initialization length
  shaka::Bytevector bv2({ 0x0a, 0x0b, 0x0c });

  // Then: they should all succeed, with the correct size and elements
  ASSERT_EQ(bv0.length(), k);
  ASSERT_EQ(bv1.length(), k);
  for (std::size_t i = 0; i < bv1.length(); ++i) {
    ASSERT_EQ(bv1[i], 0xab);
  }
  ASSERT_EQ(bv2.length(), 3);
  ASSERT_EQ(bv2[0], 0x0a);
  ASSERT_EQ(bv2[1], 0x0b);
  ASSERT_EQ(bv2[2], 0x0c);
}

/**
 * @brief Test: operator[] for Bytevector
 */
TEST(BytevectorUnitTest, element_access) {
  // Given: a Bytevector with 4 elements
  shaka::Bytevector bv(4);

  // When: you access the first element
  auto elem0 = bv[0];

  // Then: it should be equal to the first element
  ASSERT_EQ(elem0, bv[0]);

  // When: you modify the other elements
  bv[1] = 0x11;
  bv[2] = 0x22;
  bv[3] = 0x33;

  // Then: you should be able to obtain them
  ASSERT_EQ(bv[1], 0x11);
  ASSERT_EQ(bv[2], 0x22);
  ASSERT_EQ(bv[3], 0x33);
}

/**
 * @brief Test: copy for Bytevector
 */
TEST(BytevectorUnitTest, copy) {
  // Given: a Bytevector of size 3 with all elements as 0xff.
  shaka::Bytevector bv({ 0xff, 0xff, 0xff });

  // When: you copy the vector over
  shaka::Bytevector bv_other = bv;

  // Then: they should have the same elements
  for (std::size_t i = 0; i < bv.length(); ++i) {
    ASSERT_EQ(bv[i], bv_other[i]);
  }
}

/**
 * @brief Test: move for Bytevector
 */
TEST(BytevectorUnitTest, move) {
  // Given: a Bytevector of size 3 with all elements as 0xaa;
  shaka::Bytevector bv({ 0xaa, 0xaa, 0xaa });

  // When: you copy the vector over
  shaka::Bytevector bv_other = std::move(bv);

  // Then: they should have the same elements
  for (std::size_t i = 0; i < bv_other.length(); ++i) {
    ASSERT_EQ(bv_other[i], 0xaa);
  }
}

