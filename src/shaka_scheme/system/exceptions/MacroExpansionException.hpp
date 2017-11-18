#ifndef SHAKA_SCHEME_MACROEXPANSIONEXCEPTION_HPP_
#define SHAKA_SCHEME_MACROEXPANSIONEXCEPTION_HPP_

#include "shaka_scheme/system/exceptions/BaseException.hpp"

namespace shaka {

/**
 * @brief Represents macro expansion exceptions at macro expansion time.
 *
 * Used in the MacroContextChecker and macro expansion process.
 */
class MacroExpansionException : public shaka::BaseException {
public:
  /**
   * @brief Initializes the BaseException.
   * @param exception_id The unique exception type id.
   * @param message The error message.
   */
  MacroExpansionException(std::size_t exception_id,
                        std::string message) :
      shaka::BaseException(exception_id, message) {}
};

}
#endif //SHAKA_SCHEME_MACROEXPANSIONEXCEPTION_HPP
