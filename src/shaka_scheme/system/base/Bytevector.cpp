#include "shaka_scheme/system/base/Bytevector.hpp"

#include "shaka_scheme/system/exceptions/IndexOutOfBoundsException.hpp"

#include <cctype>
#include <cstring>
#include <utility>

namespace shaka {

Bytevector::Bytevector(std::size_t k) :
    arr(new unsigned char[k]),
    size(k) {}


Bytevector::Bytevector(std::size_t k, unsigned char byte) :
    arr(new unsigned char[k]),
    size(k) {
  for (std::size_t i = 0; i < k; ++i) {
    this->arr[i] = byte;
  }
}

Bytevector::Bytevector(std::initializer_list<unsigned char> l) :
    arr(new unsigned char[l.size()]),
    size(l.size()) {
  std::size_t i = 0;
  for (const auto& it : l) {
    this->arr[i] = it;
    ++i;
  }
}

Bytevector::Bytevector(const Bytevector& other) :
    arr(new unsigned char[other.length()]),
    size(other.length()) {
  std::memcpy(this->arr, other.arr, sizeof(unsigned char)*other.length());
}

Bytevector::Bytevector(Bytevector&& other) :
    arr(std::move(other.arr)),
    size(std::move(other.size)) {
  other.arr = nullptr;
  other.size = 0;
}

Bytevector::~Bytevector() {
  delete arr;
}

std::size_t Bytevector::length() const {
  return this->size;
}

unsigned char& Bytevector::operator[](std::size_t k) {
  if (k >= size) {
    throw IndexOutOfBoundsException(1, "Bytevector: index is out of bounds");
  }
  return this->arr[k];
}

Bytevector& Bytevector::operator=(Bytevector other) {
  swap(*this, other);
  return *this;
}

void swap(Bytevector& lhs, Bytevector& rhs) {
  using std::swap;

  swap(lhs.arr, rhs.arr);
  swap(lhs.size, rhs.size);
}

} // namespace shaka
