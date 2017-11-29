#ifndef SHAKA_SCHEME_SYMBOLS_HPP
#define SHAKA_SCHEME_SYMBOLS_HPP

#include "shaka_scheme/system/base/Symbol.hpp"
#include "shaka_scheme/system/base/Data.hpp"
#include <functional>

namespace shaka {

using Callable = std::function<std::deque<NodePtr>(std::deque<NodePtr>)>;

namespace core {

/**
 * @brief Implements (symbol=?).
 * @param args The data to take in
 * @return A boolean of whether the predicate was satisfied.
 */
inline bool are_symbols(std::deque<NodePtr> args){
    for(std::size_t i = 0; i < args.size(); i++) {
        if (args[i]->get_type() != Data::Type::SYMBOL)
            return false;

        if(args[i+1] != nullptr)
            if(args[i] !=  args[i+1])
                return false;
    }
    return true;
}

std::deque<NodePtr> strToSym (std::deque<NodePtr> args){

}

} //core
} //shaka
#endif //SHAKA_SCHEME_SYMBOLS_HPP
