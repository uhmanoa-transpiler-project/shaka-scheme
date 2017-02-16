#include "gtest/gtest.h"

#include <memory>

template <typename T>
struct my_shared_ptr {

    // constructor:
    // - If no data, init it, count++
    // - If data, count++
    
    // destructor:
    // - count--,
    //   - If count == 0, delete data
    //   - Else, there are still owners, and keep data alive.

    T* data;
    int count;
};

TEST(std_shared_ptr, initialization) {
    std::shared_ptr<double> sptr = std::make_shared<double>(1.0); 

}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
