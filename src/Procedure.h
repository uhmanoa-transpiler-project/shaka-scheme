#ifndef SHAKA_PROCEDURE_H
#define SHAKA_PROCEDURE_H

#include <vector>

#include "IEnvironment.h"
#include "EvaluatorStrategies.h"
//#include "Evaluator.h"

#include "IProcedure.h"

namespace shaka {

template <typename Data, typename Key, typename Value>
class Procedure : public IProcedure<Data> {
public:
    Procedure(std::shared_ptr<IEnvironment<Key, Value>> parent_env,
              std::shared_ptr<IDataNode<Data>>          body_root) :
        parent_env(parent_env),
        body_root(body_root) {}

    /// @brief Takes in arguments and then applies the function to them.
    ///
    /// Can possibly return multiple values as required by Scheme.
    virtual std::vector<Data>   call(std::vector<Data> args) {
        std::cout << "lol Procedure::call" << std::endl;
        return std::vector<Data>();
    }

    virtual std::size_t         get_fixed_arity() const {
        std::cout << "lol Procedure::get_fixed_arity" << std::endl;
        return 0;
    }

    virtual bool                is_variable_arity() const {
        std::cout << "lol Procedure::is_variable_arity" << std::endl;
        return false;
    }

private:
    std::shared_ptr<IEnvironment<Key, Value>> parent_env;
    std::shared_ptr<IDataNode<Data>>          body_root;
};

} // namespace shaka

#endif // SHAKA_PROCEDURE_H
