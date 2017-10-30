#ifndef SHAKA_SCHEME_LEXINFO_HPP
#define SHAKA_SCHEME_LEXINFO_HPP

#include <cstdint>
#include <string>

namespace shaka {

/**
 * @brief Keeps track of the current line, column, and position in a file, as
 * well as the module of origin's name.
 */
struct LexInfo {
  LexInfo(std::size_t line,
          std::size_t col,
          std::size_t pos,
          std::string module_name = "<generic input>") :
      line(line),
      col(col),
      pos(pos),
      module_name(module_name) {}

  LexInfo() :
      line(0),
      col(0),
      pos(0),
      module_name("") {}

  std::size_t line = 0;
  std::size_t col = 0;
  std::size_t pos = 0;
  std::string module_name = "";
};

bool operator==(const LexInfo& left, const LexInfo& right);
bool operator!=(const LexInfo& left, const LexInfo& right);

} // namespace shaka

#endif //SHAKA_SCHEME_LEXINFO_HPP
