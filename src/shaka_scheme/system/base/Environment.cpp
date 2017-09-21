//
// Created by dylan on 9/18/17.
//

#include "Environment.hpp"

namespace shaka {
using Key = shaka::Symbol;
using Value = NodePtr;

Environment::Environment(std::shared_ptr<IEnvironment<Key, Value>> parent) :
    parent(parent) {}

Environment::~Environment() {}

std::shared_ptr<IEnvironment<Key, Value>> Environment::get_parent() {
  return this->parent;
}

void Environment::set_parent(std::shared_ptr<IEnvironment<Key, Value>> e) {
  parent = e;
}

void Environment::set_value(const Key& key, Value data) {
  local[key] = data;
}

Value Environment::get_value(const Key& key) {

  /* Check if the key exists in local */
  if (local.find(key) != local.end()) {
    return local[key];
  }
    /* Returns null if it does not exist and doesn't have a parent */
  else if (this->parent == nullptr) {
    throw std::runtime_error(
        "Environment.get_value: key does not have an assigned value");
  }
    /* Look for key in the parent environment */
  else {
    return this->parent->get_value(key);
  }
}

bool Environment::contains(const Key& key) {
  return local.find(key) != local.end();
}

bool Environment::is_defined(const Key& key) {
  if (local.find(key) != local.end()) {
    return true;
  } else if (this->parent != nullptr) {
    return this->parent->is_defined(key);
  } else {
    return false;
  }
}

std::vector<Key> Environment::get_keys() {
  std::vector<Key> v;
  v.reserve(local.size());
  for (auto it: local) {
    v.push_back(it.first);
  }
  return v;
}

const std::map<Key, Value>& Environment::get_bindings() const {
  return local;
}

bool operator==(const Environment& lhs, const Environment& rhs) {
  return lhs.local == rhs.local && lhs.parent == rhs.parent;
}

bool operator!=(const Environment& lhs, const Environment& rhs) {
  return !operator==(lhs, rhs);
}
}