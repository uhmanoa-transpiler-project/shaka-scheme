//
// Created by mortrax on 2/8/18.
//

#ifndef SHAKA_SCHEME_GCLIST_HPP
#define SHAKA_SCHEME_GCLIST_HPP

#include "shaka_scheme/system/gc/GCData.hpp"

namespace shaka {

    class GCList {

    public:
        GCList();
        ~GCList();

        bool is_empty();
        int get_size();
        void add_data(GCData *data);
        void sweep();

    private:
        GCData *head;
        int size;

    };
}
#endif //SHAKA_SCHEME_GCLIST_HPP
