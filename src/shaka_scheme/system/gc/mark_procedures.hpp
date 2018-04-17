//
// Created by mortrax on 4/16/18.
//

#ifndef SHAKA_SCHEME_MARK_PROCEDURES_HPP
#define SHAKA_SCHEME_MARK_PROCEDURES_HPP

namespace shaka {

class HeapVirtualMachine;

namespace gc {

class GCNode;


extern void mark(const HeapVirtualMachine& hvm);
extern void mark_node(const GCNode& node);

}
}

#endif //SHAKA_SCHEME_MARK_PROCEDURES_HPP
