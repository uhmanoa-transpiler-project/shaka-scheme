//(*gcn).get<shaka::Number>()
//
// Created by Kirsten on 2/25/2018.
//
#include <gmock/gmock.h>
#include "shaka_scheme/system/gc/GCData.hpp"
#include "shaka_scheme/system/gc/GCNode.hpp"
#include "shaka_scheme/system/gc/GC.hpp"

/**
 * @Test: test_arrow_operator
 */
TEST (GCNodeUnitTest, test_constructor) {

    //Given: You constructed a GC and a GCData

    shaka::gc::GC garbage_collector;

    shaka::gc::GCData *gcd = garbage_collector.create_data(shaka::Number(5));
    
    //When: You wrap the GCData in a GCNode
    
    shaka::gc::GCNode gcn(gcd);

    //Then: the data in gcn is equal to 5
    
    ASSERT_EQ(gcn->get<shaka::Number>(), shaka::Number(5));
}

/**
 * @Test: Test dreference operator of GCNode
 */
TEST (GCNodeUnitTest, test_dreference) {

    //Given: You constructed a GC and a GCData

    shaka::gc::GC garbage_collector;

    shaka::gc::GCData *gcd = garbage_collector.create_data(shaka::Number(5));

    //When: You wrap the GCData in a GCNode
    
    shaka::gc::GCNode gcn(gcd);
    
    //Then: the data in gcn is equal to 5
    ASSERT_EQ((*gcn).get<shaka::Number>(), shaka::Number(5));
}
