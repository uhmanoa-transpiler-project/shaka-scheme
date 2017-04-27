#ifndef SHAKA_STDPROC_STRING_IMPL_H
#define SHAKA_STDPROC_STRING_IMPL_H
#include "core/base/Core.h"
#include <vector>
namespace shaka{
namespace stdproc{
// (number? obj)
using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
using EnvPtr = std::shared_ptr<shaka::Environment>;
using Function = std::function<Args(Args, EnvPtr)>;
namespace impl{
Args isstring(Args a, EnvPtr e){
static_cast<void>(e);
if(a[0] -> is_string()){
	shaka::Boolean b(true);
	return {std::make_shared<shaka::DataNode>(b)};
}	
else{
	shaka::Boolean c(false);
	return {std::make_shared<shaka::DataNode>(c)};
}

}
}
Function is_string = impl::isstring;

}
}
#endif // SHAKA_STDPROC_NUMBERS_IMPL_H
