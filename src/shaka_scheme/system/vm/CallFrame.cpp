//
// Created by Billy Wooton on 9/18/17.
//

#include "CallFrame.hpp"


shaka::CallFrame::CallFrame(shaka::Expression ret,
                            shaka::EnvPtr env,
                            shaka::ValueRib rib,
                            shaka::FramePtr next_frame) :
  return_expression(ret),
  env(env),
  value_rib(rib),
  next_frame(next_frame) {}


shaka::Expression shaka::CallFrame::get_next_expression() {
  return return_expression;
}

shaka::EnvPtr shaka::CallFrame::get_environment_pointer() {
  return env;
}

shaka::ValueRib shaka::CallFrame::get_value_rib() {
  return value_rib;
}

shaka::FramePtr shaka::CallFrame::get_next_frame() {
  return next_frame;
}

void shaka::CallFrame::set_next_expression(shaka::Expression exp) {
  this->return_expression = exp;
}

void shaka::CallFrame::set_environment_pointer(shaka::EnvPtr env) {
  this->env = env;
}

void shaka::CallFrame::set_next_frame(shaka::FramePtr next_frame) {
  this->next_frame = next_frame;
}

void shaka::CallFrame::set_value_rib(shaka::ValueRib rib) {
  this->value_rib = rib;
}




