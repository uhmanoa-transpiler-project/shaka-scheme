//
// Created by Kirsten on 2/19/2018.
//

#include "shaka_scheme/system/gc/GCNode.hpp"

namespace shaka {

    namespace gc {

        GCNode::GCNode(GCData *data) {
            gc_data = data;
        }

        GCNode::~GCNode() {}

        Data &GCNode::operator*() {
            return this->gc_data->get_data();
        }

        Data *GCNode::operator->() {
            return this->gc_data->get_data_address();
        }
    }
}
