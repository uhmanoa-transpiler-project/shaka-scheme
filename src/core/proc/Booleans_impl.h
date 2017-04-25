#ifndef SHAKA_STDPROC_BOOLEANS_IMPL_H
#define SHAKA_STDPROC_BOOLEANS_IMPL_H

#include "core/base/Number.h"
#include "core/base/Boolean.h"
#include "core/base/DataNode.h"
#include "core/base/Data.h"

#include "core/base/Environment.h"
#include <functional>
#include <typeinfo>
#include <vector>

using NodePtrs = std::shared_ptr<shaka::DataNode>;
using Args = std::vector<NodePtrs>;
using Function = std::function<Args(Args, EnvPtr)>;

// (not obj)
Args nots(Args v, EnvPtr e){
    //get data from each vector and see if false
    std::vector<NodePtrs> res;

    for(int i = 0; i < v.size(); i++){
        if (v[i]->get_data() == false) res.push_back(true);
        else{ return res.push_back(false);} 
    }
    return res;
}
// (boolean? obj)
Args isboolean(Args v, EnvPtr e){
    std::vector<NodePtrs> res;
    //check if data is boolean
    for(int i = 0; i < v.size(); i++){
        if(v[i]->is_boolean()){
            res.push_back(true);
        }
        else{res.push_back(false)}
    }
    return res;
}
#endif // SHAKA_STDPROC_BOOLEANS_IMPL_H
