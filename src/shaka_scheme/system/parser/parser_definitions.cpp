#include "shaka_scheme/system/parser/parser_definitions.hpp"

namespace shaka {
namespace parser {

ParserInput::ParserInput(std::string str, std::string origin) :
    lex(str, origin) {}

void ParserInput::append_input(std::string str) {
  if (tokens.size() > 0 && tokens.back().is_incomplete()) {
    tokens.pop_back();
  }
  lex.append_input(str);
}

lexer::LexResult ParserInput::get() {
  if (tokens.empty()) {
    return lexer::rules::scheme_lexer(lex);
  } else {
    auto token = tokens.front();
    tokens.pop_front();
    return token;
  }
}

lexer::LexResult ParserInput::peek() {
  if (tokens.empty()) {
    auto token = lexer::rules::scheme_lexer(lex);
    if (!token.is_token()) {
      return token;
    }
    tokens.push_back(token);
    return tokens.front();
  } else {
    return tokens.front();
  }
}

void ParserInput::unget(lexer::LexResult token) {
  tokens.push_front(token);
}

ParserResult::ParserResult(std::string type, NodePtr it) :
    type(type), it(it), lex_result(lexer::Error("", lexer::LexInfo(),
                                                "ParserResult-good")) {}

ParserResult::ParserResult(std::string type,
                           NodePtr it,
                           lexer::LexResult result) :
    type(type), it(it), lex_result(result) {}

bool ParserResult::is_valid() const { return type == "valid"; }
bool ParserResult::is_lexer_error() const { return type == "lexer-error"; }
bool ParserResult::is_parser_error() const { return type == "parser-error"; }
bool ParserResult::is_incomplete() const { return type == "incomplete"; }
bool ParserResult::is_complete() const { return type == "complete"; }

std::ostream& operator<<(std::ostream& left, ParserResult right) {
  left << "ParserResult("
       << "type:" << right.type << " | "
       << "it:";
  if (right.it) {
    left << *right.it << " | ";
  } else {
    left << "<nullptr>" << " | ";
  }
  left << "lex_result:" << right.lex_result << ")";
  return left;
}

ParserResult Valid(lexer::LexResult result) {
  return ParserResult("valid", nullptr, result);
}

ParserResult Complete(NodePtr node) {
  return ParserResult("complete", node);
}

ParserResult LexerError(lexer::LexResult result) {
  return ParserResult("lexer-error", nullptr, result);
}

ParserResult ParserError(lexer::LexResult result, std::string str) {
  return ParserResult("parser-error", create_node(String(str)), result);
}

ParserResult Incomplete(lexer::LexResult result) {
  return ParserResult("incomplete", nullptr, result);
}

using ParserRule = std::function<ParserResult(ParserInput&)>;
using DataConstructor = std::function<NodePtr(ParserResult)>;

/**
 * @brief Parses in fundamental primitive types, or simple datums.
 * @param in The input parser input to be used in this subfunction
 * @return The result of the parse, whether complete or erroneous
 */
ParserResult parse_simple(ParserInput& in) {
  auto next = in.peek();
  // Stop if we have no more input or there was a LexerError
  if (next.is_incomplete()) {
    return Incomplete(next);
  } else if (next.is_error()) {
    return LexerError(next);
  }
  // Get the singleton, "simple" tokens and convert them into strings,
  // or return a ParserError
  if (next.token_type == "string") {
    in.get();
    return Complete(create_node(String(next.str)));
  } else if (next.token_type == "identifier") {
    in.get();
    return Complete(create_node(Symbol(next.str)));
  } else if (next.token_type == "boolean-true") {
    in.get();
    return Complete(create_node(Boolean(true)));
  } else if (next.token_type == "boolean-false") {
    in.get();
    return Complete(create_node(Boolean(false)));
  } else if (next.token_type == "integer") {
    in.get();
    return Complete(create_node(Number(Integer(std::stoi(next.str)))));
  } else if (next.token_type == "rational") {
    in.get();
    // When converting the string form of a rational, we need to find the
    // position of the "/" in the string, and then split into the numerator
    // and denominator there.
    const auto slash_it = next.str.find("/");
    return Complete(
        create_node(
            Number(
                Rational(
                    std::stoi(next.str.substr(0, slash_it)),
                    std::stoi(next.str.substr(slash_it+1, next.str.length()))
                ))));
  } else if (next.token_type == "real") {
    in.get();
    return Complete(create_node(Number(Real(std::stod(next.str)))));
  } else {
    return ParserError(in.peek(), "could not match to simple datum");
  }
}

ParserResult parse_list(ParserInput& in) {
  // Create our accumulator list that we will append the parsed elements onto
  auto data_list = core::list();

  // We will want to possibly save our tokens in the future
  /// @todo Make sure that tokens is used to correctly place the consumed
  /// tokens back onto the input if the input list is incomplete
  std::vector<lexer::LexResult> tokens;

  // Read the (
  if (in.peek().token_type == "paren-left") {
    tokens.emplace_back(in.get());
  }

  // Keep reading elements (datums) while we have not reached the )
  while (in.peek().token_type != "paren-right") {
    if (in.peek().is_incomplete()) {
      auto incomp = in.peek();
      auto reversed_list = core::reverse(data_list);
    }
    // Read in a datum
    ParserResult datum_result = parse_datum(in);
    // If it was complete, add it onto our list
    if (datum_result.is_complete()) {
      data_list = core::append(data_list, core::list(datum_result.it));
    } else if (in.peek().token_type == "dot") {
      // However, if we have an improper list, we must end shortly after this.
      in.get();
      // Read in the last datum in the improper list
      datum_result = parse_datum(in);
      // If the last datum is correct, we must append it as the last item
      // onto the end of the list
      if (datum_result.is_complete()) {
        data_list = core::append(data_list, datum_result.it);
      } else {
        return ParserError(datum_result.lex_result, "could not match to "
            "last datum for improper list");
      }
    } else {
      // Otherwise, we have an incomplete parse, and let's return the
      // Incomplete status which is in the datum result.
      return datum_result;
    }
  }
  // We must match to the last paren
  if (in.peek().token_type == "paren-right") {
    in.get();
    return Complete(data_list);
  } else {
    // Otherwise, we have a parse error.
    return ParserError(in.peek(),
                       "could not match to closing parens for list");
  }
}

ParserResult parse_vector(ParserInput& in) {
  auto data_list = core::list();
  std::vector<lexer::LexResult> tokens;
  if (in.peek().token_type == "vector-left") {
    tokens.emplace_back(in.get());
  }

  while (in.peek().token_type != "paren-right") {
    if (in.peek().is_incomplete()) {
      auto incomp = in.peek();
      auto reversed_list = core::reverse(data_list);
    }
    ParserResult datum_result = parse_datum(in);
    if (datum_result.is_complete()) {
      data_list = core::append(data_list, core::list(datum_result.it));
    } else {
      return datum_result;
    }
  }
  if (in.peek().token_type == "paren-right") {
    in.get();
    // This is the same as parse_list, but we are instead just converting it
    // into a vector
    shaka::NodePtr converted_vector = core::list_to_vector(data_list);
    return Complete(converted_vector);
  } else {
    return ParserError(in.peek(),
                       "could not match to closing parens for vector");
  }
}

ParserResult parse_bytevector(ParserInput& in) {
  // Let us use a vector to hold the elements to have better memory access
  // patterns
  std::vector<unsigned char> elements;
  std::vector<lexer::LexResult> tokens;
  if (in.peek().token_type == "bytevector-left") {
    tokens.emplace_back(in.get());
  }

  while (in.peek().token_type != "paren-right") {
    if (in.peek().is_incomplete()) {
      auto incomp = in.peek();
    }
    ParserResult datum_result = parse_datum(in);
    if (datum_result.is_complete()) {
      auto current_element = *datum_result.it;
      if (current_element.get_type() != shaka::Data::Type::NUMBER) {
        return ParserError(in.peek(),
                           "bytevectors cannot contain non-numbers");
      }
      const auto current_number = current_element.get<shaka::Number>();
      if (current_number.get_type() !=
          shaka::Number::NumberType::INTEGER) {
        return ParserError(in.peek(),
                           "bytevectors cannot contain numbers that are not "
                               "integers");
      }
      const auto current_value = current_number.get<shaka::Integer>();
      if (current_value.get_value() < 0 || current_value.get_value() > 255) {
        return ParserError(in.peek(),
                           "bytevectors can only contain unsigned integers "
                               "within the range 0-255"
        );
      }
      elements.push_back(static_cast<unsigned char>(current_value.get_value()));
    } else {
      return datum_result;
    }
  }
  if (in.peek().token_type == "paren-right") {
    in.get();
    shaka::Bytevector bv(elements.size());
    for (std::size_t i = 0; i < elements.size(); ++i) {
      bv[i] = std::move(elements[i]);
    }
    return Complete(create_node(shaka::Data(std::move(bv))));
  } else {
    return ParserError(in.peek(),
                       "could not match to closing parens for bytevector");
  }
}

ParserResult parse_datum(ParserInput& in) {
  while (in.peek().token_type == "comment") {
    in.get();
  }

  if (in.peek().token_type == "datum-comment") {
    in.get();
    auto parsed_datum = parse_datum(in);
    if (!parsed_datum.is_complete()) {
      return parsed_datum;
    }
  }

  if (in.peek().token_type == "quote") {
    auto saved_token = in.get();
    auto parsed_datum = parse_datum(in);
    if (!parsed_datum.is_complete()) {
      in.unget(saved_token);
      return parsed_datum;
    } else {
      return Complete(core::list(
          create_node(Symbol("quote")),
          parsed_datum.it));
    }
  }

  auto simple_datum = parse_simple(in);
  if (simple_datum.is_lexer_error()) {
    return simple_datum;
  }
  if (simple_datum.is_complete()) {
    return simple_datum;
  } else {
    auto next = in.peek();
    if (next.token_type == "paren-left") {
      return parse_list(in);
    } else if (next.token_type == "vector-left") {
      return parse_vector(in);
    } else if (next.token_type == "bytevector-left") {
      return parse_bytevector(in);
    } else {
      return ParserError(next, "could not parse datum");
    }
  }
}

} // namespace parser
} // namespace shaka
