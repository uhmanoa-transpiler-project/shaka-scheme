#ifndef SHAKA_CORE_MACRO_PATTERN_H
#define SHAKA_CORE_MACRO_PATTERN_H

#include "core/base/DataNode.h"

namespace shaka {
namespace macro {

class Pattern {
public:
    Pattern (DataNode list) {
        if (!list.is_list()) {
            throw std::runtime_error("Pattern(): expected a list as a pattern as constructor argument");
        }
        if (!list.car()->is_symbol()) {
            throw std::runtime_error("Pattern(): first argument of the pattern list must be an identifier");
        }
        pattern_list = list;
    }

    /// @brief Matches whether two DataNote are equivalent
    //         <string>, <character>, <boolean>, <number>
    static bool match_datum (DataNode datum, DataNode expr) {
        if (datum.is_list() || expr.is_list()) {
            throw std::runtime_error("Pattern.match_datum: both arguments must be non-lists");
            return false;
        }
        // See if they match.
        else {
            return datum == expr;
        }
    }

    DataNode pattern_list;
};

}
}

#endif // SHAKA_CORE_MACRO_PATTERN_H 
