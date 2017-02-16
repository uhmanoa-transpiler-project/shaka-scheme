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

using Impl_IEnvironment =
    IEnvironment<std::string, std::shared_ptr<DataTree>>;


class Environment : public Impl_IEnvironment {
public:

    Environment(std::weak_ptr<IEnvironment> parent) :
        parent(parent) {}

    virtual ~Environment() override {}

    virtual std::weak_ptr<IEnvironment> get_parent() override {
        return this->parent;
    }
   
    /// @todo Decide whether this should be virtual or not.
    void set_parent(std::weak_ptr<IEnvironment> e) {
        parent = e;
    }

    virtual void set_value(const std::string& key, std::shared_ptr<DataTree> data) override {
        local[key]=data;
    }

    virtual std::shared_ptr<DataTree> get_value(const std::string& key) override {
        if (local.find(key)!= local.end()){
            return local[key];
        }
        else if (this->parent == nullptr){
            return nullptr;
        } 
        else {
            return this->parent->get_value(key);
        }
    }

    virtual bool contains(const std::string& key) {
        return local.find(key) != local.end();
    }

    virtual std::vector<std::string> get_keys() override {
        std::vector<std::string> v;
        v.reserve(local.size());
        for (auto it : local) {
            v.push_back(it.first);
        }
        return v;
    }

private:
    std::weak_ptr<IEnvironment> parent;
    std::map<std::string, std::shared_ptr<DataTree>> local;

};

} // namespace shaka
   
#endif // SHAKA_ENVIRONMENT_H
