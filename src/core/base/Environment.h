#ifndef SHAKA_ENVIRONMENT_H
#define SHAKA_ENVIRONMENT_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <memory>

#include "core/base/IEnvironment.h"
#include "core/base/DataNode.h"

namespace shaka {

/// @note Value needs to be a pointer type.

class Environment : public IEnvironment<shaka::Symbol, shaka::Data> {
public:
    using Key = shaka::Symbol;
    using Value = shaka::Data;

    Environment(std::shared_ptr<IEnvironment<Key, Value>> parent) :
        parent(parent) {}

    virtual ~Environment() override {}

    virtual std::shared_ptr<IEnvironment<Key, Value>> get_parent() override {
        return this->parent;
    }
   
    /// @todo Decide whether this should be virtual or not.
    void set_parent(std::shared_ptr<IEnvironment<Key,Value>> e) {
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
        else if (this->parent == nullptr) {
            throw std::runtime_error("Environment.get_value: key does not have an assigned value");
            return std::make_shared<DataNode>(NodePtr{nullptr});
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

    const std::map<Key, Value>& get_bindings() const {
        return local;
    }

    void print_bindings(std::ostream& out) {
        out << "{";
        for (const auto& it : local) {
           out << " {" << it.first << " : " << it.second << "}";
        }
        out << " } \n";
    }

    friend bool operator== (const shaka::Environment&, const shaka::Environment&);
    friend bool operator!= (const shaka::Environment&, const shaka::Environment&);
    friend std::ostream& operator<< (std::ostream&, const shaka::Environment&);
private:
    std::shared_ptr<IEnvironment<Key, Value>> parent;
    std::map<Key, Value> local;
};

bool operator== (const shaka::Environment& lhs, const shaka::Environment& rhs) {
    return lhs.local == rhs.local && lhs.parent == rhs.parent;
}

bool operator!= (const shaka::Environment& lhs, const shaka::Environment& rhs) {
    return !operator==(lhs, rhs);
}

std::ostream& operator<< (std::ostream& lhs, const shaka::Environment& rhs) {
    // Turning off rhs unused warning
    static_cast<void>(rhs);
    lhs << "#<environment>";
    return lhs;
}

} // namespace shaka
   
#endif // SHAKA_ENVIRONMENT_H
