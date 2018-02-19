//
// Created by Brandon Wong on 2/18/18.
//

#include <gmock/gmock.h>
#include "shaka_scheme/system/gc/GCList.hpp"

TEST(GCListUnitTest, constructor_test) {
    shaka::GCList list;
    
    ASSERT_TRUE(list.is_empty());
}