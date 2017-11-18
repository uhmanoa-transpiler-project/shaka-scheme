#include "shaka_scheme/system/parser/syntax_rules/MacroContext.hpp"

namespace shaka {
namespace macro {

std::ostream& operator<<(std::ostream& left, const ScopeSet& right) {
  left << "ScopeMap({ ";
  for (auto it : right) {
    left << it << " ";
  }
  left << "})";
  return left;
}

MacroContext::MacroContext(HeapVirtualMachine& hvm) :
    hvm(hvm),
    curr_scope(0) {
  curr_scopes.insert(curr_scope);
  curr_scope_stack.push_back(curr_scope);
  curr_scope = next_scope;
  next_scope++;
  curr_scopes.insert(curr_scope);
  curr_scope_stack.push_back(curr_scope);
}

void MacroContext::push_scope() {
  curr_scope = next_scope;
  next_scope++;
  curr_scopes.insert(curr_scope);
  curr_scope_stack.push_back(curr_scope);
}

void MacroContext::pop_scope() {
  curr_scopes.erase(curr_scope);
  auto temp_scope = curr_scope_stack[curr_scope_stack.size() - 1];
  curr_scope_stack.pop_back();
  curr_scope = temp_scope;
}

void MacroContext::map_symbol(Symbol symbol) {
  IdentifierData id_data(curr_scopes, nullptr);
  identifier_bindings.insert({ symbol, std::move(id_data)});
}

void MacroContext::map_macro(Symbol symbol, MacroPtr macro) {
  IdentifierData id_data(curr_scopes, std::move(macro));
  identifier_bindings.insert({ symbol, std::move(id_data) });
}

std::multimap<shaka::Symbol, IdentifierData>::const_iterator
MacroContext::get_bindings(Symbol symbol) {
  return identifier_bindings.find(symbol);
}



} // namespace macro
} // namespace shaka
