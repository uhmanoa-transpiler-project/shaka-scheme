#include "shaka_scheme/system/lexer/rules/rule_character.hpp"

namespace shaka {
namespace lexer {
namespace rules {

LexerRule character_name =
    (make_terminal("alarm") & replace_with("\a")
        | (make_terminal("backspace") & replace_with("\b"))
        | (make_terminal("delete") & replace_with("\x7f"))
        | (make_terminal("escape") & replace_with("\x1b"))
        | (make_terminal("newline") & replace_with("\n"))
        | (make_terminal("null") & replace_with("\0"))
        | (make_terminal("return") & replace_with("\r"))
        | (make_terminal("space") & replace_with(" "))
        | (make_terminal("tab") & replace_with("\t"))) / "character-name";

LexerRule character =
    ((make_terminal("#\\") & ignore_string) +
        (character_name
            | ((make_terminal("x") & ignore_string)
                + (hex_scalar_value & replace_hex_scalar_value))
            | (make_class([](char c) { return true; }, "any-character"))))
        / "character";

} // namespace rules
} // namespace lexer
} // namespace shaka

