#ifndef SHAKA_SCHEME_INDEXOUTOFBOUNDSEXCEPTION_HPP
#define SHAKA_SCHEME_INDEXOUTOFBOUNDSEXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace shaka {
/**
 * @brief Thrown when accessing a container with an invalid index outside of
 * its usual range.
 */
class IndexOutOfBoundsException : public std::exception {
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
   * @brief The constructor for the IndexOutOfBoundsException.
   * @param exception_id The unique excepiton id number.
   * @param message The associated error message for the exception.
   */
  IndexOutOfBoundsException(std::size_t exception_id,
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

#endif //SHAKA_SCHEME_INDEXOUTOFBOUNDS_HPP
