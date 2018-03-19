#ifndef SHAKA_SCHEME_CORE_BASE_VECTOR_HPP
#define SHAKA_SCHEME_CORE_BASE_VECTOR_HPP

#include "shaka_scheme/system/base/Data.hpp"

#include <initializer_list>
#include <cctype>


namespace shaka {

class Vector {
  NodePtr* arr;
  std::size_t size;
public:
  /**
   * @brief Constructs a fixed-size vector of size k.
   * @param k The number of elements in the vector.
   */
  Vector(std::size_t k);

  /**
   * @brief Constructs a vector of fixed-size where each element is the same.
   * @param k The number of elements in the vector.
   * @param fill The object to put into every element in the vector.
   */
  Vector(std::size_t k, NodePtr fill);

  /**
   * @brief Creates a vector from a list of objects.
   * @param l The brace-initialized list of objects to construct from.
   */
  Vector(std::initializer_list<NodePtr> l);

  /**
   * @brief Copy constructor for Vector.
   * @param other The other Vector to copy from.
   */
  Vector(const Vector& other);

  /**
   * @brief Move constructor for Vector.
   * @param other The other Vector to move resources from.
   */
  Vector(Vector&& other);

  /**
   * @brief Destroys the Vector's internal array.
   */
  ~Vector();

  /**
   * @brief Gets the length of the vector.
   * @return The length of the vector.
   */
  std::size_t length() const;

  /**
   * @brief Gets a mutable-reference to an element in the vector.
   * @param k The index of the element to access.
   * @throws IndexOutOfBoundsException upon providing an invalid k >= size.
   * @return A mutable reference to the element in the vector.
   */
  NodePtr& operator[](std::size_t k);

  /**
   * @brief Assignment operator for Vector. Uses copy-and-swap idiom.
   * @param other The other object to assign from.
   * @return A reference to this object.
   */
  Vector& operator=(Vector other);

  /**
   * @brief Swaps the contents of this and the other Vector.
   */
  friend void swap(Vector& lhs, Vector& rhs);
};

} // namespace shaka

#endif // SHAKA_SCHEME_CORE_BASE_VECTOR_HPP
