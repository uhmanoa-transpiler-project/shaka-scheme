#ifndef SHAKA_SCHEME_INVALIDINPUTEXCEPTION_HPP
#define SHAKA_SCHEME_INVALIDINPUTEXCEPTION_HPP

#include "shaka_scheme/system/exceptions/BaseException.hpp"

namespace shaka {

/**
 * @brief Represents invalid input exceptions at runtime.
 *
 * Used in classes such as Environment.
 */
class InvalidInputException : public shaka::BaseException {
public:
  /**
   * @brief Initializes the BaseException.
   * @param exception_id The unique exception type id.
   * @param message The error message.
   */
  InvalidInputException(std::size_t exception_id,
                        std::string message) :
      shaka::BaseException(exception_id, message) {}

};

}
#endif //SHAKA_SCHEME_INVALIDINPUTEXCEPTION_HPP
