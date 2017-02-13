#include<stdlib.h>
#include<stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <memory>

#include "DataNode.h"
namespace shaka {

class Environment {
    public:
    Environment(){    
        parent = nullptr;
    };
    Environment(Environment* par){
        parent = par;
    };
    ~Environment(){};

    Environment* getParentPtr(){
        return parent;
    }

    void setParent(Environment* e){
        parent = e;
    };

    void define(std::string key, char data){
        local[key]=data;
    };

    char* find(std::string key){
        if(local.find(key)!= local.end()){
            return &local[key];
        }
        else if(this->parent == nullptr){
            return NULL;
        } 
        else {
            return (this->parent)->find(key);
        }
    }

    private:
    Environment* parent;
    std::map<std::string, char> local;

};

} // namespace shaka
   
