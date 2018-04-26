//
// Created by mortrax on 4/16/18.
//
#include "shaka_scheme/system/gc/GCNode.hpp"
#include "shaka_scheme/system/vm/HeapVirtualMachine.hpp"
#include "shaka_scheme/system/gc/GCData.hpp"

namespace shaka {
namespace gc {

void mark_accumulator(const Accumulator& a) {
  mark_node(a);
}

void mark_expression(const Expression& e) {
  mark_node(e);
}

void mark_environment(const Environment& env) {
  for(auto it = env.get_bindings().begin(); it != env.get_bindings().end();
      it++) {
    mark_node(it->second);
  }
}

void mark_call_frame(const CallFrame& f) {
}

void mark_value_rib(const ValueRib& vr) {
  for(auto it = vr.begin(); it != vr.end(); it++) {
    mark_node(*it);
  }
}

void mark(const HeapVirtualMachine& hvm) {
  mark_accumulator(hvm.get_accumulator());
  mark_expression(hvm.get_expression());
  mark_environment(*hvm.get_environment());
  mark_call_frame(*hvm.get_call_frame());
  mark_value_rib(hvm.get_value_rib());
}

void mark_node(const GCNode& node) {

  // Check for cycles
  if (node.gc_data->is_marked()) {
    return;
  }

  node.gc_data->mark();
  switch(node->get_type()) {
  case shaka::Data::Type::DATA_PAIR: {
    // If the argument is a pair, mark its car and cdr
    mark_node(node->get<DataPair>().car());
    mark_node(node->get<DataPair>().cdr());
    break;
  }
  case shaka::Data::Type::CLOSURE: {
    // If the argument is a closure, mark its environment, frame, and expression
    Closure c = node->get<Closure>();
    if (c.get_call_frame() != nullptr) {
      mark_call_frame(*c.get_call_frame());
    }
    if (c.get_environment() != nullptr) {
      mark_environment(*c.get_environment());
    }
    if (c.get_function_body() != nullptr) {
      mark_expression(c.get_function_body());
    }
    break;
  }
  case shaka::Data::Type::CALL_FRAME: {
    // If the argument is a call frame, mark its contents
    mark_call_frame(node->get<CallFrame>());
    break;
  }
  default:
    break;

  /*
   * The following two cases will be added when the respective classes
   * have been rolled into the Data variant class
   * case shaka::Data::Type::VECTOR
   * case shaka::Data::Type::BYTE_VECTOR
   */
  }
}

}
}

