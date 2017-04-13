#ifndef SHAKA_EVAL_BOOLEAN_IMPL_H
#define SHAKA_EVAL_BOOLEAN_IMPL_H

#include "Data.h"
#include "Symbol.h"
#include "DataNode.h"
#include "Boolean.h"

#include "EvaluatorStrategyDefinitions.h"

#include "Evaluator.h"
#include "IEvaluatorStrategy.h"

#include "Eval_Define.h"
#include "Eval_Variable.h"
#include "Eval_Quote.h"
#include "Eval_Lambda.h"
#include "Eval_Proccall.h"

#include "Eval_Boolean.h"

#include "Eval_PrintTree.h"

#include "Eval_Define_impl.h"
#include "Eval_Variable_impl.h"
#include "Eval_Proccall_impl.h"
#include "Eval_Lambda_impl.h"


namespace shaka { 
    
/// Encapsulates the EvaluatorStrategy classes
namespace eval {

/// @brief returns a std::shared_ptr to the child node

using T = shaka::Data;
using Key = shaka::Symbol;
using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;

std::shared_ptr<IDataNode<T>> Boolean::evaluate(
    std::shared_ptr<IDataNode<T>> node,
    std::shared_ptr<IEnvironment<Key, Value>> env
) {
    
    if(node->get_data()->type() == typeid(shaka::Boolean)){
           Value bool_node = 
                std::make_shared<shaka::DataNode<T>>(*node->get_data());
           return bool_node;     
    }
    else {
        Value bool_node = 
                std::make_shared<shaka::DataNode<T>>(shaka::Boolean(true));
        return bool_node;        
    }
    
}


} // namespace eval

} // namespace shaka

#endif // SHAKA_EVAL_BOOLEAN_H