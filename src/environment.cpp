#include<stdlib.h>
#include<stdio.h>
#include <iostream>
#include <map>

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
    void define(char key, int data){
        local[key]=data;
    };
    char* find(char key){
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
    std::map<char, char> local;

};
int main() {
    
	return 0;
}   