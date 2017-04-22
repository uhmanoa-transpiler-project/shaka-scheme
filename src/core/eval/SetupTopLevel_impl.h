#ifndef SHAKA_CORE_EVAL_SETUPTOPLEVEL_IMPL_H
#define SHAKA_CORE_EVAL_SETUPTOPLEVEL_IMPL_H

#include "core/base/Core.h"
#include "core/eval/SetupTopLevel.h"
#include "core/eval/Define.h"

#include "core/proc/primitives.h"


namespace shaka { 
    
/// Encapsulates the EvaluatorStrategy classes
namespace eval {

/// @brief returns a std::shared_ptr to the child node
NodePtr SetupTopLevel::evaluate(
    NodePtr node,
    EnvPtr env
) {
    std::cout << "@SetupTopLevel" << std::endl;

    // These procedures come from core/proc/primitives.h
    //
    // They implement the primitive expressions as defined in R7RS.
    env->set_value(Symbol("define"),
                   make_node(PrimitiveProcedure(shaka::proc::define, 2)));

    env->print_bindings(std::cout);

}


} // namespace eval

} // namespace shaka

#endif // SHAKA_CORE_EVAL_SETUPTOPLEVEL_IMPL_H
