//
// Created by aytas on 11/8/2017.
//

#ifndef SHAKA_SCHEME_PRIMITIVEFORMMARKER_HPP
#define SHAKA_SCHEME_PRIMITIVEFORMMARKER_HPP

#include <string>

namespace shaka {

class PrimitiveFormMarker {
public:
  PrimitiveFormMarker(std::string str);

  PrimitiveFormMarker(const PrimitiveFormMarker& other);

  PrimitiveFormMarker(PrimitiveFormMarker&& other);

  PrimitiveFormMarker& operator=(PrimitiveFormMarker other);

  friend void swap(PrimitiveFormMarker& left, PrimitiveFormMarker& right);
  friend bool operator==(
      const PrimitiveFormMarker& left,
      const PrimitiveFormMarker& right);
  friend bool operator!=(
      const PrimitiveFormMarker& left,
      const PrimitiveFormMarker& right);
  friend std::ostream& operator<< (
      std::ostream& left,
      const PrimitiveFormMarker& right);

  std::string get();
private:
  std::string str;
};

std::ostream& operator<< (std::ostream& left, const PrimitiveFormMarker& right);

bool operator==(
    const PrimitiveFormMarker& left,
    const PrimitiveFormMarker& right);
bool operator!=(
    const PrimitiveFormMarker& left,
    const PrimitiveFormMarker& right);

} // namespace shaka

#endif //SHAKA_SCHEME_PRIMITIVEFORMMARKER_HPP
