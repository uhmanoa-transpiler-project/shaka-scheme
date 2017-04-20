#ifndef SHAKA_CORE_PARSER_TOKEN_H
#define SHAKA_CORE_PARSER_TOKEN_H

#include <iostream>
#include <string>

namespace shaka {

struct Token {
public:
    enum class Type : int {
        INVALID = 255,
        IDENTIFIER = 1,
        BOOLEAN_TRUE = 2,
        BOOLEAN_FALSE = 3,
        NUMBER = 4,
        CHARACTER = 5,
        STRING = 6,
        PAREN_START = 7,
        VECTOR_START = 8,
        BYTEVECTOR_START = 9,
        PAREN_END = 10,
        QUOTE = 11,
        BACKTICK = 12,
        COMMA = 13,
        COMMA_ATSIGN = 14,
        PERIOD = 15,
        DATUM_COMMENT = 16,
        COMMENT_START = 17,
        COMMENT_END = 18,
        DIRECTIVE = 19,
        END_OF_FILE = 0
    };

    Token::Type type;
    std::string str;

    Token(Token::Type type) :
        type(type),
        str("") {}

    Token(Token::Type type, const std::string& str) :
        type(type),
        str(str) {}

    bool operator== (const Token& other) {
        return (this->type == other.type &&
                this->str  == other.str);
    }

    bool operator!= (const Token& other) {
        return !(operator==(other));
    }

    shaka::Token::Type get_type() const {
        return this->type;
    }

    std::string get_string() const {
        return this->str;
    }

    friend bool operator== (const Token& lhs, const Token& rhs);
    friend bool operator!= (const Token& lhs, const Token& rhs);

};

std::ostream& operator<< (std::ostream& out, Token rhs) {
    out << "Token(" << static_cast<int>(rhs.type) << ",\"" << rhs.str << "\")";
    return out;
}

bool operator== (const Token& lhs, const Token& rhs) {
    return (
        lhs.type == rhs.type &&
        lhs.str == rhs.str
    );
}

bool operator!= (const Token& lhs, const Token& rhs) {
    return !operator==(lhs, rhs);
}

} // namespace shaka

#endif // SHAKA_PARSER_TOKEN_H
