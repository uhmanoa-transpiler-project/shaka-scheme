#include <gtest/gtest.h>
#include "core/base/Core.h"

using namespace shaka;

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
