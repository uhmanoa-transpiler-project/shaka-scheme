//
// Created by Kirsten on 2/19/2018.
//

#include "shaka_scheme/system/gc/GCNode.hpp"
#include "shaka_scheme/system/gc/GCData.hpp"
#include <algorithm>

namespace shaka {

namespace gc {
GCNode::GCNode() :
    gc_data(nullptr) {}

GCNode::GCNode(GCData * data) {
  gc_data = data;
}

GCNode::GCNode(const GCNode& other) : gc_data(other.gc_data) {}

GCNode::GCNode(GCNode&& other) : gc_data(other.gc_data) {
  other.gc_data = nullptr;
}

GCNode::~GCNode() {}

void swap(GCNode& lhs, GCNode& rhs) {
  std::swap(lhs.gc_data, rhs.gc_data);
}

GCNode& GCNode::operator=(GCNode other) {
  swap(*this, other);
}

Data& GCNode::operator*() const {
  return this->gc_data->get_data();
}

Data * GCNode::operator->() const {
  return this->gc_data->get_data_address();
}

Data * GCNode::get() const {
  return this->gc_data->get_data_address();
}

GCNode::operator bool() const {
  return this->gc_data != nullptr;
}

bool operator==(const GCNode& lhs, const GCNode& rhs) {
  return lhs.gc_data == rhs.gc_data;
}

bool operator!=(const GCNode& lhs, const GCNode& rhs) {
  return !operator==(lhs, rhs);
}

} //namespace gc
} //namespace shaka
