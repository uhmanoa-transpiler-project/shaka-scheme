#ifndef SHAKA_STDPROC_EQUIVALENCE_PREDICATES_IMPL_H
#define SHAKA_STDPROC_EQUIVALENCE_PREDICATES_IMPL_H

using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
using Args = std::vector<Value>;
using Function = std::function<Args(Args)>;

/// (eqv? obj1 obj2)
Args equivalent(Args a){
if((*a[0]->get_data().type()) == typeid(shaka::Number) && (*a[1]->get_data().type()) == typeid(shaka::Number)){
	if(*a[0]->get_data() == *a[1]->get_data())
		return{std::make_shared<shaka::DataNode<shaka::Data>>
			(shaka::get<shaka::Boolean>(true))};
	else{

		return{std::make_shared<shaka::DataNode<shaka::Data>>
			(shaka::get<shaka::Boolean>(false))};
	}
}

if((*a[0]->get_data().type()) == typeid(shaka::Symbol) && (*a[1]->get_data().type()) == typeid(shaka::Symbol)){
	if(*a[0]->get_data() == *a[1]->get_data())
		return{std::make_shared<shaka::DataNode<shaka::Data>>
			(shaka::get<shaka::Boolean>(true))};
	else{

		return{std::make_shared<shaka::DataNode<shaka::Data>>
			(shaka::get<shaka::Boolean>(false))};
	}
}
if((*a[0]->get_data().type()) == typeid(shaka::String) && (*a[1]->get_data().type()) == typeid(shaka::String)){
	if(*a[0]->get_data() == *a[1]->get_data())
		return{std::make_shared<shaka::DataNode<shaka::Data>>
			(shaka::get<shaka::Boolean>(true))};
	else{

		return{std::make_shared<shaka::DataNode<shaka::Data>>
			(shaka::get<shaka::Boolean>(false))};
	}
}

if((*a[0]->get_data().type()) == typeid(shaka::Boolean) && (*a[1]->get_data().type()) == typeid(shaka::Boolean)){
	if(*a[0]->get_data().get_num_children() == 0 && *a[1]->get_data().get_num_children() == 0)
		return{std::make_shared<shaka::DataNode<shaka::Data>>
			(shaka::get<shaka::Boolean>(true))};
	else{

		return{std::make_shared<shaka::DataNode<shaka::Data>>
			(shaka::get<shaka::Boolean>(false))};
	}
}

if((*a[0]->get_data().type()) == typeid(shaka::MetaTag::LIST) && (*a[1]->get_data().type()) == typeid(shaka::MetaTag::LIST)){
	if(*a[0]->get_data() == *a[1]->get_data())
		return{std::make_shared<shaka::DataNode<shaka::Data>>
			(shaka::get<shaka::Boolean>(true))};
	else{

		return{std::make_shared<shaka::DataNode<shaka::Data>>
			(shaka::get<shaka::Boolean>(false))};
	}
}
else{	
	return{std::make_shared<shaka::DataNode<shaka::Data>>
		(shaka::get<shaka::Boolean>(false))};
}

}
Function eqv = equivalent;
/// (eq? obj1 obj2)
/// (equal? obj1 obj2)

#endif // SHAKA_STDPROC_EQUIVALENCE_PREDICATES_IMPL_H
