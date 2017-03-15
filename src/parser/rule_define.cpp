#include <iostream>
#include "parser/rule_define.h"



int main(){

    bool result;
    std::string read;

    result = shaka::parser::rule::define(std::cin, NULL, read);
    std::cout << "\nRESULT: " << result << std::endl;
    if(result) std::cout << read << std::endl;
    return 0;
}



