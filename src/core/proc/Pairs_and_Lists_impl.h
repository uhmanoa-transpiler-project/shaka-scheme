#ifndef SHAKA_STDPROC_PAIRS_AND_LISTS_IMPL_H
#define SHAKA_STDPROC_PAIRS_AND_LISTS_IMPL_H

#include "core/base/DataNode.h"
#include "core/base/Data.h"

#include "core/base/Environment.h"
#include <functional>
#include <typeinfo>
#include <vector>

namespace shaka {
namespace stdproc {

using Args = std::vector<NodePtr>;


using Function = std::function<Args(Args, EnvPtr)>;

namespace impl {
// (pair? obj)
// (cons obj1 obj2)
Args cons_lists(Args args, EnvPtr env) {
	static_cast<void>(env);	
	NodePtr result = std::make_shared<shaka::DataNode>(
			DataNode::cons(*args[0], *args[1]));
	Args result_vector = {result};
	return result_vector;

}
// (car pair)
Args car_lists(Args args, EnvPtr env) {
	static_cast<void>(env);
	NodePtr result = args[0]->car();
	Args result_vector = {result};
	return result_vector;
}
// (cdr pair)
Args cdr_lists(Args args, EnvPtr env) {
	static_cast<void>(env);
	NodePtr result = args[0]->cdr();
	Args result_vector = {result};
	return result_vector;
}
// (set-car! pair obj)
// (set-cdr! pair obj)

// (caar pair)
// (cadr pair)
// (cdar pair)
// (cddr pair)

// (null? obj)
// (list? obj)

// (make-list k)
// (make-list k fill)

// (list obj ...)
Args list_lists(Args args, EnvPtr env) {
	static_cast<void>(env);
	NodePtr result = std::make_shared<shaka::DataNode>(shaka::DataNode::list());

	for (int i = args.size() - 1; i >= 0; i--) {
		result = std::make_shared<shaka::DataNode>(shaka::DataNode::cons(*args[i], *result));
	}

	Args result_vector = {result};
	return result_vector;

}
// (length list)
// (append list)
// (reverse list)

// (list-tail list k)
// (list-ref list k)

// (list-set! list k obj)

// (memq obj list)
// (memv obj list)
// (member obj list)
// (member obj list compare)

// (assq obj alist)
// (assv obj alist)
// (assoc obj alist)
// (assoc obj alist compare)

// (list-copy obj)
} // namespace impl

Function cons = impl::cons_lists; 
Function car = impl::car_lists;
Function cdr = impl::cdr_lists;
Function list = impl::list_lists;

} // namespace stdproc
} // namespace shaka


#endif // SHAKA_STDPROC_PAIRS_AND_LISTS_IMPL_H
