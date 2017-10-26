#ifndef SHAKA_SCHEME_LEXERINPUT_HPP
#define SHAKA_SCHEME_LEXERINPUT_HPP

#include "shaka_scheme/system/lexer/LexInfo.hpp"
#include "shaka_scheme/system/lexer/Token.hpp"

namespace shaka {


struct LexerInput {
  /**
   * @brief Constrcuts the LexerInput with a stream reference and a LexInfo.
   * @param in The input stream to use for all input.
   * @param module_name The module name to assign to tokens produced from
   * this input stream.
   */
  LexerInput(std::istream& in, std::string module_name = "<generic input>");

  /**
   * @brief The input stream.
   */
  std::istream& in;

  /**
   * @brief The structure to hold line, column, position, and module name.
   */
  LexInfo lex_info;

  /**
   * @brief The saved length of the previous line, in characters.
   *
   * The length of any lines beyond the immediate last one will not be
   * preserved.
   *
   * 0 means an invalid quantity.
   */
  std::size_t last_col_max = 0;

  /**
   * @brief The string buffer to put back info when using unget().
   */
  std::string buffer;

  /**
   * @brief Consumes the next character in the current buffer, or, if the
   * string buffer is empty, the next character.
   * @return The next character from the input.
   */
  char get();

  /**
   * @brief Returns the character to the front of the input stream.
   * @param c The character to put back onto the input.
   *
   * @note If you try to put a newline back onto the stream, the LexerInput
   * will attempt to restore the last known length of the last line. If you
   * try to restore more than one consecutive newline without first get()'ing
   * another entire line, the lex_info.col will then be set to 0.
   */
  void unget(char c);

  /**
   * @brief Returns the next character of input.
   * @return The character from the buffer or input.
   */
  char peek();
};

} // namespace shaka

#endif //SHAKA_SCHEME_LEXERINPUT_HPP
