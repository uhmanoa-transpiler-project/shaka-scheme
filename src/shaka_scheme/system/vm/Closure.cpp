//
// Created by Billy Wooton on 10/11/17.
//

#include "shaka_scheme/system/vm/Closure.hpp"

namespace shaka {

Closure::Closure(EnvPtr env,
                 NodePtr fb,
                 VariableList vl,
                 Callable cl,
                 FramePtr frame) :
    env(env),
    func_body(fb),
    variable_list(vl),
    callable(cl),
    frame(frame) {}

NodePtr Closure::get_function_body() {
  return this->func_body;
}

void Closure::extend_environment(ValueRib vr) {
  for (int i = 0; i < variable_list.size(); i++) {
    env->set_value(variable_list[i], vr[i]);
  }
}

EnvPtr Closure::get_environment() {
  return this->env;
}

std::vector<NodePtr> Closure::call(std::vector<NodePtr> args) {
  return (*callable)(args);
}


}
