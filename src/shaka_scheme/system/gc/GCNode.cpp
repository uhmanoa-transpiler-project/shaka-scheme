//
// Created by Kirsten on 2/19/2018.
//

#include "shaka_scheme/system/gc/GCNode.hpp"
#include "shaka_scheme/system/gc/GCData.hpp"


namespace shaka {

    namespace gc {
        GCNode::GCNode() :
          gc_data(nullptr) {}

        GCNode::GCNode(GCData *data) {
            gc_data = data;
        }

        GCNode::~GCNode() {}

        Data &GCNode::operator*() const {
            return this->gc_data->get_data();
        }

        Data *GCNode::operator->() const {
            return this->gc_data->get_data_address();
        }

        GCNode::operator bool() const {
          return this->gc_data != nullptr;
        }

        bool operator==(const GCNode& lhs, const GCNode& rhs) {
          return lhs.gc_data == rhs.gc_data;
        }

        bool operator!=(const GCNode& lhs, const GCNode& rhs) {
          return !operator==(lhs, rhs);
        }
    }
}
