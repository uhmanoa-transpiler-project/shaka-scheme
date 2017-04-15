#ifndef SHAKA_PROCEDURE_H
#define SHAKA_PROCEDURE_H

#include <vector>

#include "core/base/DataNode.h"
#include "core/base/Environment.h"    // safe

#include "core/base/IProcedure.h"

namespace shaka {

class Procedure : public IProcedure {
public:
    using Key = shaka::Symbol;
    using Data = shaka::Data;
    using Value = Data; 

    Procedure(std::shared_ptr<Environment> parent_env,
              std::shared_ptr<DataNode>                 body_root,
              std::size_t                               fixed_arity,
              bool                                      variable_arity = false) :
        parent_env(parent_env),
        curr_env(std::make_shared<shaka::Environment>(
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
    virtual std::vector<std::shared_ptr<DataNode>> 
    call (std::vector<std::shared_ptr<DataNode>> v,
          std::shared_ptr<Environment>           env);

    virtual std::size_t         get_fixed_arity() const {
        return fixed_arity;
    }

    virtual bool                is_variable_arity() const {
        return variable_arity;
    }

private:
    std::shared_ptr<Environment>    parent_env;
    std::shared_ptr<Environment>    curr_env;
    std::shared_ptr<DataNode>       body_root;
    std::size_t                     fixed_arity;
    bool                            variable_arity;
};

} // namespace shaka


#endif // SHAKA_PROCEDURE_H
