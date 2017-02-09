#include<stdlib.h>
#include<stdio.h>
#include <iostream>
#include <map>
#include <string>

class Environment {
    public:
    Environment(){    
        parent = NULL;
    };
    //constructor
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

    void define(std::string key, int data){
        local[key]=data;
    };

    char* find(std::string key){
        if(local.find(key)!= local.end()){
            // std::cout<< "local  "<<&local[key]<<std::endl;
            return &local[key];
        }
        else if(this->parent == NULL){
            std::cout<<"not found"<<std::endl;
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
   
