#ifndef SHAKA_STDPROC_BOOLEANS_IMPL_H
#define SHAKA_STDPROC_BOOLEANS_IMPL_H

#include "core/base/Number.h"
#include "core/base/Boolean.h"
#include "core/base/DataNode.h"
#include "core/base/Data.h"

#include "core/base/Environment.h"
#include <functional>
#include <typeinfo>
#include <vector>

namespace shaka {
namespace stdproc {
using NodePtr = std::shared_ptr<shaka::DataNode>;
using Args = std::vector<NodePtr>;
using Function = std::function<Args(Args, EnvPtr)>;

namespace impl {

// (not obj)
Args nots(Args v, EnvPtr e) {
	static_cast<void>(e);
	if (v[0]->is_boolean()) {
		if (shaka::get<shaka::Boolean>(v[0]->get_data()) ==
				shaka::Boolean(true)) {
			NodePtr result_value = std::make_shared<shaka::DataNode>(shaka::Boolean(false));
			Args result_vector = {result_value};
			return result_vector;
		}
		else {
			Args result_vector = {v[0]};
			return result_vector;
		}
	}
	else {
		throw std::runtime_error("STDPROC: Incorrect argument type to Native Procedure: not");
		return v;
	}
}
// (boolean? obj)
Args isboolean(Args v, EnvPtr e) {
	static_cast<void>(e);
	NodePtr result_value = std::make_shared<shaka::DataNode>(shaka::Boolean(v[0]->is_boolean()));
	Args result_vector = {result_value};
	return result_vector;
}

} // namespace impl

Function notb = impl::nots;
Function booleanp = impl::isboolean;

} // namespace stdproc
} // namespace shaka
#endif // SHAKA_STDPROC_BOOLEANS_IMPL_H
