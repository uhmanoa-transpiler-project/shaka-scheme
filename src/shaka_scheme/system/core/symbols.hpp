#ifndef SHAKA_SCHEME_SYMBOLS_HPP
#define SHAKA_SCHEME_SYMBOLS_HPP

#include "shaka_scheme/system/base/Symbol.hpp"
#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/base/String.hpp"
#include <functional>
#include <vector>
#include <string>

namespace shaka {

using BoolCall = std::function<bool(std::deque<NodePtr>)>;
using NodeCall = std::function<NodePtr(NodePtr)>;

namespace core {

/**
 * @brief Implements (symbol=?).
 * @param nodes The data to take in
 * @return A boolean of whether the predicate was satisfied.
 */
inline bool are_symbols(std::deque<NodePtr> nodes){
    for(std::size_t i = 0; i < nodes.size(); i++) {
        if (nodes[i]->get_type() != Data::Type::SYMBOL) {
            return false;
        }

        if(i+1 != nodes.size()) {
            if (nodes[i] != nodes[i + 1])
                return false;
        }
    }
    return true;
}

/**
 * @brief Implements (string->symbol)
 * @param node The data to take in
 * @return A NodePtr containing the symbol
 */
inline NodePtr string_to_symbol(NodePtr node){
    if (node->get_type() != Data::Type::STRING) {
        throw TypeException(10001, "Incompatible argument type to NativeClosure");
    }

    String str(node->get<String>());

    NodePtr results = create_node(Data(Symbol(str.get_string())));
    return results;
}

/**
 * @brief Implements (symbol->string)
 * @param node The data to take in
 * @return A NodePtr containing the string
 */
inline NodePtr symbol_to_string(NodePtr node) {
    if (node->get_type() != Data::Type::SYMBOL) {
        throw TypeException(10001, "Incompatible argument type to NativeClosure");
    }

    Symbol sym(node->get<Symbol>());

    NodePtr results = create_node(Data(String(sym.get_value())));
    return results;
}

} //core

BoolCall eq_symbols = core::are_symbols;
NodeCall string_to_symbol = core::string_to_symbol;
NodeCall symbol_to_string = core::symbol_to_string;

} //shaka
#endif //SHAKA_SCHEME_SYMBOLS_HPP
