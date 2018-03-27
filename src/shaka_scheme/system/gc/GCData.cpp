//
// Created by mortrax on 2/20/18.
//
#include "shaka_scheme/system/gc/GCData.hpp"

namespace shaka {

    namespace gc {

        GCData::GCData(const Data &data) :
            marked(false),
            data(data),
            next(nullptr) {}

        GCData::~GCData() {}

        GCData *GCData::get_next() {
            return this->next;
        }

        void GCData::set_next(GCData *next_node) {
            this->next = next_node;
        }

        void GCData::mark() {
            this->marked = true;
        }

        void GCData::unmark() {
            this->marked = false;
        }

        bool GCData::is_marked() {
            return this->marked;
        }

        Data &GCData::get_data() {
            return this->data;
        }

        Data *GCData::get_data_address() {
            return &this->data;
        }

    }
}
