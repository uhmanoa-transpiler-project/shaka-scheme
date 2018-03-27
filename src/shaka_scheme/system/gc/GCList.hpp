//
// Created by mortrax on 2/8/18.
//

#ifndef SHAKA_SCHEME_GCLIST_HPP
#define SHAKA_SCHEME_GCLIST_HPP

namespace shaka {

    namespace gc {

        class GCData;

        class GCList {
        public:

            GCList();
            ~GCList();

            bool is_empty();
            int get_size();
            void add_data(shaka::gc::GCData *data);
            void sweep();

        private:
            GCData *head;
            int size;
        };
    }
}
#endif //SHAKA_SCHEME_GCLIST_HPP
