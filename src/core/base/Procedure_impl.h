#ifndef SHAKA_PROCEDURE_IMPL_H
#define SHAKA_PROCEDURE_IMPL_H

#include "Procedure.h"

#include "Evaluator.h"

#include "Eval_Expression.h"
#include "Eval_ProcedureBody.h"

#include "Eval_ProcedureBody_impl.h"

namespace shaka {

std::vector<std::shared_ptr<IDataNode<Data>>> 
Procedure::call (std::vector<std::shared_ptr<IDataNode<Data>>> v) {
    using Data = shaka::Data;

    // Get the arguments, bind them without evaluating to the
    // names in the arguments subtree (the first child) of this
    // root node.
    auto args_list_root = this->body_root->get_child(0);
    auto env = this->curr_env;

    /// For each child, verify it's a symbol.
    for (
        std::size_t i = 0;
        i < args_list_root->get_num_children();
        ++i
    ) {
        // Get the child node pointer.
        auto args_symbol_ptr = args_list_root->get_child(i);
        // If we have a symbol, bind it.
        if(auto* symbol =
            shaka::get<shaka::Symbol>(args_symbol_ptr->get_data().get())) {
            // Set the value in our current environment
            env->set_value(*symbol, v[i]);
        } else {
            /// @todo Define better semantics for procedure call
            ///       failure.
            // Failure
            throw std::runtime_error("Procedure: argument list member node is not a Symbol");
            return std::vector<std::shared_ptr<IDataNode<Data>>>{nullptr};
        }
    }
    // Setup an Evaluator on the current environment and
    // a copy of the body root node.
    //
    shaka::Evaluator evaluator(body_root->get_child(1), env);

    // Evaluate the body of the procedure on the right side.
    //
    // DO NOT DESTROY THE TREE
    auto result = evaluator.evaluate(shaka::eval::ProcedureBody());

    // If the root of the result list is multiple values,
    // then you'll need to get a multiple value list.
    //
    // Tuples, maybe? Hm...
    //
    auto return_values =
        std::vector<std::shared_ptr<IDataNode<Data>>>();

    // Then, return the list.
    return_values.push_back(result);
    
    return return_values;
}

}

#endif //SHAKA_PROCEDURE_IMPL_H
