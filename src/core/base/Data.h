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


using Data = boost::variant<
    std::shared_ptr<DataNode>,
    shaka::Symbol,
    shaka::Number,
    shaka::String,
    shaka::Boolean
>;

using ListPtr = std::shared_ptr<DataNode>;

}

#include "core/base/Number.h"
#include "core/base/Symbol.h"
#include "core/base/Boolean.h"
#include "core/base/String.h"

#endif // SHAKA_CORE_BASE_DATA_H

