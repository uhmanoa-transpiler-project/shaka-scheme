#ifndef SHAKA_PARSER_TOKEN_H
#define SHAKA_PARSER_TOKEN_H

#include <string>

namespace shaka {

struct Token {
public:
    enum class Type : int {
        INVALID,
        IDENTIFIER,
        BOOLEAN_TRUE,
        BOOLEAN_FALSE,
        NUMBER,
        CHARACTER,
        STRING,
        PAREN_START,
        PAREN_END,
        BYTEVECTOR_START,
        U8_BYTEVECTOR_START,
        QUOTE,
        BACKTICK,
        COMMA,
        COMMA_ATSIGN,
        PERIOD,
        DATUM_COMMENT,
        COMMENT_START,
        COMMENT_END,
        DIRECTIVE,
        END_OF_FILE
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
};

std::ostream& operator<< (std::ostream& out, Token rhs) {
    out << "Token(" << static_cast<int>(rhs.type) << ",\"" << rhs.str << "\")";
    return out;
}

} // namespace shaka

#endif // SHAKA_PARSER_TOKEN_H
