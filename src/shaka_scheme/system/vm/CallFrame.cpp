//
// Created by Billy Wooton on 9/18/17.
//

#include "shaka_scheme/system/vm/CallFrame.hpp"
#include "shaka_scheme/system/base/Data.hpp"



shaka::CallFrame::CallFrame(shaka::Expression ret,
                            shaka::EnvPtr env,
                            shaka::ValueRib rib,
                            shaka::FramePtr next_frame) :
  return_expression(ret),
  env(env),
  value_rib(rib),
  next_frame(next_frame) {}

shaka::CallFrame::CallFrame() {
  //return_expression = std::make_shared<Data>();
  return_expression = create_node(Data());
  env = std::make_shared<Environment>(nullptr);
  value_rib = std::deque<NodePtr>(0);
  next_frame = nullptr;
}


shaka::Expression shaka::CallFrame::get_next_expression() const {
  return return_expression;
}

shaka::EnvPtr shaka::CallFrame::get_environment_pointer() const {
  return env;
}

shaka::ValueRib shaka::CallFrame::get_value_rib() const {
  return value_rib;
}

shaka::FramePtr shaka::CallFrame::get_next_frame() const {
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




