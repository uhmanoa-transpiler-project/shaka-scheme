//
// Created by mortrax on 2/8/18.
//

#ifndef SHAKA_SCHEME_GCDATA_HPP
#define SHAKA_SCHEME_GCDATA_HPP
#include "shaka_scheme/system/base/Data.hpp"

class GC;

namespace shaka {

    namespace gc {

        /**
         * @brief Implements the type of GCData, the internal
         * manager object which holds the mark bit, determining
         * when a data object is reclaimed by the Garbage Collector
         */
        class GCData {
        public:

            ~GCData();

            GCData *get_next();
            void set_next(GCData *next_node);
            void mark();
            void unmark();
            bool is_marked();

            Data &get_data();
            Data *get_data_address();

            friend class GC;

        private:
            bool marked;
            Data data;
            GCData *next;

            GCData(const Data &data);
        };
    }
}
#endif //SHAKA_SCHEME_GCDATA_HPP
