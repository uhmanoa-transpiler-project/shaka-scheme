#ifndef SHAKA_CORE_BASE_BYTEVECTOR_HPP
#define SHAKA_CORE_BASE_BYTEVECTOR_HPP

#include <shaka_scheme/system/gc/GCNode.hpp>

#include <initializer_list>
#include <cctype>
#include <memory>

namespace shaka {

class Data;

//using NodePtr = std::shared_ptr<Data>;
using NodePtr = gc::GCNode;

/**
 * @brief Represents a Scheme bytevector, a vector which holds only bytes.
 *
 * @todo Figure out the correct memory allocator for this object.
 */
class Bytevector {
  /**
   * @brief The raw pointer to an array of unsigned char, the bytes underneath.
   */
  unsigned char* arr;

  /**
   * @brief The fixed size of the bytevector, in bytes.
   */
  std::size_t size;
public:

  /**
   * @brief Constructs a bytevector with k byte elements.
   * @param k The number of elements that the bytevector will have.
   */
  Bytevector(std::size_t k);

  /**
   * @brief Constructs a bytevector with k elements, all with the value of byte.
   * @param k The number of elements.
   * @param byte The unsigned byte value to initialize to.
   */
  Bytevector(std::size_t k, unsigned char byte);

  /**
   * @brief Constructs a bytevector with an intiialization list of unsigned
   * chars.
   * @param l The brace-initialization list of chars to initialize with.
   */
  Bytevector(std::initializer_list<unsigned char> l);

  /**
   * @brief Copy constructor for Bytevector.
   * @param other The Bytevector to copy values over from.
   */
  Bytevector(const Bytevector& other);

  /**
   * @brief Move constructor for Bytevector.
   * @param other The Bytevector to move values from.
   *
   * The moved-from object has its array to set to nullptr and its size set
   * to 0.
   */
  Bytevector(Bytevector&& other);

  /**
   * @brief Destroys the Bytevector.
   */
  ~Bytevector();

  /**
   * @brief Gets the length of the bytevector.
   * @return The length of the bytevector.
   */
  std::size_t length() const;

  /**
   * @brief Gets a mutable reference for an element in the bytevector.
   * @param k The index of the element to get.
   * @throws IndexOutOfBoundsException upon providing an invalid k >= size.
   * @return A const-reference to the element.
   */
  unsigned char& operator[](std::size_t k);

  /**
   * @brief Copy/move assignment for Bytevector. Uses copy-and-swap idiom.
   * @param other The other Bytevector to get values from.
   * @return A reference to this object.
   */
  Bytevector& operator=(Bytevector other);

  /**
   * @brief Swaps the contents of two Vectors.
   * @param lhs The left-hand side Vector.
   * @param rhs The right-hand side Vector.
   */
  friend void swap(Bytevector& lhs, Bytevector& rhs);
};

} // namespace shaka

#endif // SHAKA_CORE_BASE_BYTEVECTOR_HPP
