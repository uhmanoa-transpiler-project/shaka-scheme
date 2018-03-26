//
// Created by Brandon Wong on 3/26/18.
//

#ifndef SHAKA_SCHEME_GC_HPP
#define SHAKA_SCHEME_GC_HPP

#include "shaka_scheme/system/gc/GCList.hpp"
#include "shaka_scheme/system/gc/GCData.hpp"
#include "shaka_scheme/system/base/Data.hpp"

namespace shaka {

    namespace gc {

        class GC {
        public:

            GCData *create_data(const shaka::Data& data);
            int get_list_size();

        private:
            GCList list;
        };
    }
}
#endif //SHAKA_SCHEME_GC_HPP
