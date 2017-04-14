#ifndef SHAKA_CORE_BASE_DATA_H
#define SHAKA_CORE_BASE_DATA_H

#include <boost/variant.hpp>

namespace shaka {

using boost::get;

class DataNode;
class Symbol;
class Number;
class String;
class Boolean;
class Environment;


using Data = boost::variant<
    std::shared_ptr<DataNode>,
    std::shared_ptr<shaka::Environment>,
    shaka::Symbol,
    shaka::Number,
    shaka::String,
    shaka::Boolean
>;

using ListPtr = std::shared_ptr<DataNode>;
using NodePtr = std::shared_ptr<DataNode>;
using EnvPtr  = std::shared_ptr<Environment>;

}

#include "core/base/Number.h"
#include "core/base/Symbol.h"
#include "core/base/Boolean.h"
#include "core/base/String.h"
#include "core/base/Environment.h"


#endif // SHAKA_CORE_BASE_DATA_H

