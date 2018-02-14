//
// Created by mortrax on 2/8/18.
//

#ifndef SHAKA_SCHEME_GCDATA_HPP
#define SHAKA_SCHEME_GCDATA_HPP

namespace shaka {

    /**
     * @brief Implements the type of GCData, the internal
     * manager object which holds the mark bit, determining
     * when a data object is reclaimed by the Garbage Collector
     */
    class GCData {
    public:
        GCData(const Data& data);
        ~GCData();

        GCData *get_next();
        void mark();
        void unmark();
        bool is_marked();

    private:
        bool marked;
        Data data;
        GCData *next;
    };

}
#endif //SHAKA_SCHEME_GCDATA_HPP
