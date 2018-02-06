//
// Created by mortrax on 2/5/18.
//

#ifndef SHAKA_SCHEME_GCNODE_HPP
#define SHAKA_SCHEME_GCNODE_HPP

#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/base/DataPair.hpp"

namespace shaka {

/**
 * @brief Defines the type of GCNode, the object which will
 * wrap over Data, keeping track of a given reference,
 * and maintaining the mark-bit for each allocated object
 */
    class GCNode {

    public:

        GCNode(const Data& data, GCNode *next) {
            this->data = new Data(data);
            this->next = next;
            this->marked = false;
        }

        ~GCNode() {
            delete this->data;
        }

        GCNode *get_next() const;

        bool is_marked() const;

        void mark();

        void unmark();

        template<typename T>
        T& get();

        Data::Type get_type() const;

    private:
        bool marked;
        Data *data;
        GCNode *next;
    };

    template<> shaka::String& shaka::GCNode::get<shaka::String>();
    template<> shaka::Symbol& shaka::GCNode::get<shaka::Symbol>();
    template<> shaka::Boolean& shaka::GCNode::get<shaka::Boolean>();
    template<> shaka::DataPair& shaka::GCNode::get<shaka::DataPair>();
    template<> shaka::Closure& shaka::GCNode::get<shaka::Closure>();
    template<> shaka::CallFrame& shaka::GCNode::get<shaka::CallFrame>();
    template<> shaka::PrimitiveFormMarker& shaka::GCNode::get<shaka::PrimitiveFormMarker>();
    template<> shaka::Number& shaka::GCNode::get<shaka::Number>();

} // namespace shaka

#endif //SHAKA_SCHEME_GCNODE_HPP
