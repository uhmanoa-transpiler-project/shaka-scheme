//
// Created by mortrax on 2/5/18.
//

#ifndef SHAKA_SCHEME_GCNODE_HPP
#define SHAKA_SCHEME_GCNODE_HPP

#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/base/DataPair.hpp"
#include "shaka_scheme/system/gc/GCData.hpp"

namespace shaka {

/**
 * @brief Defines the type of GCNode, the object which will
 * wrap over GCData, providing a managed interface to Data
 */
    class GCNode {
    public:

        GCNode(const Data& data);
        ~GCNode();

        Data& operator*();
        Data* operator->();

    private:
        GCData* gc_data;
    };


} // namespace shaka

#endif //SHAKA_SCHEME_GCNODE_HPP
