#ifndef SHAKA_CORE_PROC_PRIMITIVES_H
#define SHAKA_CORE_PROC_PRIMITIVES_H

#include "core/base/NativeProcedure.h"
#include "core/base/Evaluator.h"

#include "core/eval/Eval.h"

namespace shaka {
namespace proc  {

using Args = std::vector<NodePtr>;
using Function = std::function<Args(Args, EnvPtr)>;

Args define(Args l, EnvPtr e) {
    //std::cout << "@proc.define" << std::endl;
    auto args = make_node(DataNode::list());
    for (auto it : l) {
        args->append(DataNode::list(it));
    }

	return {shaka::Evaluator(args, e).evaluate(shaka::eval::Define())};	
}

Args quote(Args l, EnvPtr e) {
    //std::cout << "@proc.quote" << std::endl;
    auto args = make_node(DataNode::list());
    for (auto it : l) {
        args->append(DataNode::list(it));
    }
	return {shaka::Evaluator(args, e).evaluate(shaka::eval::Quote())};	
}

Args variable(Args l, EnvPtr e) {
    //std::cout << "@proc.variable" << std::endl;
    auto args = make_node(DataNode::list());
    for (auto it : l) {
        args->append(DataNode::list(it));
    }
	return {shaka::Evaluator(args, e).evaluate(shaka::eval::Variable())};	
}

Args lambda(Args l, EnvPtr e) {
    //std::cout << "@proc.lambda" << std::endl;
    auto args = make_node(DataNode::list());
    for (auto it : l) {
        args->append(DataNode::list(it));
    }
	return {shaka::Evaluator(args, e).evaluate(shaka::eval::Lambda())};
}

Args if_expr(Args l, EnvPtr e) {
    //std::cout << "@proc.if" << std::endl;
    auto args = make_node(DataNode::list());
    for (auto it : l) {
        args->append(DataNode::list(it));
    }
	return {shaka::Evaluator(args, e).evaluate(shaka::eval::If())};
}
} // namespace shaka 
} // namespace proc  
#endif // SHAKA_CORE_PROC_PRIMITIVES
