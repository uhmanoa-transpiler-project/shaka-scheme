#include "shaka_scheme/system/base/Vector.hpp"

#include "shaka_scheme/system/exceptions/IndexOutOfBoundsException.hpp"

// I included this so I can create unspecified values
#include "shaka_scheme/system/core/types.hpp"

#include <cstring>

namespace shaka {

Vector::Vector(std::size_t k) :
    arr(new shaka::NodePtr[k]),
    size(k) {
  // Initialize all of the NodePtr to unspecified value
  for (std::size_t i = 0; i < k; ++i) {
    this->arr[i] = core::create_unspecified_node();
  }
}

Vector::Vector(std::size_t k, NodePtr fill) :
    arr(new NodePtr[k]),
    size(k) {
  // Initialize all of the nodes to a copy of the NodePtr value.
  for (std::size_t i = 0; i < k; ++i) {
    this->arr[i] = create_node(*fill);
  }
}

Vector::Vector(std::initializer_list<NodePtr> l) :
    arr(new NodePtr[l.size()]),
    size(l.size()) {
  // For each NodePtr in the initializer list,
  // copy the value into the vector
  std::size_t i = 0;
  for (const auto& it : l) {
    this->arr[i] = create_node(*it);
    ++i;
  }
}
Vector::Vector(const Vector& other) :
    arr(new NodePtr[other.length()]),
    size(other.length()) {
  // Copy each of the elements from the other vector into this one.
  for (std::size_t i = 0; i < size; ++i) {
    this->arr[i] = create_node(*other.arr[i]);
  }
}

Vector::Vector(Vector&& other) :
    arr(std::move(other.arr)),
    size(std::move(other.size)) {
  other.arr = nullptr;
  other.size = 0;
}

Vector::~Vector() {
  delete[] arr;
}

std::size_t Vector::length() const {
  return this->size;
}

NodePtr& Vector::operator[](std::size_t k) {
  if (k >= size) {
    throw IndexOutOfBoundsException(1, "Vector: index is out of bounds");
  }
  return this->arr[k];
}

Vector& Vector::operator=(Vector other) {
  swap(*this, other);
  return *this;
}

void swap(Vector& lhs, Vector& rhs) {
  using std::swap;

  swap(lhs.arr, rhs.arr);
  swap(lhs.size, rhs.size);
}

} // namespace shaka
