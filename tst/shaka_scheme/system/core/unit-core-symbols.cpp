#include <gmock/gmock.h>
#include <shaka_scheme/system/core/symbols.hpp>

TEST(SymbolsUnitTest, are_symbols_True) {
    using namespace shaka;

    NodePtr node = create_node(Data(Symbol("foo")));
    std::deque<NodePtr> syms = {node, node, node};
    ASSERT_TRUE(core::are_symbols(syms));

    NodePtr node2 = node;
    std::deque<NodePtr> eqSyms = {node, node2};
    ASSERT_TRUE(core::are_symbols(eqSyms));

}

TEST(SymbolsUnitTest, are_symbols_False) {
    using namespace shaka;

    //nullptr
    std::deque<NodePtr> blank = {create_node(Data())};
    ASSERT_FALSE(core::are_symbols(blank));

    //Different Symbols and a nullptr
    std::deque<NodePtr> symsAndBlank = {create_node(Data(Symbol("foo"))),
                                        create_node(Data(Symbol("hi"))),
                                        create_node(Data())};
    ASSERT_FALSE(core::are_symbols(symsAndBlank));

    //A Symbol and a String
    std::deque<NodePtr> symAndString = {create_node(Data(Symbol("foo"))),
                                        create_node(Data(String("foo")))};
    ASSERT_FALSE(core::are_symbols(symAndString));

    //Different Symbols
    std::deque<NodePtr> diffSyms = {create_node(Data(Symbol("Every"))),
                                    create_node(Data(Symbol("Body"))),
                                    create_node(Data(Symbol("Was"))),
                                    create_node(Data(Symbol("Kung Fu Fighting")))};
    ASSERT_FALSE(core::are_symbols(diffSyms));

    //Similar Symbols
    std::deque<NodePtr>  simSyms = {create_node(Data(Symbol("foo"))),
                                    create_node(Data(Symbol("foo"))),
                                    create_node(Data(Symbol("foo")))};
    ASSERT_FALSE(core::are_symbols(simSyms));
}