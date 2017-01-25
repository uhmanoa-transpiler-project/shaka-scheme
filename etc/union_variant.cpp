#include <iostream>
#include <string>
#include <vector>

struct Pseudo_Variant {

    // Type enum declaration
    enum class Type : int {
        STRING,
        VECTOR,
        INTEGER
    };

    // class-level union members
    union {
        std::string str;
        int i;
    };

    // constructor
    Pseudo_Variant(std::string str)
    {
        type = Pseudo_Variant::Type::STRING;
        new (&this->str) std::string(str);
    }

    // destructor
    ~Pseudo_Variant() {
        destroy_union();
    }

    // union destructor delegator
    void destroy_union()
    {
        using std::string;
        if (type == Pseudo_Variant::Type::STRING) {
            (&str)->string::~string();
        }
    }

    Type type;
};

int main() {
    Pseudo_Variant pv(std::string("Hello world"));

    std::cout << pv.str << std::endl;
    
}