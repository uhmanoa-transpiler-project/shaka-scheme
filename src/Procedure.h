#ifndef SHAKA_PROCEDURE_H
#define SHAKA_PROCEDURE_H

#include <vector>

#include "IEnvironment.h"
#include "EvaluatorStrategies.h"
#include "Evaluator.h"

#include "IProcedure.h"

namespace shaka {

template <typename Data, typename Key, typename Value>
class Procedure : public IProcedure<Data> {
public:
    Procedure(std::shared_ptr<IEnvironment<Key, Value>> parent_env,
              std::shared_ptr<IDataNode<Data>>          body_root,
              std::size_t                               fixed_arity,
              bool                                      variable_arity = false) :
        parent_env(parent_env),
        curr_env(std::make_shared<shaka::Environment<Key,Value>>(
            parent_env)),
        body_root(body_root),
        fixed_arity(fixed_arity),
        variable_arity(variable_arity) {}

    /// @brief Takes in arguments and then applies the function to them.
    ///
    /// Can possibly return multiple values as required by Scheme.
    virtual std::vector<std::shared_ptr<IDataNode<Data>>> 
    call (std::vector<std::shared_ptr<IDataNode<Data>>> v) {
        // Get the arguments, bind them without evaluating to the
        // names in the arguments subtree (the first child) of this
        // root node.
        auto args_list_root = this->body_root->get_child(0);

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
                shaka::get<shaka::Symbol>(&(*args_symbol_ptr))) {
                // Set the value in our current environment
                this->curr_env->set_value(*symbol, v[i]);
            } else {
                /// @todo Define better semantics for procedure call
                ///       failure.
                // Failure
                return std::vector<std::shared_ptr<DataNode<Data>>>{nullptr};
            }
        }

        // Setup an Evaluator on the current environment and
        // a copy of the body root node.
        //
        shaka::Evaluator<
            Data,
            Key,
            Value
        > evaluator(curr_env, body_root);

        // Evaluate the body of the procedure on the right side.
        //
        // DO NOT DESTROY THE TREE
        // auto result = evaluator.evaluate(shaka::eval::Procedure<
        //      Data,
        //      Key,
        //      Value
        // >());

        // If the root of the result list is multiple values,
        // then you'll need to get a multiple value list.
        //
        // Tuples, maybe? Hm...
        //
        // Then, return the list.
        
        return std::vector<std::shared_ptr<DataNode<Data>>>();
    }

    virtual std::size_t         get_fixed_arity() const {
        return fixed_arity;
    }

    virtual bool                is_variable_arity() const {
        return variable_arity;
    }

private:
    std::shared_ptr<IEnvironment<Key, Value>> parent_env;
    std::shared_ptr<Environment<Key, Value>>  curr_env;
    std::shared_ptr<IDataNode<Data>>          body_root;
    std::size_t                               fixed_arity;
    bool                                      variable_arity;
};

} // namespace shaka

#endif // SHAKA_PROCEDURE_H
