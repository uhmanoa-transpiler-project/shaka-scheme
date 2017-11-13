#ifndef SHAKA_SCHEME_SYNTAXRULESMACRO_HPP
#define SHAKA_SCHEME_SYNTAXRULESMACRO_HPP

#include <memory>

namespace shaka {
namespace macro {

/**
 * @brief The type of a syntax-rules macro.
 *
 * It stores its pattern-matching and substitution functionality.
 *
 * This type is meant to operator on Scheme lists with an additional
 * MacroChecker context -- unlike R6RS, syntax objects are not directly needed
 * to support R7RS.
 */
class SyntaxRulesMacro {
};

/**
 * @brief The alias for the macro pointer type.
 */
using MacroPtr = std::shared_ptr<SyntaxRulesMacro>;

} // namespace macro
} // namespace shaka

#endif //SHAKA_SCHEME_SYNTAXRULESMACRO_HPP
