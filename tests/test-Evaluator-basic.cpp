#include "gtest/gtest.h"

#include <functional>
#include <algorithm>
#include <numeric>

#include <boost/variant.hpp>

#include "DataNode.h"
#include "Environment.h"
#include "Evaluator.h"
#include "Eval_PrintTree.h"

using Data = boost::variant<
    int,
    std::function<int(int,int)>
>;

using DataTree = shaka::DataNode<Data>;

using Environment =
    shaka::Environment<std::string, std::shared_ptr<DataTree>>;

TEST(Evaluator_mock, initialization) {
    std::shared_ptr<DataTree> root = std::make_shared<DataTree>([](int left, int right){
        return left + right;
    });

    Environment env(nullptr);
    root->push_child(1);
    root->push_child(2);
}

TEST(Evaluator_mock, test_print_all) {

    // Create a function at the root.
    std::shared_ptr<DataTree> root = std::make_shared<DataTree>([](int left, int right){
        return left + right;
    });
    // Push the children onto the root.
    root->push_child(1);
    root->push_child(2);
    root->push_child(3);

    // Create the environment shared ptr.
    auto env = std::make_shared<Environment>(nullptr);

    // Initialize the Evaluator object with the correct environment and root node.
    shaka::Evaluator<Data, std::string, std::shared_ptr<DataTree>> evaluator(
        env,
        root
    );

    evaluator.evaluate(shaka::eval::PrintTree<
        Data,
        std::string,
        std::shared_ptr<DataTree>,
        std::cout
    >());

    auto result = evaluator.get_node();

    //shaka::eval::PrintAll strategy(
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
