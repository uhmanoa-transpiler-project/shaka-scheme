#include <gmock/gmock.h>
#include <iostream>
#include "shaka_scheme/system/base/String.hpp"
#include "shaka_scheme/system/core/strings.hpp"
#include "shaka_scheme/system/core/types.hpp"

TEST(StringsUnitTest, make_string) {
    using namespace shaka;

    NodePtr size1 = create_node(Data(String("3")));
    NodePtr str1 = core::make_string(size1);
    ASSERT_TRUE(core::is_string(str1));

    NodePtr size2 = create_node(Data(String("5")));
    NodePtr c = create_node(Data(String("z")));
    NodePtr str2 = core::make_string(size2, c);
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

    NodePtr str = core::string_char_list(charList);
    ASSERT_TRUE(core::is_string(str));

    String s(str->get<String>());
    ASSERT_EQ(s.get_string(), "asdf");
}

TEST(StringsUnitTest, string_length) {
    using namespace shaka;

    NodePtr str = create_node(Data(String("asdfghjkl;")));

    NodePtr l = core::string_length(str);
    std::cout << l->get<String>() << std::endl;


}