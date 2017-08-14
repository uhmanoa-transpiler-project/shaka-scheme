#ifndef SHAKA_IPROCEDURE_H
#define SHAKA_IPROCEDURE_H

#include <memory>
#include <vector>

#include "core/base/DataNode.h"
#include "core/base/Environment.h"

namespace shaka {

class IProcedure {
    using IEnvPtr = std::shared_ptr<shaka::Environment>;
    /// @brief Takes in arguments and then applies the function to them.
    ///
    /// Can possibly return multiple values as required by Scheme.
    virtual std::vector<NodePtr>
        call(std::vector<NodePtr> v, IEnvPtr env) = 0; 
    virtual std::size_t         get_fixed_arity() const = 0;
    virtual bool                is_variable_arity() const = 0;
};

} // namespace shaka

#endif // SHAKA_IPROCEDURE_H
