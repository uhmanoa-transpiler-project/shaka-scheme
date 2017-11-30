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

TEST(StringsUnitTest, string_ref) {
    using namespace shaka;

    NodePtr str = create_node(Data(String("hola")));
    NodePtr k = create_node(Data(String("3")));
    NodePtr test = string_ref(str,k);

    ASSERT_TRUE(core::is_string(test));
    ASSERT_EQ("a", test->get<String>().get_string());
}

TEST(StringsUnitTest, string_set) {
    using namespace shaka;

    NodePtr str = create_node(Data(String("asdf")));
    NodePtr k = create_node(Data(String("2")));
    NodePtr ch = create_node(Data(String("o")));

    NodePtr test = string_set(str,k,ch);

    ASSERT_TRUE(core::is_string(test));
    ASSERT_EQ(str->get<String>().get_string(), "asdf");
    ASSERT_EQ(test->get<String>().get_string(), "asof");
}

TEST(StringsUnitTest, eq_strings_true) {
    using namespace shaka;

    NodePtr str1 = create_node(Data(String("hello")));
    NodePtr str2 = str1;
    NodePtr str3 = create_node(Data(String("hello")));

    std::deque<NodePtr> str_test = {str1, str1, str1};
    ASSERT_TRUE(eq_strings(str_test));

    std::deque<NodePtr> str_test2 = {str1, str2};
    ASSERT_TRUE(eq_strings(str_test2));

    std::deque<NodePtr> str_test3 = {str1, str2, str3};
    ASSERT_TRUE(eq_strings(str_test3));
}

TEST(StringsUnitTest, list_to_string) {
    using namespace shaka;

    NodePtr a = create_node(Data(String("a")));
    NodePtr b = create_node(Data(String("b")));
    NodePtr c = create_node(Data(String("c")));

    NodePtr lst = core::list(a, b, c);

    NodePtr test = list_to_string(lst);
    ASSERT_TRUE(core::is_string(test));
    ASSERT_EQ("abc", test->get<String>().get_string());

    NodePtr x = create_node(Data(Symbol("x")));
    NodePtr y = create_node(Data(Symbol("y")));
    NodePtr z = create_node(Data(Symbol("z")));

    NodePtr lst2 = core::list(x, y, z);

    NodePtr test2 = list_to_string(lst2);
    ASSERT_TRUE(core::is_string(test2));
    ASSERT_EQ("xyz", test2->get<String>().get_string());

    NodePtr lst3 = core::append(lst,lst2);

    NodePtr test3 = list_to_string(lst3);
    ASSERT_TRUE(core::is_string(test3));
    ASSERT_EQ("abcxyz", test3->get<String>().get_string());

}


