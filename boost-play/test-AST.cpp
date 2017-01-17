#include <iostream>

#include "AST.h"

int main() {
    ASTNode root(MetaTag::LIST);

    root.insert(1);
    root.insert(std::string("Hello world!"));

    root.insert(std::string("Bye world!"));

    root.insert(2);

    root.insert(2.9912312);

    auto child = root.insert(MetaTag::LIST);

    //child->insert(2.0123);



    std::function<void(ASTNode*)> visitor;
    visitor = [&visitor](ASTNode* node) {
        if (int* p = boost::get<int>(&node->get_data())) {
            std::cout << *p << ' ';
        } else if (std::string* p = boost::get<std::string>(&node->get_data())) {
            std::cout << '\"' << *p << '\"' << ' ';
        } else if (MetaTag* p = boost::get<MetaTag>(&node->get_data())) {
            if (*p == MetaTag::LIST) {
                std::cout << "( ";
                for (auto& it : node->get_children()) {
                    visitor(it.get());
                }
                std::cout << ") ";
            } else {
                assert(false);
                std::cout << "UNIMPLEMENTED ";
            }
        }
    };

    root.visit(visitor);
    std::cout << std::endl;
}