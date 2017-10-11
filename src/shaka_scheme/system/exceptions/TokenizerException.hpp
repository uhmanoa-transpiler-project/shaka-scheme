//
// Created by LOS on 10/10/2017.
//

#ifndef SHAKA_SCHEME_TOKENIZEREXCEPTION_HPP
#define SHAKA_SCHEME_TOKENIZEREXCEPTION_HPP

#include "shaka_scheme/system/exceptions/BaseException.hpp"
#include <string>

namespace shaka {

/**
 * @brief Represents exceptions from the Tokenizer.
 */
class TokenizerException : public BaseException {
public:
  TokenizerException(
      std::size_t exception_id,
      const std::string& message) :
      BaseException(
          exception_id,
          std::string("Tokenizer: ") + message) {}
};

} // namespace shaka

#endif //SHAKA_SCHEME_TOKENIZEREXCEPTION_HPP
