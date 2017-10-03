//
// Created by Billy Wooton on 10/2/17.
//

#include "shaka_scheme/system/vm/HeapVirtualMachine.hpp"
#include "shaka_scheme/system/base/Environment.hpp"

namespace shaka {

HeapVirtualMachine::~HeapVirtualMachine() {}

NodePtr HeapVirtualMachine::evaluate_assembly_instruction() {
  shaka::DataPair& exp_pair = exp->get<DataPair>();
  shaka::Symbol& instruction = exp_pair.car()->get<Symbol>();

  if (instruction == shaka::Symbol("halt")) {
    return this->acc;
  }

  if (instruction == shaka::Symbol("refer")) {
    shaka::DataPair& exp_cdr = exp_pair.cdr()->get<DataPair>();
    shaka::Symbol& var = exp_cdr.car()->get<Symbol>();
    this->set_accumulator(env->get_value(var));

    NodePtr next_expression = exp_cdr.cdr();

    this->set_expression(next_expression);

    return nullptr;
  }

  return nullptr;
}

Accumulator HeapVirtualMachine::get_accumulator() const {
  return this->acc;
}

Expression HeapVirtualMachine::get_expression() const {
  return this->exp;
}

EnvPtr HeapVirtualMachine::get_environment() const {
  return this->env;
}

ValueRib HeapVirtualMachine::get_value_rib() const {
  return this->rib;
}

FramePtr HeapVirtualMachine::get_call_frame() const {
  return this->frame;
}

void HeapVirtualMachine::set_accumulator(Accumulator a) {
  this->acc = a;
}

void HeapVirtualMachine::set_expression(Expression x) {
  this->exp = x;
}

void HeapVirtualMachine::push_call_frame(FramePtr s) {
  this->frame = s;
}

void HeapVirtualMachine::set_environment(EnvPtr e) {
  this->env = e;
}

void HeapVirtualMachine::set_value_rib(ValueRib r) {
  this->rib = r;
}


} //namespace shaka

