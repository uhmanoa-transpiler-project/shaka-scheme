#ifndef SHAKA_CORE_PROCEDURE_IMPL_H
#define SHAKA_CORE_PROCEDURE_IMPL_H

#include "core/base/Evaluator.h"
#include "core/base/Procedure.h"
#include "core/eval/ProcedureBody.h"

#include "core/eval/ProcedureBody_impl.h"

namespace shaka {

std::vector<std::shared_ptr<DataNode>> 
Procedure::call (std::vector<std::shared_ptr<DataNode>> v,
                    std::shared_ptr<Environment>    env) {

    // Get the arguments, bind them without evaluating to the
    // names in the arguments subtree (the first child) of this
    // root node.
    auto args_list_root = this->body_root->car();
    auto curr_env = this->curr_env;

    /// For each child, verify it's a symbol.
    for (
        int i = 0;
        i < (int)args_list_root->length();
        ++i
    ) {
        // Get the child node pointer.
        auto args_symbol_ptr = args_list_root->car();
        // If we have a symbol, bind it.
        if(args_symbol_ptr->is_symbol()){
            Data symbol = args_symbol_ptr->get_data();
            Data value = (*v[i]).get_data();
            // Set the value in our current environment
            curr_env->set_value(shaka::get<shaka::Symbol>(symbol), value);
        } else {
            /// @todo Define better semantics for procedure call
            ///       failure.
            // Failure
            throw std::runtime_error("Procedure: argument list member node is not a Symbol");
            return std::vector<std::shared_ptr<DataNode>>{nullptr};
        }
        args_list_root = args_list_root->cdr();
    }
    // Setup an Evaluator on the current environment and
    // a copy of the body root node.
    //
    shaka::Evaluator evaluator(this->body_root->cdr(), curr_env);

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
        std::vector<std::shared_ptr<DataNode>>();

    // Then, return the list.
    return_values.push_back(result);
    
    return return_values;
};

std::ostream& operator<< (std::ostream& lhs, const shaka::Procedure& rhs) {
    lhs << "#<procedure>";
    return lhs;
}

bool operator== (const Procedure& lhs, const Procedure& rhs) {
    if (lhs.fixed_arity == rhs.fixed_arity) {
       if(lhs.variable_arity ==rhs.variable_arity){
           if(lhs.body_root==rhs.body_root)
            return true;
       }
    }
    return false;
}

}

#endif //SHAKA_PROCEDURE_IMPL_H
