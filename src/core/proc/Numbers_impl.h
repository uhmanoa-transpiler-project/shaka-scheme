#ifndef SHAKA_STDPROC_NUMBERS_IMPL_H
#define SHAKA_STDPROC_NUMBERS_IMPL_H
#include "core/base/Core.h"
#include <vector>
namespace shaka{
namespace stdproc{
// (number? obj)
using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
using EnvPtr = std::shared_ptr<shaka::Environment>;
using Function = std::function<Args(Args, EnvPtr)>;
namespace impl{
Args isnumber(Args a, EnvPtr e){
static_cast<void>(e);
if(a[0] -> is_number()){
	shaka::Boolean b(true);
	return {std::make_shared<shaka::DataNode>(b)};
}	
else{
	shaka::Boolean c(false);
	return {std::make_shared<shaka::DataNode>(c)};
}

}
// (complex? obj)
// (real? obj)
// (rational? obj)
// (integer? obj)

// (exact? z)
// (inexact? z)

// (exact-integer? z)
// (finite? z)
// (infinite? z)
// (nan? z)

// (= z1 z2 z3 ...)
// (< z1 z2 z3 ...)
// (> z1 z2 z3 ...)
// (<= z1 z2 z3 ...)
// (>= z1 z2 z3 ...)

// (zero? z)
// (positive? x)
// (negative? x)
// (odd? n)
// (even? n)

// (max? x1 x2 ...)
// (min? x1 x2 ...)

// (number->string z)
// (number->string z radix)

// (string->number string)
// (string->number string radix)
}
Function is_number = impl::isnumber;

}
}
#endif // SHAKA_STDPROC_NUMBERS_IMPL_H
