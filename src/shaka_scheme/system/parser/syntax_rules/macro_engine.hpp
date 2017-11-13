//
// Created by aytas on 11/8/2017.
//

#ifndef SHAKA_SCHEME_MACRO_ENGINE_HPP
#define SHAKA_SCHEME_MACRO_ENGINE_HPP

#include "shaka_scheme/system/parser/parser_definitions.hpp"
#include "shaka_scheme/system/core/lists.hpp"
#include "shaka_scheme/system/core/types.hpp"

#include <map>
#include <stack>
#include <algorithm>

namespace shaka {
namespace macro {

template<typename T>
struct TreeNode {

  TreeNode(const T& data, std::shared_ptr<TreeNode<T>> parent = nullptr) :
      data(data),
      parent(parent) {}

  TreeNode(const TreeNode& other) = delete;

  TreeNode(TreeNode&& other) :
      data(std::move(other.data)),
      children(std::move(other.children)),
      parent(std::move(other.parent)) {}

  T data;
  std::vector<std::shared_ptr<TreeNode>> children;
  std::weak_ptr<TreeNode> parent;
};

using ScopeMap = std::map<shaka::Symbol, std::set<std::size_t>>;
struct ScopeData {
  std::size_t scope_id;
  ScopeMap scopes;
};

std::ostream& operator<<(std::ostream& left, const std::set<std::size_t>&
right) {
  left << "ScopeMap({ ";
  for (auto it : right) {

    left << it << " ";
  }
  left << "})";
  return left;
}

using ScopeTree = TreeNode<ScopeData>;
using ScopePtr = std::shared_ptr<ScopeTree>;

using ScopeSet = std::set<std::size_t>;

struct SyntaxRulesMacro;
using MacroPtr = std::shared_ptr<SyntaxRulesMacro>;

struct SyntaxRulesMacro {

};

struct IdentifierData {
  IdentifierData(ScopeSet scopes, MacroPtr macro = nullptr) :
      scopes(scopes),
      macro(std::move(macro)) {}

  ScopeSet scopes;
  MacroPtr macro;
};

struct MacroContextChecker {

  MacroContextChecker(HeapVirtualMachine& hvm) :
      curr_scope(0),
      hvm(hvm) {
    curr_scopes.insert(curr_scope);
    curr_scope_stack.push_back(curr_scope);
    ++curr_scope;
    curr_scopes.insert(curr_scope);
    curr_scope_stack.push_back(curr_scope);
  }

  void push_scope() {
    ++curr_scope;
    curr_scopes.insert(curr_scope);
    curr_scope_stack.push_back(curr_scope);
  }

  void pop_scope() {
    curr_scopes.erase(curr_scope);
    auto temp_scope = curr_scope_stack[curr_scope_stack.size() - 1];
    curr_scope_stack.pop_back();
    curr_scope = temp_scope;
  }

  void map_symbol(Symbol symbol) {
    IdentifierData id_data (curr_scopes, nullptr);
    identifier_bindings.insert({
                                   symbol,
                               std::move(id_data)});
  }

  void map_macro(Symbol symbol, MacroPtr macro) {
    IdentifierData id_data (curr_scopes, std::move(macro));
    identifier_bindings.insert({
                                   symbol,
                                   std::move(id_data)
                               });
  }

  std::multimap<shaka::Symbol, IdentifierData>::const_iterator
  get_bindings(Symbol symbol) {
    return identifier_bindings.find(symbol);
  }

  HeapVirtualMachine& hvm;
  std::vector<std::size_t> curr_scope_stack;
  ScopeSet curr_scopes;
  std::size_t curr_scope = 1;
  std::multimap<shaka::Symbol, IdentifierData> identifier_bindings;

  friend std::ostream& operator<<(
      std::ostream& lhs,
      const MacroContextChecker& rhs);
};

auto is_primitive_set = [](Symbol symbol, MacroContextChecker& context) {
  try {
    if (context.hvm.get_environment()->get_value(symbol)
        ->get<PrimitiveFormMarker>() == PrimitiveFormMarker("set!")) {
      return true;
    }
  } catch (shaka::InvalidInputException e) {
    return false;
  }
  return false;
};

auto get_macro = [](Symbol symbol, MacroContextChecker& context) {
  IdentifierData current_binding(context.curr_scopes, nullptr);
  IdentifierData max_data(std::set<std::size_t>(), nullptr);
  for (auto it = context.get_bindings(symbol);
       it != context.identifier_bindings.end();
       ++it) {
    const auto scopes = it->second.scopes;
    std::vector<std::size_t> intersect;
    std::set_intersection(
        scopes.begin(),
        scopes.end(),
        current_binding.scopes.begin(),
        current_binding.scopes.end(),
        std::back_inserter(intersect)
    );
    if (intersect.size() > max_data.scopes.size()) {
      max_data = it->second;
    }
  }
  return max_data.macro;
};

auto is_primitive_syntax_rules =
    [](Symbol symbol, MacroContextChecker& context) {
      try {
        if (context.hvm.get_environment()->get_value(symbol)
            ->get<PrimitiveFormMarker>()
            == PrimitiveFormMarker("syntax-rules")) {
          return true;
        }
      } catch (shaka::InvalidInputException e) {
        return false;
      }
      return false;
    };

auto is_primitive_lambda = [](Symbol symbol, MacroContextChecker& context) {
  try {
    if (context.hvm.get_environment()->get_value(symbol)
        ->get<PrimitiveFormMarker>() == PrimitiveFormMarker("lambda")) {
      return true;
    }
  } catch (shaka::InvalidInputException e) {
    return false;
  }
  return false;
};

auto is_primitive_quote = [](Symbol symbol, MacroContextChecker& context) {
  try {
    if (context.hvm.get_environment()->get_value(symbol)
        ->get<PrimitiveFormMarker>() == PrimitiveFormMarker("quote")) {
      return true;
    }
  } catch (shaka::InvalidInputException e) {
    return false;
  }
  return false;
};

auto is_primitive_define_syntax =
    [](Symbol symbol, MacroContextChecker& context) {
      try {
        if (context.hvm.get_environment()->get_value(symbol)
            ->get<PrimitiveFormMarker>() ==
            PrimitiveFormMarker("define-syntax")) {
          return true;
        }
      } catch (shaka::InvalidInputException e) {
        return false;
      }
      return false;
    };

auto is_primitive_let_syntax =
    [](Symbol symbol, MacroContextChecker& context) {
      try {
        if (context.hvm.get_environment()->get_value(symbol)
            ->get<PrimitiveFormMarker>() ==
            PrimitiveFormMarker("let-syntax")) {
          return true;
        }
      } catch (shaka::InvalidInputException e) {
        return false;
      }
      return false;
    };

std::ostream& operator<<(
    std::ostream& lhs,
    const MacroContextChecker& rhs) {
  lhs << "MacroContextChecker(";
  lhs << "curr_scope: " << rhs.curr_scope << " | ";
  lhs << "scope_stack: { ";
  for (auto it : rhs.curr_scope_stack) {
    lhs << it << " ";
  }
  lhs << "} | ";
  lhs << "curr_scopes: { ";
  for (auto it : rhs.curr_scopes) {
    lhs << it << " ";
  }
  lhs << "}";
  lhs << ")";
  return lhs;
}

} // namespace macro
} // namespace shaka

#endif //SHAKA_SCHEME_MACRO_ENGINE_HPP
