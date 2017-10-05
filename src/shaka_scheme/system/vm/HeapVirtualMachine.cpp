//
// Created by Billy Wooton on 10/2/17.
//

#include "shaka_scheme/system/vm/HeapVirtualMachine.hpp"
#include "shaka_scheme/system/base/Environment.hpp"
#include "shaka_scheme/system/vm/CallFrame.hpp"

namespace shaka {

HeapVirtualMachine::~HeapVirtualMachine() {}

NodePtr HeapVirtualMachine::evaluate_assembly_instruction() {
  shaka::DataPair& exp_pair = exp->get<DataPair>();
  shaka::Symbol& instruction = exp_pair.car()->get<Symbol>();

  // (halt)
  if (instruction == shaka::Symbol("halt")) {
    return this->acc;
  }

  // (refer var x)
  if (instruction == shaka::Symbol("refer")) {
    shaka::DataPair& exp_cdr = exp_pair.cdr()->get<DataPair>();
    shaka::Symbol& var = exp_cdr.car()->get<Symbol>();
    this->set_accumulator(env->get_value(var));

    DataPair& next_pair= exp_cdr.cdr()->get<DataPair>();
    NodePtr next_expression = next_pair.car();

    this->set_expression(next_expression);

    return nullptr;
  }

  // (constant obj x)
  if (instruction == shaka::Symbol("constant")) {
    shaka::DataPair& exp_cdr = exp_pair.cdr()->get<DataPair>();
    NodePtr obj = exp_cdr.car();

    this->set_accumulator(obj);

    DataPair& next_pair = exp_cdr.cdr()->get<DataPair>();

    NodePtr next_expression = next_pair.car();

    this->set_expression(next_expression);
  }

  // (test then else)
  if (instruction == shaka::Symbol("test")) {
    shaka::DataPair& exp_cdr = exp_pair.cdr()->get<DataPair>();
    NodePtr then_exp = exp_cdr.car();
    NodePtr else_exp = exp_cdr.cdr()->get<DataPair>().car();

    if (this->acc->get_type() == shaka::Data::Type::SYMBOL &&
        this->acc->get<Symbol>() == Symbol("#f")) {

      this->set_expression(else_exp);
    }

    else {
      this->set_expression(then_exp);
    }

    return nullptr;
  }

  // (assign var x)

  if (instruction == shaka::Symbol("assign")) {
    shaka::DataPair& exp_cdr = exp_pair.cdr()->get<DataPair>();
    shaka::Symbol& var = exp_cdr.car()->get<Symbol>();

    DataPair& next_pair = exp_cdr.cdr()->get<DataPair>();

    NodePtr expression = next_pair.car();

    this->env->set_value(var, this->acc);

    this->set_expression(expression);

    return nullptr;
  }

  // (frame x ret)

  if (instruction == shaka::Symbol("frame")) {
    shaka::DataPair& expr_cdr = exp_pair.cdr()->get<DataPair>();

    NodePtr x = expr_cdr.car();

    NodePtr ret = expr_cdr.cdr()->get<DataPair>().car();

    FramePtr new_frame =
        std::make_shared<CallFrame>(ret, this->env,
                                    this->rib, this->frame);
    this->frame = new_frame;
    this->set_expression(x);

    shaka::ValueRib vr;

    this->set_value_rib(vr);

    return nullptr;
  }

  // (argument x)

  if (instruction == shaka::Symbol("argument")) {
    shaka::DataPair& exp_cdr = exp_pair.cdr()->get<DataPair>();

    NodePtr x = exp_cdr.car();

    this->rib.push_back(this->acc);

    this->set_expression(x);

    return nullptr;
  }

  // (return)

  if (instruction == shaka::Symbol("return")) {
    this->set_expression(this->frame->get_next_expression());
    this->set_value_rib(this->frame->get_value_rib());
    this->set_environment(this->frame->get_environment_pointer());
    this->frame = this->frame->get_next_frame();

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

