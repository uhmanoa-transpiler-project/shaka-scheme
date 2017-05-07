#ifndef SHAKA_CORE_EVAL_SETUPTOPLEVEL_IMPL_H
#define SHAKA_CORE_EVAL_SETUPTOPLEVEL_IMPL_H

#include "core/base/Core.h"
#include "core/eval/SetupTopLevel.h"
#include "core/eval/Define.h"

#include "core/proc/primitives.h"
#include "core/proc/Numbers_Arithmetic_impl.h"
#include "core/proc/Pairs_and_Lists_impl.h"
#include "core/proc/Numbers_impl.h"
namespace shaka { 
    
/// Encapsulates the EvaluatorStrategy classes
namespace eval {

/// @brief returns a std::shared_ptr to the child node
NodePtr SetupTopLevel::evaluate(
    NodePtr node,
    EnvPtr env
) {
    //std::cout << "@SetupTopLevel" << std::endl;

    // Turn off node unused warning.
    static_cast<void>(node);

    // These procedures come from core/proc/primitives.h
    //
    // They implement the primitive expressions as defined in R7RS.
    env->set_value(Symbol("define"),
                   make_node(PrimitiveProcedure(shaka::proc::define, 2)));

    env->set_value(Symbol("quote"),
                   make_node(PrimitiveProcedure(shaka::proc::quote, 1)));

    env->set_value(Symbol("lambda"),
                   make_node(PrimitiveProcedure(shaka::proc::lambda, 2, true)));

    env->set_value(Symbol("if"),
                   make_node(PrimitiveProcedure(shaka::proc::if_expr, 2, true)));


    // Numbers Arithmetic section.
    env->set_value(Symbol("+"),
                   make_node(NativeProcedure(shaka::stdproc::add, 1, true)));

    env->set_value(Symbol("-"),
                   make_node(NativeProcedure(shaka::stdproc::sub, 1, true)));

    env->set_value(Symbol("*"),
                   make_node(NativeProcedure(shaka::stdproc::mul, 1, true)));

    env->set_value(Symbol("/"),
                   make_node(NativeProcedure(shaka::stdproc::div, 1, true)));

    env->set_value(Symbol("abs"),
                   make_node(NativeProcedure(shaka::stdproc::abs, 1)));

    env->set_value(Symbol("floor"),
                   make_node(NativeProcedure(shaka::stdproc::floor, 1)));

    env->set_value(Symbol("ceiling"),
                   make_node(NativeProcedure(shaka::stdproc::ceiling, 1)));

    env->set_value(Symbol("truncate"),
                   make_node(NativeProcedure(shaka::stdproc::truncate, 1)));

    env->set_value(Symbol("round"),
                   make_node(NativeProcedure(shaka::stdproc::round, 1)));

    env->set_value(Symbol("quotient"),
                   make_node(NativeProcedure(shaka::stdproc::quotient, 2)));

    env->set_value(Symbol("remainder"),
                   make_node(NativeProcedure(shaka::stdproc::remainder, 2)));

    env->set_value(Symbol("modulo"),
                   make_node(NativeProcedure(shaka::stdproc::modulo, 2)));

    env->set_value(Symbol("gcd"),
                   make_node(NativeProcedure(shaka::stdproc::gcd, 0, true)));

    env->set_value(Symbol("lcm"),
                   make_node(NativeProcedure(shaka::stdproc::lcm, 0, true)));

    env->set_value(Symbol("numerator"),
                   make_node(NativeProcedure(shaka::stdproc::numerator, 1)));

    env->set_value(Symbol("denominator"),
                   make_node(NativeProcedure(shaka::stdproc::denominator, 1)));

    env->set_value(Symbol("exp"),
                   make_node(NativeProcedure(shaka::stdproc::exp, 1)));

    env->set_value(Symbol("log"),
                   make_node(NativeProcedure(shaka::stdproc::log, 1)));

    env->set_value(Symbol("sqrt"),
                   make_node(NativeProcedure(shaka::stdproc::sqrt, 1)));

    //env->set_value(Symbol("logm"),
    //               make_node(NativeProcedure(shaka::stdproc::log, 1)));


    //env->print_bindings(std::cout);
	
	// Pairs and Lists section

	env->set_value(Symbol("cons"),
			make_node(NativeProcedure(shaka::stdproc::cons, 2)));

	env->set_value(Symbol("car"),
			make_node(NativeProcedure(shaka::stdproc::car, 1)));

	env->set_value(Symbol("cdr"),
			make_node(NativeProcedure(shaka::stdproc::cdr, 1)));

	env->set_value(Symbol("list"),
			make_node(NativeProcedure(shaka::stdproc::list, 0, true)));
	env->set_value(Symbol("pair?"),
			make_node(NativeProcedure(shaka::stdproc::pairp, 1)));
	env->set_value(Symbol("null?"),
			make_node(NativeProcedure(shaka::stdproc::nullp, 1)));
	env->set_value(Symbol("list?"),
			make_node(NativeProcedure(shaka::stdproc::listp, 1)));

	// Numeric Predicates

	env->set_value(Symbol("zero?"),
			make_node(NativeProcedure(shaka::stdproc::zerop, 1)));

	return nullptr;
}


} // namespace eval

} // namespace shaka

#endif // SHAKA_CORE_EVAL_SETUPTOPLEVEL_IMPL_H
