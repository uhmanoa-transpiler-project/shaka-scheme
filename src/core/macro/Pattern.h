#ifndef SHAKA_CORE_MACRO_PATTERN_H
#define SHAKA_CORE_MACRO_PATTERN_H

#include "core/base/DataNode.h"
#include "core/base/Environment.h"

namespace shaka {
namespace macro {

class Pattern {
public:
    Pattern (const shaka::DataNode& list,
             Symbol                 ellipsis = Symbol("..."),
             EnvPtr                 e = nullptr) :
        parent_env(e),
        pattern_list(list),
        ellipsis(ellipsis),
        bindings(std::make_shared<Environment>(e)) {
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
        if (datum.get_data().type() != expr.get_data().type()) { return false; }
        else if (datum.is_list() || expr.is_list()) {
            throw std::runtime_error("Pattern.match_datum: both arguments must be non-lists");
            return false;
        }
        //else if (datum.is_symbol() || expr.is_symbol()) {
        //    throw std::runtime_error("Pattern.match_datum: both arguments must be non-symbols");
        //    return false;
        //}
        // See if they match.
        else if (datum.is_string() || datum.is_boolean() || datum.is_number()) {
            std::cout << "\tComparing datum and expr..." << std::endl;
            return datum.get_data() == expr.get_data();
        }
        else {
            throw std::runtime_error("Pattern.match_datum: cannot match using non-datum types");
            return false;
        }
    }

    static bool match_symbol (DataNode p, DataNode e) {
        if (!p.is_symbol()) {
            throw std::runtime_error("Pattern.match_symbol: pattern comonent must be a symbol");
            return false;
        }
        return !e.is_null();
    }

    bool match (DataNode expr_list) {
        this->bindings = std::make_shared<Environment>(parent_env);
        auto p = pattern_list;
        auto e = expr_list;

        std::cout << "pattern_list: " << p << std::endl;
        std::cout << "express_list: " << e << std::endl;
        
        // The macro call should be a list like a procedure call.
        // If their list-ness does not match, reject.
        if (p.is_list() != e.is_list()) {
            std::cout << "\tp and e are not the same listness" << std::endl;
            return false;
        }
        // If the pattern is not a list, it is invalid anyways. Reject.
        else if (!p.is_list()) {
            std::cout << "\tp and e are not lists" << std::endl;
            return false;
        }
        // If the pattern is a list but the expression is not, reject.
        else if (p.is_list() && !e.is_list()) {
            std::cout << "\tp is a list but e is not" << std::endl;
            return false;
        }
        // The pattern is a list and the expression is a list. Inspect.
        else {
            // For each element in the pattern, match it to a
            // corresponding expression in the list.
            while (!p.is_null()) {
                // Examine p and e
                std::cout << "\tp: " << *p.car() << "\t\t| e: " << *e.car() << std::endl;
                // If we have exhausted the expression already,
                // stop.
                if (e.is_null()) {
                    std::cout << "\tterminating Symbol..." << std::endl;
                    return false;
                }

                if (p.car()->is_symbol()) {
                    std::cout << "\tmatching Symbol..." << std::endl;
                    bindings->set_value(get<Symbol>(p.get_data()), std::make_shared<DataNode>(*e.car()));
                }
                else if (p.car()->is_list()) {
                    std::cout << "\tmatching list..." << std::endl;
                    if (!e.car()->is_list()) {
                        std::cout << "\te is not a list" << std::endl;
                        return false;
                    }
                    // p and e are both lists, so initialize a subpattern.
                    Pattern subpattern(DataNode(*p.car()), this->ellipsis, bindings);
                    // If the pattern doesn't match, stop.
                    if (!subpattern.match(*e.car())) {
                        std::cout << "\te doens't match the p subpattern" << std::endl;
                        return false;
                    }
                }
                else if (p.car()->is_number() ||
                         p.car()->is_boolean() ||
                         p.car()->is_string()) {
                    if (!Pattern::match_datum(*p.car(), *e.car())) {
                        std::cout << "\tp-datum does not match e-datum" << std::endl;
                        return false;
                    }
                }

               
                // Increment
                p = *p.cdr();
                e = *e.cdr();
            }
            if (!e.is_null()) {
                std::cout << "e is not exhausted after matching" << std::endl;
                return false;
            }
        }
        std::cout << "\t<<BINDINGS>>" << std::endl;
        for (auto it : this->bindings->get_bindings()) {
            if (it.second.type() != typeid(NodePtr)) {
                std::cout << "\t\t" << it.first << " : " << it.second << std::endl;
            }
            else {
                std::cout << "\t\t" << it.first << " : " << *get<NodePtr>(it.second) << std::endl;
            }
        }
        return true;
    }

    EnvPtr get_bindings() {
        return bindings;
    }

    DataNode pattern_list;
    Symbol ellipsis;
    EnvPtr bindings;
    EnvPtr parent_env;
};

}
}

#endif // SHAKA_CORE_MACRO_PATTERN_H 
