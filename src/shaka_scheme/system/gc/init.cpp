//
// Created by mortrax on 3/26/18.
//

#include "shaka_scheme/system/gc/init.hpp"

namespace shaka {
    namespace gc {

        NodePtrFactory create_node;

        NodePtrFactory init_create_node(GC& gc) {
            create_node = [&gc](const Data& data) {
                return gc.create_data(data);
            };
        }
    }
}

