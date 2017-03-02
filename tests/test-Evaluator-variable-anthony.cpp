#include "gtest/gtest.h"

#include <functional>
#include <algorithm>
#include <numeric>
#include <memory>
#include <boost/variant.hpp>

#include "DataNode.h"
#include "Environment.h"
#include "Evaluator.h"
#include "Eval_variable-anthony.h"
#include "Symbol.h"
#include "IDataNode.h"


using DataTree = shaka::DataNode<shaka::Data>;
using IDataTree = shaka::IDataNode<shaka::Data>;
using Environment =
    shaka::Environment<shaka::Symbol, std::shared_ptr<IDataTree>>;

TEST(Evaluator_variable, initializing){
    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::Symbol("x"));
    std::shared_ptr<DataTree> root1 = std::make_shared<DataTree>(2);

    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

    env -> set_value(shaka::Symbol("x"), root1);

    shaka::Evaluator<shaka::Data, shaka::Symbol, std::shared_ptr<DataTree>> evaluator(
	    env, 
	    root
     );

   ASSERT_EQ(evaluator.evaluate(shaka::eval::Variable<shaka::Data, shaka::Symbol, std::shared_ptr<IDataTree>>()), root1);
    
}





/*TEST(Evaluator_mock, initialization) {
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
}*/

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
