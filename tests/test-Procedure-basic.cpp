#include "gtest/gtest.h"

#include <functional>
#include <algorithm>
#include <numeric>

#include <boost/variant.hpp>

#include "DataNode.h"
#include "Environment.h"
#include "Procedure.h"
#include "Evaluator.h"

using IDataTree = shaka::IDataNode<shaka::Data>;
using DataTree = shaka::DataNode<shaka::Data>;

using Environment =
    shaka::Environment<shaka::Symbol, std::shared_ptr<IDataTree>>;

/// @brief Test initialization of a DataTree tree.
TEST(Procedure_basic, initialization_DataTree) {
    auto root = std::make_shared<DataTree>(shaka::MetaTag::LIST);

    ASSERT_EQ(
        shaka::get<shaka::MetaTag>(*root->get_data()),
        shaka::MetaTag::LIST
    ); 
}

/// @brief Test initialization of a Procedure
TEST(Procedure_basic, initialization_Procedure) {

    // Create the root node. 
    auto root = std::make_shared<DataTree>(shaka::MetaTag::LAMBDA);

    // Create the arguments list
    auto args_list = root->push_child(shaka::MetaTag::LIST);
    args_list->push_child(shaka::MetaTag::LIST)->push_child(shaka::Symbol("a"));
    // (lambda (a) ...)

    // Create the body expression list
    auto body_root = root->push_child(shaka::MetaTag::LIST);

    // (lambda (a) a)
    body_root->push_child(shaka::Symbol("a"));

    // Create a root environment.
    auto env  = std::make_shared<Environment>(nullptr);
    auto i_env = std::static_pointer_cast<shaka::IEnvironment<shaka::Symbol, std::shared_ptr<IDataTree>>>(env);

    // Create the procedure with the parent being the root env,
    // and provide the DataTree tree as the body of the procedure.
    shaka::Procedure<
        shaka::Data,
        shaka::Symbol,
        std::shared_ptr<shaka::IDataNode<shaka::Data>>
    > proc(
        i_env,
        body_root,
        body_root->get_num_children(),
        false 
    );

    ASSERT_EQ(
        shaka::get<shaka::MetaTag>(*root->get_data()),
        shaka::MetaTag::LAMBDA
    );
    /*
    */
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
