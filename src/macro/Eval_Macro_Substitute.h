#ifndef SHAKA_EVAL_MACRO_SUBSTITUTE
#define SHAKA_EVAL_MACRO_SUBSTITUTE

#include "IEvaluatorStrategy.h"

namespace shaka {
namespace eval {

/// @brief Prints the types of all of the T in the tree.
class Macro_Substitute : public IEvaluatorStrategy {
public:
    using T = shaka::Data;
    using Key = shaka::Symbol;
    using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;

    /// @brief Prints the type of all the items in the tree recursively.
    std::shared_ptr<IDataNode<T>> evaluate(
        std::shared_ptr<IDataNode<T>> node,
        std::shared_ptr<IEnvironment<Key, Value>> env
    ); 
};

}
}

#endif // SHAKA_EVAL_MACRO_SUBSTITUTE
