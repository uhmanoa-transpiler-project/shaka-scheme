#ifndef SHAKA_SCHEME_MACROCONTEXT_HPP
#define SHAKA_SCHEME_MACROCONTEXT_HPP

#include "shaka_scheme/system/parser/parser_definitions.hpp"
#include "shaka_scheme/system/core/lists.hpp"
#include "shaka_scheme/system/core/types.hpp"

#include "shaka_scheme/system/exceptions/MacroExpansionException.hpp"
#include "shaka_scheme/system/vm/HeapVirtualMachine.hpp"
#include "shaka_scheme/system/parser/syntax_rules/SyntaxRulesMacro.hpp"

#include <map>
#include <stack>
#include <algorithm>
#include <set>

namespace shaka {
namespace macro {

/**
 * @brief The alias for the set of scopes that we use for lexical analysis.
 */
using ScopeSet = std::set<std::size_t>;

/**
 * @brief Used to print out the scopes for debugging purposes.
 * @param left The output stream to output to.
 * @param right The ScopeSet to print out
 * @return The updated reference to the output stream.
 */
std::ostream& operator<<(std::ostream& left, const ScopeSet& right);

/**
 * @brief The type of a macro that will be used in macro expansion.
 */
class SyntaxRulesMacro;

/**
 * @brief The type of data stored in the identifier bindings.
 */
struct IdentifierData {
  /**
   * @brief Initializes the struct with a set of scopes and an optional macro.
   * @param scopes The set of lexical scopes.
   * @param macro A shared pointer to an optional macro. If it is not
   * present, this identifier binding does not bind to a macro.
   */
  IdentifierData(ScopeSet scopes, MacroPtr macro = nullptr) :
      scopes(scopes),
      macro(std::move(macro)) {}

  ScopeSet scopes;
  MacroPtr macro;
};

/**
 * @brief The interface for managing lexical information at macro expansion
 * time.
 */
struct MacroContext {

  /**
   * @brief Intializes the MacroContext with the 0th scope and the 1st scope.
   * @param hvm The HeapVirtualMachien to query for the presence of primitive
   * forms.
   */
  MacroContext(HeapVirtualMachine& hvm);

  /**
   * @brief Changes the internal state of the context to have one additional
   * scope in its internal scope stack.
   */
  void push_scope();

  /**
   * @brief Pops the most recent scope from the current tracking set of scopes,
   * and restores the most recent one to the curr_scope variable.
   */
  void pop_scope();

  /**
   * @brief Maps an identifier to a non-macro binding.
   * @param symbol The symbol to bind with the current set of scopes.
   */
  void map_symbol(Symbol symbol);

  /**
   * @brief Maps an identifier to a macro.
   * @param symbol The symbol to bind to the macro.
   * @param macro The macro to be bound inside the macro expansion identifier
   * bindings map.
   */
  void map_macro(Symbol symbol, MacroPtr macro);

  /**
   * @brief Gets an iterator to a list of bindings that share the same
   * symbol, but not necesarily the same sets of scopes.
   * @param symbol The symbol to query for in the identifier bindings.
   * @return A constant iterator to a list of bindings.
   */
  std::multimap<shaka::Symbol, IdentifierData>::const_iterator
  get_bindings(Symbol symbol);

  /**
   * @brief A reference to the virtual machine to use when deciding the
   * presence of primitive forms.
   */
  HeapVirtualMachine& hvm;

  /**
   * @brief Stores the order that the context goes into scopes so it can
   * restore the most recent one.
   */
  std::vector<std::size_t> curr_scope_stack;

  /**
   * @brief The current set of scopes to use when binding identifiers in this
   * immediate scope.
   */
  ScopeSet curr_scopes;

  /**
   * @brief Stores the current scope index. Defaults to 0.
   */
  std::size_t curr_scope = 0;

  /**
   * @brief Stores the next scope. Defeaults to curr_scope + 1.
   */
  std::size_t next_scope = 1;

  /**
   * @brief The identifier bindings table, which can store multiple
   * identifiers with possible different sets of scopes.
   */
  std::multimap<shaka::Symbol, IdentifierData> identifier_bindings;

  /**
   * @brief Prints out a short representation of the MacroContext.
   * @param lhs The output stream.
   * @param rhs The MacroContext.
   * @return The updated reference of the output stream.
   */
  friend std::ostream& operator<<(
      std::ostream& lhs,
      const MacroContext& rhs);
};

} // namespace macro
} // namespace shaka

#endif //SHAKA_SCHEME_MACROCONTEXT_HPP
