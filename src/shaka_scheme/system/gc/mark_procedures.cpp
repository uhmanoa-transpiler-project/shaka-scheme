//
// Created by mortrax on 4/16/18.
//
#include "shaka_scheme/system/gc/GCNode.hpp"
#include "shaka_scheme/system/vm/HeapVirtualMachine.hpp"
#include "shaka_scheme/system/gc/GCData.hpp"

namespace shaka {
namespace gc {

static void mark_accumulator(Accumulator a) {
}

static void mark_expression(Expression e) {
}

static void mark_environment(Environment env) {
}

static void mark_call_frame(CallFrame f) {
}

static void mark_value_rib(ValueRib vr) {
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
    mark_call_frame(*c.get_call_frame());
    mark_environment(*c.get_environment());
    mark_expression(c.get_function_body());
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

