#ifndef SHAKA_ENVIRONMENT_H
#define SHAKA_ENVIRONMENT_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <memory>

#include "IEnvironment.h"
#include "DataNode.h"

namespace shaka {

using DataTree =
    DataNode<Data>;

/// @note Value needs to be a pointer type.
template <typename Key, typename Value>
class Environment : public IEnvironment<Key, Value> {
public:

    Environment(IEnvironment<Key, Value>* parent) :
        parent(parent) {}

    virtual ~Environment() override {}

    virtual IEnvironment<Key, Value>* get_parent() override {
        return this->parent;
    }
   
    /// @todo Decide whether this should be virtual or not.
    void set_parent(IEnvironment<Key,Value>* e) {
        parent = e;
    }

    virtual void set_value(const Key& key, Value data) override {
        local[key]=data;
    }

    virtual Value get_value(const Key& key) override {

        /* Check if the key exists in local */
        if (local.find(key)!= local.end()){
            return local[key];
        }
        /* Returns null if does not exist and doesn't have a parent */
        else if (this->parent == nullptr){
            return nullptr;

        } 
        /* Looks for key in the parent environment */
        else {
            return this->parent->get_value(key);
        }
    }

    virtual bool contains(const Key& key) {
        return local.find(key) != local.end();
    }

    virtual std::vector<Key> get_keys() override {
        std::vector<Key> v;
        v.reserve(local.size());
        for (auto it : local) {
            v.push_back(it.first);
        }
        return v;
    }

private:
    IEnvironment<Key, Value>* parent;
    std::map<Key, Value> local;

};

} // namespace shaka
   
#endif // SHAKA_ENVIRONMENT_H
