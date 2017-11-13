//
// Created by aytas on 8/6/2017.
//
#include <gmock/gmock.h>
#include <shaka_scheme/system/base/Data.hpp>

/**
 * @brief Test: Constructing Data with PrimitiveFormMarker
 */
TEST(PrimitiveFormMarkerUnitTest, data_constructor) {
  // Given: a PrimitiveFormMarker
  shaka::PrimitiveFormMarker marker("define");

  // When: a Data is constructed with a PrimitiveFormMarker
  shaka::Data data(marker);

  // Then: it should succeed
}

/**
 * @brief Test: PrimitiveFormMarker -> std::string -> PrimitiveFormMarker
 */
TEST(PrimitiveFormMarkerUnitTest, marker_get_value) {
  // Given: a PrimitiveFormMarker
  shaka::PrimitiveFormMarker marker("asdf");

  // When: you get the string value from it
  auto string = marker.get();

  // Then: it should be re-constructable back into the equivalent PrimitiveFormMarker
  ASSERT_EQ(shaka::PrimitiveFormMarker(string), marker);
}

/**
 * @brief Test: PrimitiveFormMarker to PrimitiveFormMarker comparison
 */
TEST(PrimitiveFormMarkerUnitTest, marker_comparison) {
  // Given: Three markers, from least to greatest, with lexigraphical order
  shaka::PrimitiveFormMarker marker1("abc");
  shaka::PrimitiveFormMarker marker2("abhgf");
  shaka::PrimitiveFormMarker marker2_dup("abhgf");
  shaka::PrimitiveFormMarker marker3("b");

  // When: you compare them
  // Then: expect string comparison
  ASSERT_NE(marker1, marker2);
  ASSERT_EQ(marker2, marker2_dup);
  ASSERT_NE(marker2, marker3);
}

TEST(PrimitiveFormMarkerUnitTest, printing) {
  // Given: a PrimitiveFormMarker
  shaka::PrimitiveFormMarker marker("Hello world");

  // When: you try to trigger the std::ostream& operator<<
  std::cout << marker << '\n';
  // Then: it should work.
}