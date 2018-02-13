//
// Created by Billy Wooton on 10/11/17.
//

#include "shaka_scheme/system/vm/Closure.hpp"
#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/core/lists.hpp"

namespace shaka {

class Data;

Closure::Closure(EnvPtr env,
                 NodePtr fb,
                 VariableList vl,
                 CallablePtr cl,
                 FramePtr frame,
                 bool arity) :
    env(env),
    func_body(fb),
    variable_list(vl),
    callable(cl),
    frame(frame),
    variable_arity(arity) {}

Closure::Closure(Callable cl, bool arity) {

    this->env = nullptr;
    this->func_body = nullptr;
    this->variable_list = std::vector<shaka::Symbol>(0);
    this->callable = std::make_shared<Callable>(cl);
    this->frame = nullptr,
    this->variable_arity = arity;
}

Closure::Closure() {
  env = std::make_shared<Environment>(nullptr);
  func_body = std::make_shared<Data>();
  variable_list = std::vector<shaka::Symbol>(0);
  callable = nullptr;
  frame = std::make_shared<CallFrame>();
  variable_arity = false;

}

NodePtr Closure::get_function_body() {
  return this->func_body;
}

void Closure::extend_environment(ValueRib vr) {

  EnvPtr new_frame = std::make_shared<Environment>(env);

  if (this->variable_arity) {

    size_t i = 0;
    // The var_args parameter should always be last in the variable list
    while (i < variable_list.size() - 1) {
      new_frame->set_value(variable_list[i], vr[i]);
      i++;
    }

    if (i < vr.size()) {
      NodePtr var_args = core::list();
      for (;i < vr.size(); i++) {
        var_args = core::append(var_args, core::list(vr[i]));
      }
      new_frame->set_value(
          variable_list[variable_list.size() - 1],
          var_args
      );
    }

  }

  else {
    for (size_t i = 0; i < variable_list.size(); i++) {
      new_frame->set_value(variable_list[i], vr[i]);
    }
  }

  this->env = new_frame;
}

EnvPtr Closure::get_environment() {
  return this->env;
}

std::deque<NodePtr> Closure::call(std::deque<NodePtr> args) {
  return (*callable)(args);
}

FramePtr Closure::get_call_frame() {
  return this->frame;
}

VariableList Closure::get_variable_list() {
  return this->variable_list;
}

bool Closure::is_native_closure() {
  return this->callable != nullptr;
}

bool Closure::is_continuation_closure() {
  return this->frame != nullptr;
}

bool Closure::is_variable_arity() {
  return this->variable_arity;
}


}
