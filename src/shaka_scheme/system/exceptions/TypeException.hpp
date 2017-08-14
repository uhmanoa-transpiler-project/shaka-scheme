//
// Created by aytas on 8/6/2017.
//

#ifndef SHAKA_SCHEME_TYPEEXCEPTION_HPP
#define SHAKA_SCHEME_TYPEEXCEPTION_HPP

#include <shaka_scheme/system/exceptions/BaseException.hpp>

namespace shaka {

class TypeException : public BaseException {
public:
  TypeException(std::size_t exception_id,
                std::string message) :
      BaseException(exception_id, message) {}
};

}

#endif //SHAKA_SCHEME_TYPEEXCEPTION_HPP
