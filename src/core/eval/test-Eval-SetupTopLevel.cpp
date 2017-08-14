#include <gtest/gtest.h>

#include "core/eval/SetupTopLevel_impl.h"

using namespace shaka;

TEST(Eval_SetupTopLevel, initialization) {

    // Create a dummy, null list node.
    auto root = make_node(DataNode::list());
    // Create the global environment to setup the
    // core bindings in.
    auto env  = std::make_shared<Environment>(nullptr);
    // Do the evaluation.
    Evaluator eval(root, env);
    eval.evaluate(eval::SetupTopLevel());
}

int main (int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
