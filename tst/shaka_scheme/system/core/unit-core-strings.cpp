#include <gmock/gmock.h>
#include <iostream>
#include "shaka_scheme/system/base/String.hpp"
#include "shaka_scheme/system/core/strings.hpp"
#include "shaka_scheme/system/core/types.hpp"

TEST(StringsUnitTest, make_string) {
    using namespace shaka;

    NodePtr str1 = core::make_string(3);
    ASSERT_TRUE(core::is_string(str1));

    NodePtr str2 = core::make_string(5, 'z');
    ASSERT_TRUE(core::is_string(str2));

    String s1(str1->get<String>());
    String s2(str2->get<String>());

    ASSERT_EQ(s1.get_string(), "   ");
    ASSERT_EQ(s2.get_string(), "zzzzz");

}

TEST(StringsUnitTest, string_list) {
    using namespace shaka;

    std::deque<char> charList = {'a', 's', 'd', 'f'};
    NodePtr str = core::string_list(charList);
    ASSERT_TRUE(core::is_string(str));

    String s(str->get<String>());
    ASSERT_EQ(s.get_string(), "asdf");
}