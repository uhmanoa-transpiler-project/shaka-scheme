#include <functional>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <iostream>
#include <cctype>

#include "gtest/gtest.h"

#include "DataNode.h"

using DataTree = shaka::DataNode<
    boost::variant<
        int,
        std::function<int(int,int)>
    >
>;

TEST(Parser_mock, initialize_ifstream) {
    std::ifstream in("parsing-test-files/initialize_ifstream.txt");
}

TEST(Parser_mock, read_integer) {
    std::ifstream in("parsing-test-files/read_digit.txt");

    auto root = std::make_shared<DataTree>([](int i, int j) {
        return i + j;
    });

    auto parse = [](std::istream& in, std::shared_ptr<DataTree> root) {
        std::string buf;
        while (std::isdigit(in.peek())) {
            buf += in.peek();
            in.get();
        }
        if (std::isspace(in.peek())) {
            root->push_child(std::stoi(buf));
            in.get();
            return true;
        } else {
            return false;
        }
    };

    while (parse(in, root)) {
        std::cout << shaka::get<int>(*root->get_child(
            root->get_num_children()-1)->get_data()) << ' ';
    }   std::cout << std::endl;

    ASSERT_EQ(shaka::get<int>(*root->get_child(0)->get_data()), 1); 
    ASSERT_EQ(shaka::get<int>(*root->get_child(1)->get_data()), 2); 
    ASSERT_EQ(shaka::get<int>(*root->get_child(2)->get_data()), 0); 
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
