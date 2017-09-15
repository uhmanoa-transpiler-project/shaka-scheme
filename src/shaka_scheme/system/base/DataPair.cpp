//
// Created by aytas on 9/3/2017.
//

#include "shaka_scheme/system/base/DataPair.hpp"
#include "shaka_scheme/system/base/Data.hpp"

namespace shaka {

NodePtr create_node(Data data) {
  return std::make_shared<Data>(data);
}

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
