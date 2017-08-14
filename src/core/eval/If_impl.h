#ifndef SHAKA_IF_IMPL_H
#define SHAKA_IF_IMPL_H

#include "core/base/IEvaluatorStrategy.h"
#include "core/base/Evaluator.h"
#include "core/eval/If.h"
#include "core/eval/Expression_impl.h"
#include "core/base/DataNode.h"
#include "core/base/Data.h"
namespace shaka {

namespace eval {

	using Key = shaka::Symbol;
	using Value = std::shared_ptr<shaka::DataNode>;

std::shared_ptr<shaka::DataNode> If::evaluate(
	std::shared_ptr<shaka::DataNode> list,
	std::shared_ptr<shaka::Environment> env) {

    //std::cout << "@If" << std::endl;

    auto list_length = list->length();

    if (list_length < 2 || list_length > 3) {
        throw std::runtime_error("eval.If: Cannot evaluate if expression of invalid list length");
        return nullptr;
    }

    // First of all, evaluate the first thing in the list.
    shaka::Evaluator cond(list->car(), env);
    auto cond_value = cond.evaluate(shaka::eval::Expression());
    
    if (cond_value->get_data().type() == typeid(shaka::Boolean)) {
        //std::cout << "@If: is boolean" << std::endl;
        // If the conditional is true, then return the affirmative
        // expression's evaluation value.
        if (shaka::get<shaka::Boolean>(cond_value->get_data())
            == Boolean(false)) {
            //std::cout << "@If: negative" << std::endl;
            // If there is no third element to the list, there
            // is no negative expression to evaluate.
            if (list->cdr()->cdr()->is_null()) {
                //std::cout << "@If: negative missing" << std::endl;
                return nullptr;
            }
            // Otherwise, grab it and evaluate it, return its
            // evaluation value.
            else {
                shaka::Evaluator neg(list->cdr()->cdr()->car(), env);
                //std::cout << "@If: negative present" << std::endl;
                return neg.evaluate(shaka::eval::Expression());
            }
        }
        else {
            //std::cout << "@If: affirmative" << std::endl;
            shaka::Evaluator affirm(list->cdr()->car(), env);
            return affirm.evaluate(shaka::eval::Expression());
        }
    }
    else {
        //std::cout << "@If: affirmative" << std::endl;
        shaka::Evaluator affirm(list->cdr()->car(), env);
        return affirm.evaluate(shaka::eval::Expression());
    }
}


} //namespace eval

} //namespace shaka



#endif //SHAKA_IF_IMPL_H
