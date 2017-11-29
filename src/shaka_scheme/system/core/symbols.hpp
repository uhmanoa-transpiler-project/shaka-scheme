#ifndef SHAKA_SCHEME_SYMBOLS_HPP
#define SHAKA_SCHEME_SYMBOLS_HPP

#include "shaka_scheme/system/base/Symbol.hpp"
#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/base/String.hpp"
#include <functional>
#include <vector>
#include <string>

namespace shaka {

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

/**
 * @brief Implements (string->symbol)
 * @param arg The data to take in
 * @return A NodePtr containing the symbol
 */
inline NodePtr string_to_symbol(NodePtr arg){
    if (arg->get_type() != Data::Type::STRING) {
        throw TypeException(10001, "Incompatible argument type to NativeClosure");
    }

    String str(arg->get<String>());

    NodePtr results = create_node(Data(Symbol(str.get_string())));
    return results;
}

/**
 * @brief Implements (symbol->string)
 * @param arg The data to take in
 * @return A NodePtr containing the string
 */
inline NodePtr symbol_to_string(NodePtr arg) {
    if (arg->get_type() != Data::Type::SYMBOL) {
        throw TypeException(10001, "Incompatible argument type to NativeClosure");
    }

    Symbol sym(arg->get<Symbol>());

    NodePtr results = create_node(Data(String(sym.get_value())));
    return results;
}

} //core

} //shaka
#endif //SHAKA_SCHEME_SYMBOLS_HPP
