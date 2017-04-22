#ifndef SHAKA_CORE_BASE_ENVIRONMENT_IMPL_H
#define SHAKA_CORE_BASE_ENVIRONMENT_IMPL_H

#include "core/base/Environment.h"
#include "core/base/DataNode.h"

namespace shaka {

void Environment::print_bindings (std::ostream& out) {
    out << "{";
    for (const auto& it : local) {
        // If the Symbol is bound to a NodePtr,
        // then dereference it and print out its value.
        if (typeid(it.second) == typeid(NodePtr)) {
            out << " {" << it.first << " : " << *(it.second) << "}";
        }
        else {
            out << " {" << it.first << " : " << (it.second) << "}";
        }
    }
    out << " } \n";
}

} // namespace shaka

#endif // SHAKA_CORE_BASE_ENVIRONMENT_IMPL_H
