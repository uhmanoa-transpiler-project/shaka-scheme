//
// Created by mortrax on 4/16/18.
//

#ifndef SHAKA_SCHEME_MARK_PROCEDURES_HPP
#define SHAKA_SCHEME_MARK_PROCEDURES_HPP
#include <deque>

namespace shaka {

class HeapVirtualMachine;
class Environment;
class CallFrame;

namespace gc {

class GCNode;

using NodePtr = GCNode;
using Accumulator = NodePtr;
using Expression = NodePtr;
using ValueRib = std::deque<NodePtr>;

extern void mark(const HeapVirtualMachine& hvm);
extern void mark_node(const GCNode& node);
extern void mark_accumulator(const Accumulator& acc);
extern void mark_environment(const Environment& env);
extern void mark_expression(const Expression& e);
extern void mark_call_frame(const CallFrame& f);
extern void mark_value_rib(const ValueRib& vr);


}
}

#endif //SHAKA_SCHEME_MARK_PROCEDURES_HPP
