//
// Created by Brandon Wong on 3/26/18.
//

#include "shaka_scheme/system/gc/GC.hpp"

namespace shaka {

    namespace gc {

        GC::GC() {}
        GC::~GC() {}

        GC::GC(GC&& other) : list(std::move(other.list)) {}

        GCData* GC::create_data(const shaka::Data& data) {
            GCData *gcd = new GCData(data);
            this->list.add_data(gcd);
            return gcd;
        }

        int GC::get_size() {
            return this->list.get_size();
        }

        void GC::sweep() {
            this->list.sweep();
        }
    }
}