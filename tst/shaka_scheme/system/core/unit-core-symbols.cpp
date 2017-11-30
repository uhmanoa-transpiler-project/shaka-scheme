#include <gmock/gmock.h>
#include "shaka_scheme/system/core/symbols.hpp"
#include "shaka_scheme/system/core/types.hpp"

TEST(SymbolsUnitTest, are_symbols_True) {
    using namespace shaka;

    NodePtr node = create_node(Data(Symbol("foo")));
    std::deque<NodePtr> syms = {node, node, node};
    ASSERT_TRUE(core::is_symbol(node));
    ASSERT_TRUE(eq_symbols(syms));

    NodePtr node2 = node;
    std::deque<NodePtr> eqSyms = {node, node2};
//    ASSERT_TRUE(eq_symbols(eqSyms));

}

TEST(SymbolsUnitTest, are_symbols_False) {
    using namespace shaka;

    //nullptr
    std::deque<NodePtr> blank = {create_node(Data())};
    ASSERT_FALSE(eq_symbols(blank));

    //Different Symbols and a nullptr
    std::deque<NodePtr> symsAndBlank = {create_node(Data(Symbol("foo"))),
                                        create_node(Data(Symbol("hi"))),
                                        create_node(Data())};
    ASSERT_FALSE(eq_symbols(symsAndBlank));

    //A Symbol and a String
    std::deque<NodePtr> symAndString = {create_node(Data(Symbol("foo"))),
                                        create_node(Data(String("foo")))};
    ASSERT_FALSE(eq_symbols(symAndString));

    //Different Symbols
    std::deque<NodePtr> diffSyms = {create_node(Data(Symbol("Every"))),
                                    create_node(Data(Symbol("Body"))),
                                    create_node(Data(Symbol("Was"))),
                                    create_node(Data(Symbol("Kung Fu Fighting")))};
    ASSERT_FALSE(eq_symbols(diffSyms));

    //Similar Symbols
    std::deque<NodePtr>  simSyms = {create_node(Data(Symbol("foo"))),
                                    create_node(Data(Symbol("foo"))),
                                    create_node(Data(Symbol("foo")))};
    ASSERT_FALSE(eq_symbols(simSyms));
}

TEST(SymbolsUnitTest, StringtoSymbol) {
    using namespace shaka;

    NodePtr str = create_node(Data(String("asdfghjkl;")));

    ASSERT_TRUE(core::is_string(str));
    ASSERT_FALSE(core::is_symbol(str));
    ASSERT_TRUE(core::is_symbol(string_to_symbol(str)));

    NodePtr sym = string_to_symbol(str);

    ASSERT_FALSE(core::is_string(sym));
    ASSERT_TRUE(core::is_symbol(sym));
}

TEST(SymbolsUnitTest, SymboltoString) {
    using namespace shaka;

    NodePtr symb = create_node(Data(Symbol("asdfghjkl;")));

    ASSERT_TRUE(core::is_symbol(symb));
    ASSERT_FALSE(core::is_string(symb));
    ASSERT_TRUE(core::is_string(symbol_to_string(symb)));

    NodePtr stri = symbol_to_string(symb);

    ASSERT_FALSE(core::is_symbol(stri));
    ASSERT_TRUE(core::is_string(stri));
}