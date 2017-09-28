//
// Created by dylan on 9/18/17.
//

#ifndef SHAKA_SCHEME_ENVIRONMENT_H
#define SHAKA_SCHEME_ENVIRONMENT_H

#include <map>
#include "shaka_scheme/system/base/IEnvironment.hpp"
#include "shaka_scheme/system/base/DataPair.hpp"
#include "shaka_scheme/system/base/Symbol.hpp"

namespace shaka {
/**
 * @brief Representation for a Scheme Environment
 */
class Environment : public IEnvironment<shaka::Symbol, NodePtr> {

public:
  using Key = shaka::Symbol;
  using Value = NodePtr;

  /**
  * @brief Constructor for Environment
  * @param parent Pointer to Parent Environment, nullptr if top environment
  */
  Environment(std::shared_ptr<IEnvironment<Key, Value>> parent);

  /**
   * @brief Destroys Environment
   */
  ~Environment() override;

  /**
   * @brief Gets pointer to the parent environment
   * @return The pointer to the parent environment
   */

  std::shared_ptr<IEnvironment<Key, Value>> get_parent() override;

  /**
   * @brief Sets the Parent Environment to 'e'
   * @param e Pointer to an Environment
   */
  void set_parent(std::shared_ptr<IEnvironment<Key, Value>> e);

  /**
   * @brief Sets an element in the Environment referred to by the 'key'
   *        and sets its value to 'data'
   * @param key They key to be used for lookup in the environment
   * @param data The data associated with the key
   */
  void set_value(const Key& key, Value data) override;

  /**
   * @brief Returns a reference to the value referred to by the key. Key
   *        must exist, otherwise, it throws a runtime error.
   * @param key The key to lookup and return the value for.
   * @return The value associated with the given key
   * @throws InvalidInputException when the key does not exist in the
   *         environment bindings
   */
  Value get_value(const Key& key) override;

  /**
   * @brief Returns whether a key has an associated value in the environment.
   * @param key The key to lookup in the environment
   * @return Whether this environment contains the key.
   */
  bool contains(const Key& key) override;

  /**
   * @brief Returns whether a key definition is directly contained in
   *        the environment.
   * @param key The key to look for in this and parent environment.
   * @return Whether the key is defined
   */
  bool is_defined(const Key& key) override;

  /**
   * @brief Returns a list of all the keys in the Environment.
   * @return List of keys
   */
  std::vector<Key> get_keys() override;

  /**
   * @brief Returns all bindings in the Environment.
   * @return Bindings for current Environment.
   */
  const std::map<Key, Value>& get_bindings() const;

  friend bool operator==(const shaka::Environment&, const shaka::Environment&);

  friend bool operator!=(const shaka::Environment&, const shaka::Environment&);

private:
  std::shared_ptr<IEnvironment<Key, Value>> parent;
  std::map<Key, Value> local;
};

} //namespace shaka


#endif //SHAKA_SCHEME_ENVIRONMENT_H
