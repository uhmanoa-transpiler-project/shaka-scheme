#include "shaka_scheme/system/lexer/lexer_definitions.hpp"

namespace shaka {
namespace lexer {

bool operator==(LexInfo left, LexInfo right) {
  return (
      left.filename == right.filename
          && left.pos == right.pos
          && left.row == right.row
          && left.col == right.col
  );
}

bool operator!=(LexInfo left, LexInfo right) {
  return !operator==(left, right);
}

std::ostream& operator<<(std::ostream& left, const LexInfo& right) {
  left << "LexInfo("
       << "name:\"" << right.filename << "\" | "
       << "pos:" << right.pos << " | "
       << "row:" << right.row << " | "
       << "col:" << right.col << ")";
  return left;
}

LexResult::LexResult(std::string type,
                     std::string str,
                     LexInfo info,
                     std::string token_type) :
    type(type),
    str(str),
    info(info),
    token_type(token_type) {}

bool LexResult::is_error() const { return type == "error"; }
bool LexResult::is_token() const { return type == "token"; }
bool LexResult::is_incomplete() const { return type == "incomplete"; }

bool operator==(const LexResult& left, const LexResult& right) {
  return (
      left.info == right.info &&
          left.token_type == right.token_type &&
          left.str == right.str &&
          left.type == right.type
  );
}

bool operator!=(const LexResult& left, const LexResult& right) {
  return !operator==(left, right);
}

LexResult Error(std::string str, LexInfo info, std::string token_type) {
  return LexResult("error", str, info, token_type);
}

LexResult Token(std::string str, LexInfo info, std::string token_type) {
  return LexResult("token", str, info, token_type);
}

LexResult Incomplete(std::string str, LexInfo info) {
  return LexResult("incomplete", str, info);
}

std::ostream& operator<<(std::ostream& left, LexResult right) {
  left << "LexResult("
       << "type:[" << right.type << "] | "
       << "str:\"" << right.str << "\" | "
       << "info:" << right.info << " | "
       << "token_type:<" << right.token_type << ">)";
  return left;
}

LexerException::LexerException(std::string str, LexInfo info) {
  std::stringstream ss;
  ss << info;
  str += ": ";
  str += ss.str();
  this->str = str;
}

const char * LexerException::what() const noexcept {
  return str.c_str();
}

LexerInput::LexerInput(std::string input, std::string name) :
    input(input) {
  curr = 0;
  info = {name, 1, 1, 1};
}

int LexerInput::index() {
  return curr;
}

char LexerInput::peek() {
  if (input[curr] == '\0' || input[curr] == EOF || curr >= input.length()) {
    throw LexerException("need more input", this->info);
  }
  return input[curr];
}

LexInfo LexerInput::get_info() {
  return info;
}

void LexerInput::set_info(LexInfo info) {
  this->info = info;
}

char LexerInput::get() {
  const char c = input[curr];
  // If at end of string, just send back end of string.
  if (curr >= input.length()) {
    throw LexerException("need more input", this->info);
  }
  // Change col and row if newline.
  if (c == '\n') {
    info.row++;
    info.col = 1;
  } else {
    info.col++;
  }
  // Always increment pos counter.
  info.pos++;
  // Move iterator forward.
  ++curr;
  //std::cout << "get: pos: " << curr + 1 << std::endl;
  //std::cout << "get-distance: " << this->index() << " | " <<
  //          static_cast<char>
  //          (c) << std::endl;
  return c;
}

LexInfo LexerInput::info_then_get() {
  auto info = this->info;
  this->get();
  return info;
}

void LexerInput::unget(std::vector<LexResult> tokens) {
  //std::cout << "unget: before-tokens: " << std::endl;
  //for (auto it : tokens) {
  //  std::cout << it << std::endl;
  //}
  //std::cout << "unget: before: " << input << "|" << this->info <<
  //          std::endl;
  if (tokens.empty()) {
    return;
  }
  this->info = tokens[0].info;
  // Take the input.
  std::string temp;
  auto it_pos = this->index();
  //std::cout << "it_pos: " << it_pos << std::endl;
  for (auto i = curr; i < input.length(); ++i) {
    temp += input[i];
  }
  // Insert past input back into it.
  this->input = "";
  for (auto token : tokens) {
    //std::cout << "inserting token back: " << token.str << std::endl;
    this->input += token.str;
    for (auto i = 0; i < token.str.length(); ++i) {
      this->curr--;
    }
  }
  this->input += temp;
  this->curr = 0;
  //std::cout << "unget: after: " << input << "|" << this->info << std::endl;
}

void LexerInput::append_input(std::string more_input) {
  std::string temp;
  for (auto i = 0; i < input.length(); ++i) {
    temp += input[i];
  }
  temp += more_input;
  this->input = temp;
  curr = 0;
}

LexerRule sequence(LexerRule left,
                   LexerRule right,
                   std::string type) {
  return [=](LexerInput& lex) -> LexResult {
    // Save the string and info before hand.
    LexInfo saved_info = lex.get_info();
    std::string buf;

    auto lresult = left(lex);
    if (!lresult.is_token()) {
      return lresult;
    }
    //std::cout << "sequence: left: " << lresult << std::endl;
    auto rresult = right(lex);
    if (!rresult.is_token()) {
      lex.unget({lresult});
      return rresult;
    }
    //std::cout << "sequence: right: " << rresult << std::endl;

    buf += lresult.str;

    buf += rresult.str;

    std::string token_type = type;
    if (token_type.empty()) {
      token_type = lresult.token_type;
      token_type += "+";
      token_type += rresult.token_type;
    }
    return Token(buf, saved_info, token_type);
  };
}

LexerRule make_terminal(std::string str, std::string type) {
  return [=](LexerInput& lex) -> LexResult {
    // Save the string and info before hand.
    LexInfo saved_info = lex.get_info();
    std::string buf;

    try {
      // If we matched to the entire string.
      bool valid = true;
      // For each character in the terminal string,
      // try to match the next input to it.
      for (auto it : str) {
        if (lex.peek() != it) {
          valid = false;
          break;
        }
        buf += lex.peek();
        lex.get();
      }
      // If we got through the entire array without error, return the token.
      if (valid) {
        return Token(buf, saved_info, type);
      } else {
        // If an error, unget the token.
        auto token = Token(buf, saved_info, type);
        lex.unget({token});
        return Error(buf, lex.get_info(), std::string(type) + ": "
            "could not match to \"" + str + "\"");
      }
    } catch (LexerException e) {
      auto result = Incomplete(buf, saved_info);
      lex.unget({result});
      return Incomplete(e.what(), lex.get_info());
    }
  };
}

LexerRule make_class(std::function<bool(char)> pred, std::string type) {
  return [=](LexerInput& lex) -> LexResult {
    // Save the string and info before hand.
    LexInfo saved_info = lex.get_info();
    std::string buf;

    try {
      // If we matched to the entire string.
      bool valid = true;
      // For each character in the terminal string,
      // try to match the next input to it.
      if (!pred(lex.peek())) {
        valid = false;
      }
      buf += lex.peek();
      lex.get();
      // If we got through the entire array without error, return the token.
      if (valid) {
        return Token(buf, saved_info, type);
      } else {
        // If an error, unget the token.
        auto token = Token(buf, saved_info, type);
        lex.unget({token});
        return Error(buf, lex.get_info(), std::string(type) + ": "
            "character did not pass predicate");
      }
    } catch (LexerException e) {
      auto result = Incomplete(buf, saved_info);
      lex.unget({result});
      return Incomplete(e.what(), lex.get_info());
    }
  };
}

LexerRule operator+(LexerRule left, LexerRule right) {
  return sequence(left, right);
}

LexerRule alternative(LexerRule left,
                      LexerRule right,
                      std::string token_type) {
  return [=](LexerInput& lex) -> LexResult {
    // Save the string and info before hand.
    LexInfo saved_info = lex.get_info();
    std::string buf;

    auto lresult = left(lex);
    if (lresult.is_token()) {
      return lresult;
    }
    auto rresult = right(lex);
    if (rresult.is_token() || rresult.is_incomplete()) {
      return rresult;
    }
    return Error(rresult.str, saved_info, lresult.token_type +
        "|" + rresult.token_type);
  };
}

LexerRule operator|(LexerRule left, LexerRule right) {
  return alternative(left, right);
}

LexerRule kleene(LexerRule rule) {
  return [=](LexerInput& lex) -> LexResult {
    // Save the string and info before hand.
    LexInfo saved_info = lex.get_info();
    std::string buf;

    auto result = rule(lex);
    std::string token_type = result.token_type;
    if (!result.is_token()) {
      return Token("", saved_info, "empty");
    }
    //std::cout << result << std::endl;
    while (result.is_token()) {
      buf += result.str;
      result = rule(lex);
      //std::cout << result << std::endl;
    }
    return Token(buf, saved_info, "*" + token_type);
  };
}

LexerRule operator*(LexerRule rule) {
  return kleene(rule);
}

LexerRule with_label(LexerRule rule, std::string label) {
  return [=](LexerInput& lex) -> LexResult {
    // Save the string and info before hand.
    auto result = rule(lex);
    if (result.is_token()) {
      result.token_type = label;
    }
    return result;
  };
}

LexerRule operator/(LexerRule rule, std::string right) {
  return with_label(rule, right);
}

LexResult empty_string(LexerInput& lex) {
  return Token("", lex.info, "empty");
}

LexerRule repeat(LexerRule rule, std::size_t times) {
  auto repeated_rule = rule;
  for (auto i = 1; i < times; ++i) {
    repeated_rule = repeated_rule + rule;
  }
  return repeated_rule;
}

LexerRule operator*(LexerRule rule, std::size_t right) {
  return repeat(rule, right);
}

LexerRule operator*(std::size_t left, LexerRule rule) {
  return repeat(rule, left);
}

LexerRule suffix_action(LexerRule rule,
                        std::function<LexResult(LexResult)> func) {
  return [=](LexerInput& lex) {
    auto result = rule(lex);
    return func(result);
  };
}

LexerRule operator&(LexerRule left, std::function<LexResult(LexResult)> func) {
  return suffix_action(left, func);
}

LexerRule prefix_action(LexerRule rule,
                        std::function<void(LexerInput&)> func) {
  return [=](LexerInput& lex) {
    func(lex);
    auto result = rule(lex);
    return result;
  };
}

LexerRule operator&(std::function<void(LexerInput&)> func, LexerRule rule) {
  return prefix_action(rule, func);
}

LexerRule reject_if(LexerRule rule) {
  return [=](LexerInput& lex) {
    auto result = rule(lex);
    if (result.is_token()) {
      lex.unget({result});
      return Error(result.str, result.info, "Error: rejection rule \"" + result
          .token_type + "\" triggered");
    } else if (result.is_error()) {
      return Token(result.str, result.info, result.token_type);
    } else {
      return result;
    }
  };
}

LexerRule operator!(LexerRule rule) {
  return reject_if(rule);
}

} // namespace lexer
} // namespace shaka
