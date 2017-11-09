//
// Created by aytas on 11/8/2017.
//

#include "shaka_scheme/system/base/PrimitiveFormMarker.hpp"

namespace shaka {

PrimitiveFormMarker::PrimitiveFormMarker(std::string str) :
    str(str) {}

PrimitiveFormMarker::PrimitiveFormMarker(const PrimitiveFormMarker& other) :
    str(other.str) {}

PrimitiveFormMarker::PrimitiveFormMarker(PrimitiveFormMarker&& other) :
    str(std::move(other.str)) {}

PrimitiveFormMarker& PrimitiveFormMarker::operator=(PrimitiveFormMarker other) {
  PrimitiveFormMarker temp(other);
  swap(*this, temp);
  return *this;
}

void swap(PrimitiveFormMarker& left, PrimitiveFormMarker& right) {
  using std::swap;

  swap(left.str, right.str);
}

std::string PrimitiveFormMarker::get() {
  return str;
}

std::ostream& operator<< (
    std::ostream& left,
    const PrimitiveFormMarker& right) {
  left << std::string("#<procedure:|") << right.str << std::string("|>");
  return left;
}

bool operator==(
    const PrimitiveFormMarker& left,
    const PrimitiveFormMarker& right) {
  return left.str == right.str;
}

bool operator!=(
    const PrimitiveFormMarker& left,
    const PrimitiveFormMarker& right) {
  return ! operator==(left, right);
}

} // namespace shaka
