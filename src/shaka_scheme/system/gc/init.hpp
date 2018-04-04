//
// Created by mortrax on 3/26/18.
//

#ifndef SHAKA_SCHEME_INIT_HPP
#define SHAKA_SCHEME_INIT_HPP

#include <functional>
#include "shaka_scheme/system/gc/GCNode.hpp"
#include "shaka_scheme/system/base/Data.hpp"

namespace shaka {
    namespace gc {

        class GC;
        using NodePtr = GCNode;
        using NodePtrFactory = std::function<NodePtr(const Data&)>;

        NodePtrFactory init_create_node(GC& gc);



    }
}

#endif //SHAKA_SCHEME_INIT_HPP
