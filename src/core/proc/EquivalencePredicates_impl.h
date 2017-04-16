#ifndef SHAKA_STDPROC_EQUIVALENCE_PREDICATES_IMPL_H
#define SHAKA_STDPROC_EQUIVALENCE_PREDICATES_IMPL_H
 
#include "core/base/Boolean.h"
#include "core/base/Procedure.h"
#include "core/base/DataNode.h"
#include "core/base/Data.h"

#include "core/base/Environment.h"
#include <functional>
#include <typeinfo>
#include <vector>
namespace shaka{
namespace stdproc{
using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
using EnvPtr = std::shared_ptr<shaka::Environment>;
Args eqv(Args list, EnvPtr env){
	if(list[0]->is_number() && list[1]->is_number()){
		if(*list[0] == *list[1]){
			return {std::make_shared<shaka::DataNode>(shaka::Boolean(true))};
		}
		else{

			return {std::make_shared<shaka::DataNode>(shaka::Boolean(false))};
		}
	}
	if(list[0]->is_symbol() && list[1]->is_symbol()){
		if(*list[0] == *list[1]){
			return {std::make_shared<shaka::DataNode>(shaka::Boolean(true))};
		}
		else{

			return {std::make_shared<shaka::DataNode>(shaka::Boolean(false))};
		}
	}
	if(list[0]->is_boolean() && list[1]->is_boolean()){
		if(*list[0] == *list[1]){
			return {std::make_shared<shaka::DataNode>(shaka::Boolean(true))};
		}
		else{

			return {std::make_shared<shaka::DataNode>(shaka::Boolean(false))};
		}
	}
	if(list[0]->is_null() && list[1]->is_null()){
		if(*list[0] == *list[1]){
			return {std::make_shared<shaka::DataNode>(shaka::Boolean(true))};
		}
		else{

			return {std::make_shared<shaka::DataNode>(shaka::Boolean(false))};
		}
	}
	if(list[0]->is_pair() && list[1]->is_pair()){
		if(list[0].get() == list[1].get()){
			return {std::make_shared<shaka::DataNode>(shaka::Boolean(true))};
		}
		else{

			return {std::make_shared<shaka::DataNode>(shaka::Boolean(false))};
		}
	}

	if(list[0]->is_string() && list[1]->is_string()){
		if(list[0].get() == list[1].get()){
			return {std::make_shared<shaka::DataNode>(shaka::Boolean(true))};
		}
		else{

			return {std::make_shared<shaka::DataNode>(shaka::Boolean(false))};
		}
	}
	else{
		return {std::make_shared<shaka::DataNode>(shaka::Boolean(false))};
	}
}
Args eq(Args list, EnvPtr env){

	if(list[0]->is_number() && list[1]->is_number()){
		if(*list[0] == *list[1]){
			return {std::make_shared<shaka::DataNode>(shaka::Boolean(true))};
		}
		else{

			return {std::make_shared<shaka::DataNode>(shaka::Boolean(false))};
		}
	}
	if(list[0]->is_symbol() && list[1]->is_symbol()){
		if(*list[0] == *list[1]){
			return {std::make_shared<shaka::DataNode>(shaka::Boolean(true))};
		}
		else{

			return {std::make_shared<shaka::DataNode>(shaka::Boolean(false))};
		}
	}
	if(list[0]->is_boolean() && list[1]->is_boolean()){
		if(*list[0] == *list[1]){
			return {std::make_shared<shaka::DataNode>(shaka::Boolean(true))};
		}
		else{

			return {std::make_shared<shaka::DataNode>(shaka::Boolean(false))};
		}
	}
	if(list[0]->is_null() && list[1]->is_null()){
		if(*list[0] == *list[1]){
			return {std::make_shared<shaka::DataNode>(shaka::Boolean(true))};
		}
		else{

			return {std::make_shared<shaka::DataNode>(shaka::Boolean(false))};
		}
	}
	if(list[0]->is_pair() && list[1]->is_pair()){
		if(list[0].get() == list[1].get()){
			return {std::make_shared<shaka::DataNode>(shaka::Boolean(true))};
		}
		else{

			return {std::make_shared<shaka::DataNode>(shaka::Boolean(false))};
		}
	}

	if(list[0]->is_string() && list[1]->is_string()){
		if(list[0].get() == list[1].get()){
			return {std::make_shared<shaka::DataNode>(shaka::Boolean(true))};
		}
		else{

			return {std::make_shared<shaka::DataNode>(shaka::Boolean(false))};
		}
	}
	else{
		return {std::make_shared<shaka::DataNode>(shaka::Boolean(false))};
	}

}

Args equal(Args list, EnvPtr env){
	if(*list[0] == *list[1]){
		return {std::make_shared<shaka::DataNode>(shaka::Boolean(true))};
	}
	else{
		return {std::make_shared<shaka::DataNode>(shaka::Boolean(false))};
	}
}
}//namespace stdproc
}//namespace shaka
/// (eqv? obj1 obj2)
/// (eq? obj1 obj2)
/// (equal? obj1 obj2)

#endif // SHAKA_STDPROC_EQUIVALENCE_PREDICATES_IMPL_H
