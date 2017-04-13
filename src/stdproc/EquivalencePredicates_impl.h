#ifndef SHAKA_STDPROC_EQUIVALENCE_PREDICATES_IMPL_H
#define SHAKA_STDPROC_EQUIVALENCE_PREDICATES_IMPL_H

#include "../Number.h"
#include "../Symbol.h"
#include "../ASCII_String.h"
#include "../Boolean.h"
#include "../IDataNode.h"
#include "../DataNode.h"
#include "../Data.h"

#include "../Procedure_impl.h"

#include <functional>
#include <typeinfo>
#include <vector>
using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
using Args = std::vector<Value>;
using Function = std::function<Args(Args)>;

/// (eqv? obj1 obj2)
Args equivalent(Args a){
shaka::Boolean c(true);
shaka::Boolean d(false);
if((*a[0]->get_data()).type() == typeid(shaka::Number) && (*a[1]->get_data()).type() == typeid(shaka::Number)){
	if(*a[0]->get_data() == *a[1]->get_data())
		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((c))};
	else{

		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((d))};
	}
}

if((*a[0]->get_data()).type() == typeid(shaka::Symbol) && (*a[1]->get_data()).type() == typeid(shaka::Symbol)){
	if(*a[0]->get_data() == *a[1]->get_data())
		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((c))};
	else{

		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((d))};
	}
}
if((*a[0]->get_data()).type() == typeid(shaka::String) && (*a[1]->get_data()).type() == typeid(shaka::String)){
	if(*a[0]->get_data() == *a[1]->get_data())
		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((c))};
	else{

		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((d))};
	}
}

if((*a[0]->get_data()).type() == typeid(shaka::Boolean) && (*a[1]->get_data()).type() == typeid(shaka::Boolean)){
	if(*a[0]->get_data() == *a[1]->get_data())
		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((c))};
	else{

		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((d))};
	}
}

if((*a[0]->get_data()).type() == typeid(shaka::MetaTag::LIST) && (*a[1]->get_data()).type() == typeid(shaka::MetaTag::LIST)){
	if(a[0]->get_num_children() == 0 && a[1]->get_num_children() == 0)
		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((c))};
	else{

		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((d))};
	}
}
else{	
	return{std::make_shared<shaka::DataNode<shaka::Data>>
		((d))};
}

}
Function eqv = equivalent;
/// (eq? obj1 obj2)

Args equivalence(Args a){
shaka::Boolean c(true);
shaka::Boolean d(false);
if((*a[0]->get_data()).type() == typeid(shaka::Number) && (*a[1]->get_data()).type() == typeid(shaka::Number)){
	if(*a[0]->get_data() == *a[1]->get_data())
		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((c))};
	else{

		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((d))};
	}
}

if((*a[0]->get_data()).type() == typeid(shaka::Symbol) && (*a[1]->get_data()).type() == typeid(shaka::Symbol)){
	if(*a[0]->get_data() == *a[1]->get_data())
		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((c))};
	else{

		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((d))};
	}
}
if((*a[0]->get_data()).type() == typeid(shaka::String) && (*a[1]->get_data()).type() == typeid(shaka::String)){
	if(*a[0]->get_data() == *a[1]->get_data())
		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((c))};
	else{

		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((d))};
	}
}

if((*a[0]->get_data()).type() == typeid(shaka::Boolean) && (*a[1]->get_data()).type() == typeid(shaka::Boolean)){
	if(*a[0]->get_data() == *a[1]->get_data())
		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((c))};
	else{

		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((d))};
	}
}

if((*a[0]->get_data()).type() == typeid(shaka::MetaTag::LIST) && (*a[1]->get_data()).type() == typeid(shaka::MetaTag::LIST)){
	if(a[0]->get_num_children() == 0 && a[1]->get_num_children() == 0)
		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((c))};
	else{

		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((d))};
	}
}
else{	
	return{std::make_shared<shaka::DataNode<shaka::Data>>
		((d))};
}

}
Function eq = equivalence;
/// (equal? obj1 obj2)

Args equality(Args a){
shaka::Boolean c(true);
shaka::Boolean d(false);
if((*a[0]->get_data()).type() == typeid(shaka::Number) && (*a[1]->get_data()).type() == typeid(shaka::Number)){
	if(*a[0]->get_data() == *a[1]->get_data())
		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((c))};
	else{

		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((d))};
	}
}

if((*a[0]->get_data()).type() == typeid(shaka::Symbol) && (*a[1]->get_data()).type() == typeid(shaka::Symbol)){
	if(*a[0]->get_data() == *a[1]->get_data())
		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((c))};
	else{

		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((d))};
	}
}
if((*a[0]->get_data()).type() == typeid(shaka::String) && (*a[1]->get_data()).type() == typeid(shaka::String)){
	if(*a[0]->get_data() == *a[1]->get_data())
		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((c))};
	else{

		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((d))};
	}
}

if((*a[0]->get_data()).type() == typeid(shaka::Boolean) && (*a[1]->get_data()).type() == typeid(shaka::Boolean)){
	if(*a[0]->get_data() == *a[1]->get_data())
		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((c))};
	else{

		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((d))};
	}
}

if((*a[0]->get_data()).type() == typeid(shaka::MetaTag::LIST) && (*a[1]->get_data()).type() == typeid(shaka::MetaTag::LIST)){
	if(a[0]->get_num_children() == 0 && a[1]->get_num_children() == 0)
		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((c))};
	else{

		return{std::make_shared<shaka::DataNode<shaka::Data>>
			((d))};
	}
}
else{	
	return{std::make_shared<shaka::DataNode<shaka::Data>>
		((d))};
}

}
Function equal = equality;

#endif // SHAKA_STDPROC_EQUIVALENCE_PREDICATES_IMPL_H
