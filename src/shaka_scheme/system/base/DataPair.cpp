//
// Created by aytas on 9/3/2017.
//

#include "shaka_scheme/system/base/DataPair.hpp"
#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/gc/GCNode.hpp"
#include "shaka_scheme/system/gc/GC.hpp"
#include "shaka_scheme/system/gc/init_gc.hpp"

namespace shaka {

std::shared_ptr<Data> create_node_shared_ptr(const Data& data) {
  return std::make_shared<Data>(data);
}

std::function<gc::GCNode(const Data&)> create_node;
/* =
    [](const Data& data) {
      return create_node_shared_ptr(data);
    };
*/

void swap (shaka::DataPair& lhs, shaka::DataPair& rhs) {
  using std::swap;

  swap(lhs.left, rhs.left);
  swap(lhs.right, rhs.right);
}

} // namespace shska

shaka::DataPair::DataPair() :
  left(create_node(Data())),
  right(create_node(Data())) {}

shaka::DataPair::DataPair(Data data) :
    left(create_node(data)),
    right(create_node(Data())) {}

shaka::DataPair::DataPair(Data left_data, Data right_data) :
  left(create_node(left_data)),
  right(create_node(right_data)) {}

shaka::DataPair::DataPair(NodePtr node) :
  left(node),
  right(create_node(Data())) {}

shaka::DataPair::DataPair(NodePtr left_node, NodePtr right_node) :
  left(left_node),
  right(right_node) {}

shaka::DataPair::DataPair(const DataPair& other) :
  left(create_node(*other.left)),
  right(create_node(*other.right)) {}

shaka::DataPair::DataPair(DataPair&& other) :
  left(std::move(other.left)),
  right(std::move(other.right)) {}

shaka::DataPair& shaka::DataPair::operator= (shaka::DataPair other) {
  shaka::DataPair temp(other);
  swap(*this, temp);

  return *this;
}
