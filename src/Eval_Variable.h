#ifndef SHAKA_Eval_Variable_H
#define SHAKA_Eval_Variable_H

#include <memory>
#include <utility>
#include <vector>
#include "Symbol.h"
#include "IEnvironment.h"

namespace shaka {

template <typename T, typename Key, typename Value>
class Eval_Variable : public shaka::IEvaluatorStrategy<T, Key, Value> {


    T find_variable(Symbol find_this_one, std::shared_ptr<IEnvironment<Key, Value>> env ){

        std::vector<Key> all_keys = env->get_keys();

        for(int i = 0; i < all_keys.size(); i++ )
            if(find_this_one == all_keys[i]){

                return all_keys[i]->get_Value();
            }


    }

};


}

#endif // SHAKA_Eval_Variable_H
