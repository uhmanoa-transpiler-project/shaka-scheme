
#include <iostream>
#include <vector>
#include <functional>
#include "DataNode.h"
#include "IDataNode.h"
#include "parser/primitives.h"
#include "parser/char_rules.h"

namespace shaka {
namespace parser {
namespace rule {

//using InputStream = std::istream;
//using NodePtr = std::shared_ptr<shaka::IDataNode<shaka::Data>>;

template <typename T>
bool rules_or(std::vector<std::function<bool(InputStream&, NodePtr,T&)>> rules,
              InputStream& in,
              NodePtr      root,
              T&           interm){
    for(auto f : rules){
        if(f(in, root, interm)) return true;
    }
    return false;
}

template <typename T>
bool firstRule(InputStream& in, NodePtr root, T& interm){
    bool accept = false;

    std::vector<std::function<bool(InputStream&, NodePtr, T&)>> rules;
    rules.push_back(digit);
    rules.push_back(alpha);
    rules.push_back(match_char<std::string, '.'>);
    rules.push_back(match_char<std::string, '-'>);
    rules.push_back(match_char<std::string, '_'>);

    while(rules_or(rules, in, root, interm)){
        accept = true;
    }
    return accept;
}

template <typename T>
bool parseEmailAddr(InputStream& in, NodePtr root, T& interm){
    bool accept = false;
    bool set2 = false;
    bool set3 = false;
    bool set4 = false;
    int count = 0;
    if(firstRule(in, root, interm)) set2 = match_char<std::string, '@'>(in, root, interm);
    if(set2) set3 = alpha(in, root, interm);
    if(set3) set4 = match_char<std::string, '.'>(in, root, interm);
    if(set4){
        while(count < 3) alpha(in, root, interm);
        accept = (count == 2 && count == 3) ? true : false;
    }
    return accept;
}


}
}
}

int main(){

    std::string builder;
    std::cout << shaka::parser::rule::parseEmailAddr(std::cin, NULL, builder) << std::endl;
    return 0;
}
