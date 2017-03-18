#ifndef SHAKA_PROCEDURE_H
#define SHAKA_PROCEDURE_H

#include <vector>

#include "IDataNode.h"
#include "Environment.h"
#include "Evaluator.h"
#include "IProcedure.h"

#include "Eval_Expression.h"

namespace shaka {

class Procedure : public IProcedure<
    shaka::Data
> {
public:
    using Key = shaka::Symbol;
    using Data = shaka::Data;
    using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;

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
    /// Assumes that the input nodes are already evaluated to their correct,
    /// desired input forms.
    ///
    /// Can possibly return multiple values as required by Scheme,
    /// which is why they're a vector.
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
            /*
            // If we have a symbol, bind it.
            if(auto* symbol =
                shaka::get<shaka::Symbol>(args_symbol_ptr->get_data().get())) {
                // Set the value in our current environment
                this->curr_env->set_value(*symbol, v[i]);
            } else {
                /// @todo Define better semantics for procedure call
                ///       failure.
                // Failure
                return std::vector<std::shared_ptr<IDataNode<Data>>>{nullptr};
            }
            */
        }

        // Setup an Evaluator on the current environment and
        // a copy of the body root node.
        //
        shaka::Evaluator evaluator(body_root, curr_env);

        // Evaluate the body of the procedure on the right side.
        //
        // DO NOT DESTROY THE TREE
        auto result = evaluator.evaluate(shaka::eval::Expression());

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

    virtual std::size_t         get_fixed_arity() const {
        return fixed_arity;
    }

    virtual bool                is_variable_arity() const {
        return variable_arity;
    }

private:
    std::shared_ptr<IEnvironment<Key, Value>> parent_env;
    std::shared_ptr<IEnvironment<Key, Value>>  curr_env;
    std::shared_ptr<IDataNode<Data>>          body_root;
    std::size_t                               fixed_arity;
    bool                                      variable_arity;
};

} // namespace shaka


#endif // SHAKA_PROCEDURE_H
