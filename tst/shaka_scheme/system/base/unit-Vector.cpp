#include <gmock/gmock.h>

#include <shaka_scheme/system/base/Vector.hpp>
#include <shaka_scheme/system/base/DataPair.hpp>

#include <shaka_scheme/system/exceptions/IndexOutOfBoundsException.hpp>
#include "shaka_scheme/system/gc/GC.hpp"
#include "shaka_scheme/system/gc/init_gc.hpp"

using namespace shaka;
/**
 * @brief Test: Constructors for Vector.
 */
TEST(VectorUnitTest, constructors) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);
  // Given: a size k and an element fill to construct with.
  std::size_t k       = 8;
  shaka::NodePtr fill = create_node(shaka::String("HelloWorld"));

  // When: a Vector is constructed with a size
  shaka::Vector bv0(k);
  // When: a Vector is constructed with a size and a fill element
  shaka::Vector bv1(k, fill);
  // When: a Vector is constructed with a brace initialization list
  const auto& c = shaka::create_node;
  shaka::Vector bv2({
                        c(shaka::Boolean(true)),
                        c(shaka::Number(1.23)),
                        c(shaka::Data())
                    });

  // Then: they should all succeed, with the correct size and elements
  ASSERT_EQ(bv0.length(), k);
  ASSERT_EQ(bv1.length(), k);
  for (std::size_t i = 0; i < bv1.length(); ++i) {
    ASSERT_EQ(bv1[i]->get<shaka::String>(), shaka::String("HelloWorld"));
  }
  ASSERT_EQ(bv2.length(), 3);
  ASSERT_EQ(bv2[0]->get<shaka::Boolean>(), shaka::Boolean(true));
  ASSERT_EQ(bv2[1]->get<shaka::Number>(), shaka::Number(1.23));
  ASSERT_EQ(bv2[2]->get_type(), shaka::Data::Type::NULL_LIST);
}

/**
 * @brief Test: operator[] for Vector
 */
TEST(VectorUnitTest, element_access) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);
  // Given: a Vector with 4 elements
  shaka::Vector bv(4);

  // When: you access the first element
  auto elem0 = bv[0];

  // Then: it should be equal to the first element
  ASSERT_EQ(elem0, bv[0]);

  // When: you modify the other elements
  const auto& c = shaka::create_node;
  bv[1] = c(shaka::String("a"));
  bv[2] = c(shaka::String("b"));
  bv[3] = c(shaka::String("c"));

  // Then: you should be able to obtain them
  ASSERT_EQ(bv[1]->get<shaka::String>(), shaka::String("a"));
  ASSERT_EQ(bv[2]->get<shaka::String>(), shaka::String("b"));
  ASSERT_EQ(bv[3]->get<shaka::String>(), shaka::String("c"));
}

/**
 * @brief Test: copy for Vector
 */
TEST(VectorUnitTest, copy) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  const auto& c = shaka::create_node;
  // Given: a Vector of size 3 with all elements as Number(1).
  shaka::Vector bv({
                       c(shaka::Number(1)),
                       c(shaka::Number(1)),
                       c(shaka::Number(1))
                   });

  // When: you copy the vector over
  shaka::Vector bv_other = bv;

  // Then: the two vectors should have the same length
  ASSERT_EQ(bv.length(), 3);
  ASSERT_EQ(bv_other.length(), 3);

  // Then: they should have the same elements
  for (std::size_t i = 0; i < bv.length(); ++i) {
    // The NodePtr should not be the same
    ASSERT_NE(bv[i], bv_other[i]);
    // But the values should be the same
    ASSERT_EQ(bv[i]->get<shaka::Number>(), bv_other[i]->get<shaka::Number>());
  }
}

/**
 * @brief Test: move for Vector
 */
TEST(VectorUnitTest, move) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  const auto& c = shaka::create_node;
  // Given: a Vector of size 3 with all elements as Number(1)
  shaka::Vector bv({
                       c(shaka::Number(1)),
                       c(shaka::Number(1)),
                       c(shaka::Number(1))
                   });

  // When: you move the vector over
  shaka::Vector bv_other = std::move(bv);

  // Then: you should be able to access the moved-into vector
  ASSERT_NO_THROW(bv_other[0]);
  // Then: you should get an exception for trying to access the moved-out of
  // vector
  ASSERT_THROW(bv[0], shaka::IndexOutOfBoundsException);
  // Then: the moved-into vector should have the same elements as the one
  // that was moved out of
  for (std::size_t i = 0; i < bv_other.length(); ++i) {
    ASSERT_EQ(bv_other[i]->get<shaka::Number>(), shaka::Number(1));
  }
  // Then: the moved-out of vector should have length 0, but the one that
  // was moved into should have the length of that which was moved-from
  // before it was moved
  ASSERT_EQ(bv.length(), 0);
  ASSERT_EQ(bv_other.length(), 3);
}

