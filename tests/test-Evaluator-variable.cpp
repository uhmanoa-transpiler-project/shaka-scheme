#include "gtest/gtest.h"

#include <functional>
#include <algorithm>
#include <numeric>
#include <memory>
#include <boost/variant.hpp>

#include "DataNode.h"
#include "Environment.h"
#include "Evaluator.h"
#include "Eval_Variable.h"
#include "Symbol.h"
#include "IDataNode.h"

#include "Procedure.h"

#include "Eval_Variable_impl.h"

using DataTree = shaka::DataNode<shaka::Data>;
using IDataTree = shaka::IDataNode<shaka::Data>;
using Environment =
    shaka::Environment<shaka::Symbol, std::shared_ptr<IDataTree>>;

TEST(Evaluator_variable, initializing){
    std::shared_ptr<DataTree> variable = std::make_shared<DataTree>(shaka::Symbol("x"));
    std::shared_ptr<DataTree> value = std::make_shared<DataTree>(shaka::Number(2));

    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

    env -> set_value(shaka::Symbol("x"), value);

    shaka::Evaluator evaluator(
        variable,
        env
    );

    auto result = evaluator.evaluate( shaka::eval::Variable() );

    ASSERT_EQ(shaka::get<shaka::Number>(*result->get_data()) , 
            shaka::get<shaka::Number>(*value->get_data()));

}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
