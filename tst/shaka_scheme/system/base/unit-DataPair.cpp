//
// Created by aytas on 8/6/2017.
//
#include "shaka_scheme/system/base/DataPair.hpp"
#include "shaka_scheme/system/base/Data.hpp"

#include <gmock/gmock.h>

/**
 * @brief Test: Constructor and car().
 */
TEST(DataPairUnitTest, single_constructor_and_cdr) {
    // Given: Data initialized to a (String, null list)
    shaka::String str("Hello world");
    shaka::Data data(str);

    // When: Data is used to initialize a DataPair to (String, null list)
    shaka::DataPair pair(data);

    // Then: when you try to get the car of the pair,
    // it will be the same data that we put into the string
    shaka::NodePtr car_node = pair.car();
    shaka::NodePtr cdr_node = pair.cdr();
    ASSERT_EQ(car_node->get<shaka::String>(), data.get<shaka::String>());
    ASSERT_EQ(cdr_node->get_type(), shaka::Data().get_type());
}

/**
 * @brief Test: dotted pair and cdr().
 */
TEST(DataPairUnitTest, double_constructor_and_cdr) {
    // Given: two Datas containing different symbols
    shaka::Symbol sym0("foo");
    shaka::Symbol sym1("bar");
    shaka::Data data0(sym0);
    shaka::Data data1(sym1);

    // When: you try to create a DataPair from the two Data
    shaka::DataPair pair(data0, data1);

    // Then: the car and cdr will have the correct contents
    shaka::NodePtr car_node = pair.car();
    shaka::NodePtr cdr_node = pair.cdr();

    ASSERT_EQ(car_node->get<shaka::Symbol>(), data0.get<shaka::Symbol>());
    ASSERT_EQ(cdr_node->get<shaka::Symbol>(), data1.get<shaka::Symbol>());
}

TEST(DataPairUnitTest, set_car) {
    // Given: a DataPair initialized to (#t, #f)
    shaka::DataPair pair(
        shaka::Data(shaka::Boolean(true)),
        shaka::Data(shaka::Boolean(false))
    );

    // When: you try to set-car! the DataPair to a string "foo"
    pair.set_car(shaka::create_node(shaka::Data(shaka::String("foo"))));

    // Then: the car will be changed.
    shaka::NodePtr car_node = pair.car();
    shaka::NodePtr cdr_node = pair.cdr();

    ASSERT_EQ(car_node->get_type(), shaka::Data::Type::STRING);
    ASSERT_EQ(cdr_node->get<shaka::Boolean>(), shaka::Boolean(false));
}

TEST(DataPairUnitTest, set_cdr) {
    // Given: a DataPair initialized to (#t, #f)
    shaka::DataPair pair(
        shaka::Data(shaka::Boolean(true)),
        shaka::Data(shaka::Boolean(false))
    );

    // When: you try to set-car! the DataPair to a string "qux"
    pair.set_cdr(shaka::create_node(shaka::Data(shaka::String("qux"))));

    // Then: the cdr will be changed.
    shaka::NodePtr car_node = pair.car();
    shaka::NodePtr cdr_node = pair.cdr();

    ASSERT_EQ(car_node->get<shaka::Boolean>(), shaka::Boolean(true));
    ASSERT_EQ(cdr_node->get_type(), shaka::Data::Type::STRING);
}
