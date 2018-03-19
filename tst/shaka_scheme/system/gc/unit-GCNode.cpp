//(*gcn).get<shaka::Number>()
//
// Created by Kirsten on 2/25/2018.
//
#include <gmock/gmock.h>
#include "shaka_scheme/system/gc/GCData.hpp"
#include "shaka_scheme/system/gc/GCNode.hpp"

/**
 * @Test: Test constructor of GCNode
 */
TEST (GCNodeUnitTest, test_constructor) {

    //Given: You construct a GCNode as follows
    shaka::GCData* gcd = new shaka::GCData(shaka::Data(shaka::Number(5)));
    shaka::GCNode gcn(gcd);

    //Then: the data in gcn is equal to 5
    ASSERT_EQ(gcn->get<shaka::Number>(), shaka::Number(5));

}

/**
 * @Test: Test dreference operator of GCNode
 */
TEST (GCNodeUnitTest, test_) {

    //Given: You construct a GCNode as follows
    shaka::GCData* gcd = new shaka::GCData(shaka::Data(shaka::Number(5)));
    shaka::GCNode gcn(gcd);
    
    //Then: the data in gcn is equal to 5
    ASSERT_EQ((*gcn).get<shaka::Number>(), shaka::Number(5));
}
