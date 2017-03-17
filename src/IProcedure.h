#ifndef SHAKA_IPROCEDURE_H
#define SHAKA_IPROCEDURE_H

#include <memory>
#include <vector>

#include "IDataNode.h"

namespace shaka {

template <typename Data>
class IProcedure {
    /// @brief Takes in arguments and then applies the function to them.
    ///
    /// Can possibly return multiple values as required by Scheme.
    virtual std::vector<std::shared_ptr<IDataNode<Data>>>
        call(std::vector<std::shared_ptr<IDataNode<Data>>> v) = 0; 
    virtual std::size_t         get_fixed_arity() const = 0;
    virtual bool                is_variable_arity() const = 0;
};

} // namespace shaka

#endif // SHAKA_IPROCEDURE_H
