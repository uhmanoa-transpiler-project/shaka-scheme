//
// Created by mortrax on 3/26/18.
//

#include "shaka_scheme/system/gc/init.hpp"
#include "shaka_scheme/system/gc/GC.hpp"
#include "shaka_scheme/system/base/DataPair.hpp"

namespace shaka {
    namespace gc {

        void init_create_node(GC& gc) {
            create_node = [&gc](const Data& data) {

                return GCNode(gc.create_data(data));
            };
        }
    }
}

