#include "shaka_scheme/system/lexer/rules/common_rules.hpp"

namespace shaka {
namespace lexer {
namespace rules {

LexerRule letter;
LexerRule digit;
LexerRule hex_digit;
LexerRule hex_scalar_value;

std::function<LexResult(LexResult)> ignore_string;

std::function<LexResult(LexResult)> print_string;

std::function<LexResult(LexResult)> print_result;
LexerRule inline_hex_escape;

LexerRule mnemonic_escape;

LexerRule intraline_whitespace;

LexerRule carriage_return;
LexerRule not_newline;
LexerRule semicolon;
LexerRule newline;

LexerRule line_ending;


void print_lexstate(LexerInput& input) {
  std::cout << "lexstate: \"" << input.input << "\" : " << input.info <<
            std::endl;
};

std::function<LexResult(LexResult)> print_message(const std::string message) {
  return [=](LexResult result) {
    if (result.is_token()) {
      std::cout << message << std::endl;
    }
    return result;
  };
}

std::function<void(LexerInput&)> prefix_message(const std::string message) {
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

void init_common_rules() {
  letter = make_class([](char c) { return std::isalpha(c); },
                      "letter");
  digit = make_class([](char c) { return std::isdigit(c); },
                     "digit");
  hex_digit = (make_class([](char c) {
    return c >= 'a' && c <= 'f';
  }, "") | digit) / "hex-digit";

  hex_scalar_value = hex_digit + *hex_digit;
  inline_hex_escape = ((make_terminal("\\") + (make_terminal("x") +
      hex_scalar_value +
      make_terminal(";")) & replace_hex_escape)) /
      "inline-hex-escape";

  ignore_string = [](LexResult result) {
    if (result.is_token()) {
      result.str = "";
    }
    return result;
  };

  print_string = [](LexResult result) {
    if (result.is_token()) {
      std::cout << result.str << std::endl;
    }
    return result;
  };

  print_result = [](LexResult result) {
    std::cout << result << std::endl;
    return result;
  };

  mnemonic_escape = ((make_terminal("\\") + make_class([](char c) {
    return c == 'a' |
        c == 'b' |
        c == 't' |
        c == 'n' |
        c == 'r';
  }, "mnemonic-escape-chars")) & replace_mnemonic_escape) / "mnemonic-escape";
  intraline_whitespace = make_terminal(" ", "space") | make_terminal
      ("\t", "tab");

  carriage_return = make_terminal("\r", "return");
  not_newline = make_class([](char c) { return c != '\n'; },
                           "not-newline");
  semicolon = make_terminal(";", "semicolon");
  newline = make_terminal("\n", "newline");

  line_ending = newline | (carriage_return + newline) | carriage_return;

}

} // namespace rules
} // namespace lexer
} // namespace shaka
