#ifndef SHAKA_SCHEME_BASEEXCEPTION_HPP
#define SHAKA_SCHEME_BASEEXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace shaka {
/**
 * @brief The class to serve as the base for exception types within Shaka
 * Scheme.
 */
class BaseException : public std::exception {
  /**
   * @brief The exception id. This should be unique and recorded in a table
   * somewhere to aid with future error diagnosis.
   */
  const std::size_t id;

  /**
   * @brief The exception error message.
   */
  const std::string message;

public:
  /**
   * @brief The constructor for the BaseException.
   * @param exception_id The unique excepiton id number.
   * @param message The associated error message for the exception.
   */
  BaseException(std::size_t exception_id,
                std::string message) :
      id(exception_id),
      message(message) {}
  /**
   * @brief Returns the error message.
   * @return The error message string.
   */
  const char *
  what() const noexcept {
    return message.c_str();
  }

  /**
   * @brief Returns the exception id.
   * @return The exception id.
   */
  std::size_t
  get_id() const noexcept {
    return id;
  }
};

} // namespace shaka

#endif //SHAKA_SCHEME_BASEEXCEPTION_HPP
