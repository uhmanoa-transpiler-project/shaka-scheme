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
            GCList(const GCList& other) = delete;
            GCList(GCList&& other);

            bool is_empty();
            int get_size() const;
            void add_data(shaka::gc::GCData *data);
            void sweep();

        private:
            void swap(GCList& list1, GCList& list2);

            int list_size;
            GCData *head;
        };
    }
}
#endif //SHAKA_SCHEME_GCLIST_HPP
