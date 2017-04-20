#ifndef SHAKA_PROCCALL_H
#define SHAKA_PROCCALL_H

#include "core//base/IEvaluatorStrategy.h"

// attempts to get the procedure bound in the current environment
// and call it on the arguments condained as the child nodes of the
// list node that the procedure is called on
// returns a pointer to the list node with its child node(s)
// updated to be the result(s) of the procedure call

namespace shaka {
namespace eval {

class ProcCall : public shaka::IEvaluatorStrategy {
    
	/// @brief Evaluates a procedure call within the current environment
    virtual NodePtr evaluate(
        NodePtr list,
        EnvPtr env
    ) override; 
};

} // namespace eval
} // namespace shaka
#endif // SHAKA_PROCCALL_H
