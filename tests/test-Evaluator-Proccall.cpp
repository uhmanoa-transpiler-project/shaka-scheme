
#include "gtest/gtest.h"

#include <functional>
#include <algorithm>
#include <numeric>

#include <boost/variant.hpp>

#include "DataNode.h"
#include "Environment.h"
#include "Procedure.h"
#include "Evaluator.h"

#include "Eval_Expression_impl.h"

using IDataTree = shaka::IDataNode<shaka::Data>;
using DataTree = shaka::DataNode<shaka::Data>;

using Environment =
    shaka::Environment<shaka::Symbol, std::shared_ptr<IDataTree>>;

/// @brief Test initialization of a DataTree tree.
TEST(Procedure_basic, initialization_DataTree) {
    auto list_root = std::make_shared<DataTree>(shaka::MetaTag::LIST);

    ASSERT_EQ(
        shaka::get<shaka::MetaTag>(*list_root->get_data()),
        shaka::MetaTag::LIST
    ); 
}

/// @brief Test initialization of a Procedure
TEST(Procedure_basic, initialization_Procedure) {

    // Create the root node. 
    auto root = std::make_shared<DataTree>(shaka::MetaTag::LAMBDA);

    // Create the arguments list
    auto args_list = root->push_child(shaka::MetaTag::LIST);
    args_list->push_child(shaka::Symbol("a"));
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
    shaka::Procedure proc(
        i_env,
        root,
        root->get_child(0)->get_num_children(),
        false 
    );

    ASSERT_EQ(
        shaka::get<shaka::MetaTag>(*root->get_data()),
        shaka::MetaTag::LAMBDA
    );

    ASSERT_EQ( proc.get_fixed_arity(), 1 );
    ASSERT_EQ( proc.is_variable_arity(), false );
	
	// construct a procedure call DataTree with the defined procedure as the left most child
	// and the args list node as the right child, with a child of 1
	auto proc_call_root = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::MetaTag::PROC_CALL);
	proc_call_root->push_child(proc);
	proc_call_root->push_child(shaka::MetaTag::LIST);
	proc_call_root->get_child(1)->push_child(shaka::Number(1));

	ASSERT_EQ(proc_call_root->get_num_children(), 2);
	ASSERT_EQ(proc_call_root->get_child(1)->get_num_children(), 1);


	
	/*
    std::vector<std::shared_ptr<shaka::IDataNode<shaka::Data>>> args_vector;
    args_vector.push_back(std::make_shared<shaka::DataNode<shaka::Data>>(shaka::Number(1)));
    auto result_vector = proc.call(args_vector);

    ASSERT_EQ(result_vector.size(), std::size_t(1));

    auto result = shaka::get<shaka::Number>(*result_vector[0]->get_data());
    ASSERT_EQ(shaka::Number(1), result);

	*/
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
