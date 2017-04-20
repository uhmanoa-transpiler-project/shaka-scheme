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
	std::shared_ptr<shaka::Environment> env){
if(shaka::get<shaka::Symbol>(list->get_data()) == shaka::Symbol("if")){
	

	if((shaka::get<shaka::Boolean>((shaka::Evaluator(list->car()->cdr(), env).evaluate(shaka::eval::Expression())->get_data())))!= shaka::Boolean(false)) {

		return shaka::Evaluator(list->car()->cdr()->cdr(), env).evaluate(shaka::eval::Expression());
		
	}
	else{
		
		return shaka::Evaluator(list->car()->cdr()->cdr()->cdr(), env).evaluate(shaka::eval::Expression());
	}

}
else {

	return nullptr;

}
}


} //namespace eval

} //namespace shaka
















#endif //SHAKA_IF_H
