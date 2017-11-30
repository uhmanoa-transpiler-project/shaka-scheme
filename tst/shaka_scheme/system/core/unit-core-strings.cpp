#include <gmock/gmock.h>
#include <iostream>
#include "shaka_scheme/system/base/String.hpp"
#include "shaka_scheme/system/core/strings.hpp"
#include "shaka_scheme/system/core/types.hpp"
#include "shaka_scheme/system/core/lists.hpp"

TEST(StringsUnitTest, make_string) {
    using namespace shaka;

    NodePtr size1 = create_node(Data(String("3")));
    NodePtr str1 = make_string_blank(size1);
    ASSERT_TRUE(core::is_string(str1));

    NodePtr size2 = create_node(Data(String("5")));
    NodePtr c = create_node(Data(String("z")));
    NodePtr str2 = make_string(size2, c);
    ASSERT_TRUE(core::is_string(str2));

    String s1(str1->get<String>());
    String s2(str2->get<String>());

    ASSERT_EQ(s1.get_string(), "   ");
    ASSERT_EQ(s2.get_string(), "zzzzz");

}

TEST(StringsUnitTest, string_char_list) {
    using namespace shaka;

    std::deque<NodePtr> charList = {create_node(Data(String("a"))),
                                    create_node(Data(String("s"))),
                                    create_node(Data(String("d"))),
                                    create_node(Data(String("f")))};

    NodePtr str = char_string(charList);
    ASSERT_TRUE(core::is_string(str));

    String s(str->get<String>());
    ASSERT_EQ(s.get_string(), "asdf");
}

TEST(StringsUnitTest, string_length) {
    using namespace shaka;

    NodePtr str = create_node(Data(String("asdfghjkl;")));
    NodePtr l = string_length(str);
    ASSERT_EQ(l->get<String>().get_string(), "10");

}

TEST(StringsUnitTest, list_to_string) {
    using namespace shaka;

    NodePtr a = create_node(Data(String("a")));
    NodePtr b = create_node(Data(String("b")));
    NodePtr c = create_node(Data(String("c")));

    NodePtr lst = core::list(a, b, c);

    NodePtr test = list_to_string(lst);
    ASSERT_TRUE(core::is_string(test));

    std::cout << test->get<String>().get_string() << std::endl;
}
