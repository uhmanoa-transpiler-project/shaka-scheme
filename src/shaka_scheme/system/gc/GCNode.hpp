//
// Created by mortrax on 2/5/18.
//

#ifndef SHAKA_SCHEME_GCNODE_HPP
#define SHAKA_SCHEME_GCNODE_HPP

#include "mark_procedures.hpp"

namespace shaka {
class Data;

namespace gc {
class GCData;
/**
 * @brief Defines the type of GCNode, the object which will
 * wrap over GCData, providing a managed interface to Data
 */
class GCNode {
public:

  GCNode();
  GCNode(GCData * data);
  GCNode(const GCNode& other);
  GCNode(GCNode&& other);
  ~GCNode();

  Data& operator*() const;
  Data * operator->() const;

  Data * get() const;
  operator bool() const;

  GCNode& operator=(GCNode other);

  friend bool operator==(const GCNode& lhs, const GCNode& rhs);
  friend bool operator!=(const GCNode& lhs, const GCNode& rhs);

  friend void mark_node(const GCNode& node);
  friend void swap(GCNode& lhs, GCNode& rhs);

private:
  GCData * gc_data;
};

} // namespace gc
} // namespace shaka

#endif //SHAKA_SCHEME_GCNODE_HPP
