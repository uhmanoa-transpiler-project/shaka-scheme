//
// Created by aytas on 11/1/2017.
//

#ifndef SHAKA_SCHEME_PARSER_DEFINITIONS_HPP
#define SHAKA_SCHEME_PARSER_DEFINITIONS_HPP

#include "shaka_scheme/system/lexer/rules/rule_token.hpp"
#include "shaka_scheme/system/core/lists.hpp"

#include <deque>

namespace shaka {
namespace parser {

struct ParserInput {
  ParserInput(std::string str, std::string origin = "<generic>");

  void append_input(std::string str);

  lexer::LexResult get();

  lexer::LexResult peek();

  void unget(lexer::LexResult token);

  lexer::LexerInput lex;
  std::deque<lexer::LexResult> tokens;
};

struct ParserResult {
  ParserResult(std::string type, NodePtr it);

  ParserResult(std::string type, NodePtr it, lexer::LexResult result);

  std::string type;
  NodePtr it;
  lexer::LexResult lex_result;

  bool is_valid() const;
  bool is_lexer_error() const;
  bool is_parser_error() const;
  bool is_incomplete() const;
  bool is_complete() const;
};

std::ostream& operator<<(std::ostream& left, ParserResult right);

ParserResult Valid(lexer::LexResult result);

ParserResult Complete(NodePtr node);

ParserResult LexerError(lexer::LexResult result);

ParserResult ParserError(lexer::LexResult result, std::string str);

ParserResult Incomplete(lexer::LexResult result);

using ParserRule = std::function<ParserResult(ParserInput&)>;
using DataConstructor = std::function<NodePtr(ParserResult)>;

ParserResult parse_simple(ParserInput& in);

ParserResult parse_list(ParserInput& in);
ParserResult parse_datum(ParserInput& in);

} // namespace shaka
} // namespace parser

#endif //SHAKA_SCHEME_PARSER_DEFINITIONS_HPP
