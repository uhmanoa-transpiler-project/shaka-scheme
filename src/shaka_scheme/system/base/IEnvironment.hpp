//
// Created by aytas on 8/5/2017.
//

#ifndef SHAKA_SCHEME_IENVIRONMENT_HPP
#define SHAKA_SCHEME_IENVIRONMENT_HPP

#include <memory>
#include <utility>
#include <vector>

namespace shaka {

/**
 * @brief The interface for the environment type. Holds variable bindings.
 * @tparam Key The key type. Should be comparable and equality comparable.
 * @tparam Value The value type.
 */
template<typename Key, typename Value>
class IEnvironment {
public:
  virtual ~IEnvironment() {}

  /**
   * @brief Gets the pointer to the parent environment.
   * @return The pointer to the parent environment.
   */
  virtual std::shared_ptr<IEnvironment<Key, Value>>
  get_parent() = 0;

  /**
   * @brief Returns whether a key has an associated value in the environment.
   * @param key The key to lookup in the environment.
   * @return Whether this environment or its parents contain the key.
   */
  virtual bool
  contains(const Key& key) = 0;

  /**
   * @brief Returns whether a key definition is directly contained in the
   * environment.
   * @param key The key to look for in this and parent environment.
   * @return Whether the key is defined.
   */
  virtual bool
  is_defined(const Key& key) = 0;

  /**
   * @brief Returns a reference to the value refered
   * to by the key. Note that the key must exist,
   * otherwise, it throws a shaka::InvalidInputException.
   * @param key The key to lookup and return the value for.
   * @return The value associated with the given key.
   */
  virtual Value
  get_value(const Key& key) = 0;

  /// @brief Sets an element in the Environment referred to be the `key`
  ///        and then sets its value to `value`.
  virtual void
  set_value(const Key& key,
            Value value) = 0;

  /// @brief Returns a list of all the keys in the Environment.
  virtual std::vector<Key>
  get_keys() = 0;

};

}
#endif //SHAKA_SCHEME_IENVIRONMENT_HPP
