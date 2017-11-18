#ifndef SHAKA_SCHEME_MACRO_ENGINE_HPP
#define SHAKA_SCHEME_MACRO_ENGINE_HPP

#include "shaka_scheme/system/parser/parser_definitions.hpp"
#include "shaka_scheme/system/core/lists.hpp"
#include "shaka_scheme/system/core/types.hpp"

#include "shaka_scheme/system/exceptions/MacroExpansionException.hpp"

#include "shaka_scheme/system/parser/syntax_rules/MacroContext.hpp"

#include <map>
#include <stack>
#include <algorithm>

namespace shaka {
namespace macro {

bool is_primitive_set(Symbol symbol, MacroContext& context) {
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

MacroPtr get_macro(Symbol symbol, MacroContext& context) {
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

bool is_primitive_syntax_rules(Symbol symbol, MacroContext& context) {
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

bool is_primitive_lambda(Symbol symbol, MacroContext& context) {
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

bool is_primitive_define(Symbol symbol, MacroContext& context) {
  try {
    if (context.hvm.get_environment()->get_value(symbol)
        ->get<PrimitiveFormMarker>() == PrimitiveFormMarker("define")) {
      return true;
    }
  } catch (shaka::InvalidInputException e) {
    return false;
  }
  return false;
};

bool is_primitive_quote(Symbol symbol, MacroContext& context) {
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

bool is_primitive_define_syntax(Symbol symbol, MacroContext& context) {
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

bool is_primitive_let_syntax(Symbol symbol, MacroContext& context) {
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

bool process_define_form(NodePtr& it, MacroContext& context) {
  if (!is_primitive_define(core::car(it)->get<Symbol>(), context)) {
    return false;
  }
  using namespace shaka::core;
  if (is_proper_list(car(cdr(it))) || is_improper_list(car(cdr(it)))) {
    auto lambda_form = list(
        create_node(Symbol("lambda")),
        cdr(car(cdr(it)))
    );
    set_cdr(cdr(lambda_form), cdr(cdr(it)));
    auto rewritten_form = list(
        create_node(Symbol("define")),
        car(car(cdr(it))),
        lambda_form
    );
    it = rewritten_form;
    //std::cout << "DEFINE: rewriting define procedure form: " << *it <<
    //          std::endl;
    return process_define_form(it, context);
  }
  if (is_symbol(car(cdr(it)))) {
    //std::cout << "mapping identifier: " << car(cdr(it))
    //    ->get<Symbol>() << std::endl;
    context.map_symbol(car(cdr(it))->get<Symbol>());

    it = core::cdr(it);
    it = core::cdr(it);
    return true;
  }
};

bool process_set_form(NodePtr& it, MacroContext& context) {
  if (!is_primitive_set(core::car(it)->get<Symbol>(), context)) {
    return false;
  }
  if (!core::is_symbol(core::car(core::cdr(it)))) {
    throw MacroExpansionException(60007, "(set!) must have an identifier "
        "as its second argument");
  }
  if (core::length(it) != 3) {
    throw MacroExpansionException(60008, "(set!) expression must be a "
        "list of 3 elements");
  }
  it = core::cdr(it);
  it = core::cdr(it);
  return true;
};

bool process_quote_form(NodePtr& it, MacroContext& context) {
  if (!is_primitive_quote(core::car(it)->get<Symbol>(), context)) {
    return false;
  }
  if (core::length(it) != 2) {
    throw MacroExpansionException(60004, "(quote) cannot have more than 1 "
        "argument");
  }
  it = core::cdr(it);
  return true;
};

bool process_lambda_form(NodePtr& it, MacroContext& context) {
  if (!is_primitive_lambda(core::car(it)->get<Symbol>(), context)) {
    return false;
  }
  if (core::length(it) <= 2) {
    throw MacroExpansionException(60001, "(lambda) form must contain at "
        "least the arguments and the body expression(s)");
  }
  auto args = core::car(core::cdr(it));
  std::vector<Symbol> identifiers;
  // If the lambda is a proper or improper list, we must figure out
  // if it consists of only identifiers.
  if (core::is_pair(args)) {
    auto jt = args;
    //std::cout << "jt: " << *jt << std::endl;
    for (;
        core::is_pair(jt);
        jt = core::cdr(jt)) {
      auto item = core::car(jt);
      //std::cout << "item: " << *item << std::endl;
      if (item->get_type() != Data::Type::SYMBOL) {
        throw MacroExpansionException(60000, "(lambda) arguments must "
            "contain only identifiers");
      }
      identifiers.push_back(item->get<Symbol>());
    }
    if (jt->get_type() == Data::Type::SYMBOL) {
      //std::cout << "(lambda) improper list last args: " <<
      //
      // jt/->get<Symbol>()
      //          << std::endl;
      identifiers.push_back(jt->get<Symbol>());
    } else if (jt->get_type() != Data::Type::NULL_LIST) {
      //std::cout << *jt << std::endl;
      throw MacroExpansionException(60006, "the last argument in a "
          "(lambda) arguments list must be a symbol or a null list");
    }
    // If we got through the loop, we need to mark the identifiers with
    // the current scope before we return true;
    it = core::cdr(it);
    it = core::cdr(it);
    context.push_scope();
    for (auto identifier : identifiers) {
      //std::cout << "mapping identifier: " << identifier << std::endl;
      context.map_symbol(identifier);
    }
    // The iterator is left at the body.
    return true;
  } else if (core::is_symbol(args)) {
    //std::cout << "mapping identifier: " << *args << std::endl;
    context.map_symbol(args->get<Symbol>());
    it = core::cdr(it);
    it = core::cdr(it);
    return true;
  } else {
    throw MacroExpansionException(60002, "(lambda) arguments cannot be "
        "non-symbol types");
  }
};

std::ostream& operator<<(
    std::ostream& lhs,
    const MacroContext& rhs) {
  lhs << "MacroContext(curr_scope: " << rhs.curr_scope << " | scope_stack: { ";
  for (auto it : rhs.curr_scope_stack) {
    lhs << it << " ";
  }
  lhs << "} | curr_scopes: { ";
  for (auto it : rhs.curr_scopes) {
    lhs << it << " ";
  }
  lhs << "})";
  return lhs;
}

void run_macro_expansion(
    NodePtr root,
    MacroContext& macro_context) {
  //std::cout << "\nBEFORE TRAVERSE TREE: " << *root << std::endl;
  //std::cout << "BEFORE TRAVERSE TREE CONTEXT: " << macro_context << std::endl;
  //for (
  //  auto binding :
  //    macro_context.identifier_bindings) {
  //  //std::cout << "BEFORE TRAVERSE TREE BINDINGS {" << binding.first << " | "
  //  //    "" << binding .second.scopes << std::endl;
  //}
  int count = 0;
  bool need_to_pop_scope = false;
  if (core::is_pair(root)) {
    NodePtr proc_name = core::car(root);
    if (core::is_symbol(proc_name)) {
      Symbol identifier = proc_name->get<Symbol>();
      if (auto macro = get_macro(identifier, macro_context)) {
        //std::cout << "NEED TO EXPAND MACRO HERE!" << std::endl;
      } else {
        if (process_define_form(root, macro_context)) {
          //std::cout << "PRIMITIVE: define" << std::endl;
        } else if (process_set_form(root, macro_context)) {
          //std::cout << "PRIMITIVE: set" << std::endl;
        } else if (process_lambda_form(root, macro_context)) {
          //std::cout << "PRIMITIVE: lambda" << std::endl;
          need_to_pop_scope = true;
        } else if (process_quote_form(root, macro_context)) {
          //std::cout << "PRIMITIVE: quote" << std::endl;
          return;
        } else if (is_primitive_define_syntax(identifier, macro_context)) {
          //std::cout << "PRIMITIVE: define-syntax" << std::endl;
          need_to_pop_scope = true;
          macro_context.push_scope();
        } else if (is_primitive_let_syntax(identifier, macro_context)) {
          //std::cout << "PRIMITIVE: let-syntax" << std::endl;
          need_to_pop_scope = true;
          macro_context.push_scope();
        } else if (is_primitive_syntax_rules(identifier, macro_context)) {
          //std::cout << "PRIMITIVE: syntax-rules" << std::endl;
          need_to_pop_scope = true;
          macro_context.push_scope();
        } else {
          //std::cout << "NON-PRIMITIVE: " << *proc_name << std::endl;
        }
      }
    } else if (!core::is_pair(proc_name)) {
      throw MacroExpansionException(60010, "procedure name cannot be a "
          "non-identifier or non-procedure call");
    }
  }
  for (NodePtr it = root;
       core::is_pair(it);
       it = core::cdr(it), count++) {
    auto item = core::car(it);
    //std::cout << "#" << count << ": " << *it << " | " << *item << std::endl;
    if (core::is_proper_list(item)) {
      run_macro_expansion(item, macro_context);
    }
  }
  if (need_to_pop_scope) {
    macro_context.pop_scope();
  }
  //std::cout << "after TRAVERSE TREE: " << *root << std::endl;
  //std::cout << "after TRAVERSE TREE CONTEXT: " << macro_context << std::endl;
  //for (
  //  auto binding :
  //    macro_context.identifier_bindings) {
  //  //std::cout << "after TRAVERSE TREE BINDINGS {" << binding.first << " | "
  //  //    "" << binding .second.scopes << std::endl;
  //} //std::cout << std::endl;
}

} // namespace macro
} // namespace shaka

#endif //SHAKA_SCHEME_MACRO_ENGINE_HPP
