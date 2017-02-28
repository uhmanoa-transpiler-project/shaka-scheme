#include "gtest/gtest.h"
#include "DataNode.h"

#include <functional>
#include <algorithm>
#include <numeric>

enum class MetaTag{
    DEFINE,
    PROC_CALL
};

using Data = boost::variant<
    MetaTag,
    int,
    std::string
>;
using DataTree = shaka::DataNode<Data>;

/// @brief Basic default constructor test
TEST(DataNode, constructor_default) {
   
    // Defined 3 shaka::DataNode<Data>
    DataTree root0(MetaTag::DEFINE);
    DataTree root1(5);
    DataTree root2("Hello World!!");

    // retrieve
    auto data0 = boost::get<MetaTag>(*root0.get_data());
    auto data1 = boost::get<int>(*root1.get_data());
    auto data2 = boost::get<std::string>(*root2.get_data());

    // Here is now to check the type inside the node
    if(MetaTag* ptr = boost::get<MetaTag>(root0.get_data().get())){
        std::cout << "Data in Root0 is MetaTag" << std::endl;
    }
    else if(int* ptr = boost::get<int>(root0.get_data().get())){
        std::cout << "Data in Root0 is int" << std::endl;
    }
    else if(std::string* ptr = boost::get<std::string>(root0.get_data().get())){
        std::cout << "Data in Root0 is std::string" << std::endl;
    }

    //std::shared_ptr<DataTree>

}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
