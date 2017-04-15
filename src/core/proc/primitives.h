#ifndef SHAKA_CORE_PROC_PRIMITIVES_H
#define SHAKA_CORE_PROC_PRIMITIVES_H

#include "core/base/NativeProcedure.h"
#include "core/base/Evaluator.h"

#include "core/eval/Define_impl.h"

namespace shaka {
namespace proc  {

using Args = std::vector<NodePtr>;
using Function = std::function<Args(Args, EnvPtr)>;

NodePtr define (NodePtr l, EnvPtr e) {

}

Function 

} // namespace shaka 
} // namespace proc  
#endif // SHAKA_CORE_PROC_PRIMITIVES
