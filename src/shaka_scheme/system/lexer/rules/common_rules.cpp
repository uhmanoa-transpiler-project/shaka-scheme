#include "shaka_scheme/system/lexer/rules/rule_boolean.hpp"

namespace shaka {
namespace lexer {
namespace rules {

LexerRule letter = make_class([](char c) { return std::isalpha(c); },
                              "letter");
LexerRule digit = make_class([](char c) { return std::isdigit(c); },
                             "digit");
LexerRule hex_digit = (make_class([](char c) {
  return c >= 'a' && c <= 'f';
}, "") | digit) / "hex-digit";

LexerRule hex_scalar_value = hex_digit + *hex_digit;

std::function<LexResult(LexResult)> ignore_string = [](LexResult result) {
  if (result.is_token()) {
    result.str = "";
  }
  return result;
};

std::function<LexResult(LexResult)> print_string = [](LexResult result) {
  if (result.is_token()) {
    std::cout << result.str << std::endl;
  }
  return result;
};

std::function<LexResult(LexResult)> print_result = [](LexResult result) {
  std::cout << result << std::endl;
  return result;
};

void print_lexstate(LexerInput& input) {
  std::cout << "lexstate: \"" << input.input << "\" : " << input.info <<
            std::endl;
};

std::function<LexResult(LexResult)> print_message(std::string message) {
  return [=](LexResult result) {
    if (result.is_token()) {
      std::cout << message << std::endl;
    }
    return result;
  };
}

std::function<void(LexerInput&)> prefix_message(std::string message) {
  return [=](LexerInput& input) {
    std::cout << message << std::endl;
  };
}

std::function<LexResult(LexResult)> replace_with(const std::string s) {
  return [=](LexResult result) {
    if (result.is_token()) {
      result.str = s;
    }
    return result;
  };
}

LexResult replace_hex_escape(LexResult result) {
  if (result.is_token()) {
    std::string hex_escape = result.str.substr(2, result.str.length() - 2);
    int hex_value = std::stoi(hex_escape, nullptr, 16);
    char new_value = static_cast<char>(hex_value % 256);
    std::string str;
    str += new_value;
    result.str = str;
  }
  return result;
}

LexResult replace_hex_scalar_value(LexResult result) {
  if (result.is_token()) {
    int hex_value = std::stoi(result.str, nullptr, 16);
    char new_value = static_cast<char>(hex_value % 256);
    std::string str;
    str += new_value;
    result.str = str;
  }
  return result;
}

LexResult replace_mnemonic_escape(LexResult result) {
  if (result.is_token()) {
    if (result.str == "\\a") {
      result.str = "\a";
    } else if (result.str == "\\b") {
      result.str = "\b";
    } else if (result.str == "\\t") {
      result.str = "\t";
    } else if (result.str == "\\n") {
      result.str = "\n";
    } else if (result.str == "\\r") {
      result.str = "\\r";
    }
  }
  return result;
};

LexerRule inline_hex_escape = ((make_terminal("\\") + (make_terminal("x") +
    hex_scalar_value +
    make_terminal(";")) & replace_hex_escape)) /
    "inline-hex-escape";

LexerRule mnemonic_escape = ((make_terminal("\\") + make_class([](char c) {
  return c == 'a' |
      c == 'b' |
      c == 't' |
      c == 'n' |
      c == 'r';
}, "mnemonic-escape-chars")) & replace_mnemonic_escape) / "mnemonic-escape";

LexerRule intraline_whitespace = make_terminal(" ", "space") | make_terminal
    ("\t", "tab");

LexerRule carriage_return = make_terminal("\r", "return");
LexerRule not_newline = make_class([](char c) { return c != '\n'; },
                                   "not-newline");
LexerRule semicolon = make_terminal(";", "semicolon");
LexerRule newline = make_terminal("\n", "newline");

LexerRule line_ending = newline | (carriage_return + newline) | carriage_return;

} // namespace rules
} // namespace lexer
} // namespace shaka
