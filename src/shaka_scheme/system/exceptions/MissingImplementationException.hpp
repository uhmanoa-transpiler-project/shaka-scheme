//
// Created by aytas on 9/8/2017.
//

#ifndef SHAKA_SCHEME_MISSINGIMPLEMENTATIONEXCEPTION_HPP
#define SHAKA_SCHEME_MISSINGIMPLEMENTATIONEXCEPTION_HPP

#include "shaka_scheme/system/exceptions/BaseException.hpp"

namespace shaka {

class MissingImplementationException : public BaseException {
public:
  MissingImplementationException(
      size_t exception_id,
      const std::string& message) :
      BaseException(
          exception_id,
          std::string("Missing Implementation: " + message)) {}

};

} // namespace shaka

#endif //SHAKA_SCHEME_MISSINGIMPLEMENTATIONEXCEPTION_HPP
