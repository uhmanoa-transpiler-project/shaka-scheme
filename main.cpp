#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <functional>

namespace shaka {

struct Object {
    enum class Type : int {
        kBoolean,
        kChar,
        kNull,
        kPair,
        kProcedure,
        kSymbol,
        kBytevector,
        kEof_Object,
        kNumber,
        kPort,
        kString,
        kVector,
        kRecord
    };

    union {
    public:
        bool                            m_boolean_;
        char                            m_char_;
        std::pair<Object*, Object*>     m_pair_;
        std::function<Object(Object)>   m_procedure_;
        std::string                     m_symbol_;
        std::vector<uint8_t>            m_bytevector_;
        int                             m_eof_object_;
        double                          m_number_;
        int                             m_port_;
        std::string                     m_string_;
        std::vector<Object>             m_vector_;
        int                             m_record_; 
    };

    Object(Object::Type type) {
        type_ = type;
        m_boolean_ = true;        
    }

    ~Object() {
        destroy_union();
    }

    void destroy_union() {
        if (type_ == Object::Type::kBoolean) {

        }
    }

    Object::Type get_type() { return type_; }
    void set_type(Object::Type type) { type_ = type; }

private:
    Object::Type            type_;

};

}   

int main() {
    shaka::Object object1(shaka::Object::Type::kBoolean);
    shaka::Object object2(shaka::Object::Type::kChar);


    std::cout << static_cast<int>(object1.get_type()) << std::endl;
    std::cout << static_cast<int>(object2.get_type()) << std::endl;
    std::cout << object1.m_boolean_ << std::endl;
}