//
// Created by mortrax on 2/5/18.
//

#include "shaka_scheme/system/gc/GCNode.hpp"

shaka::GCNode *shaka::GCNode::get_next() const {
    return this->next;
}

bool shaka::GCNode::is_marked() const {
    return this->marked;
}

void shaka::GCNode::mark() {
    this->marked = true;
}

void shaka::GCNode::unmark() {
    this->marked = false;
}

template<> shaka::String& shaka::GCNode::get<shaka::String>() {
    return this->data->get<shaka::String>();
}
template<> shaka::Symbol& shaka::GCNode::get<shaka::Symbol>() {
    return this->data->get<shaka::Symbol>();
}
template<> shaka::Boolean& shaka::GCNode::get<shaka::Boolean>() {
    return this->data->get<shaka::Boolean>();
}
template<> shaka::DataPair& shaka::GCNode::get<shaka::DataPair>() {
    return this->data->get<shaka::DataPair>();
}
template<> shaka::Closure& shaka::GCNode::get<shaka::Closure>() {
    return this->data->get<shaka::Closure>();
}
template<> shaka::CallFrame& shaka::GCNode::get<shaka::CallFrame>() {
    return this->data->get<shaka::CallFrame>();
}
template<> shaka::PrimitiveFormMarker& shaka::GCNode::get<shaka::PrimitiveFormMarker>() {
    return this->data->get<shaka::PrimitiveFormMarker>();
}
template<> shaka::Number& shaka::GCNode::get<shaka::Number>() {
    return this->data->get<shaka::Number>();
}


