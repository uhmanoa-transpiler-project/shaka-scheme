#ifndef SHAKA_PROCEDURE_H
#define SHAKA_PROCEDURE_H

#include <vector>

#include "Data.h"

#include "IDataNode.h"      // safe
#include "Environment.h"    // safe

#include "IProcedure.h"
#include "Symbol.h"

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
    call (std::vector<std::shared_ptr<IDataNode<Data>>> v);

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

std::ostream& operator<< (std::ostream& lhs, const shaka::Procedure rhs) {
    lhs << "Procedure(" << rhs.get_fixed_arity();
    if (rhs.is_variable_arity()) { lhs << "+"; }
    lhs << ')';
    return lhs;
}


#endif // SHAKA_PROCEDURE_H
