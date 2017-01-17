#ifndef SHAKA_SEXPRESSION_H
#define SHAKA_SEXPRESSION_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <boost/variant.hpp>

namespace shaka {

struct Symbol {
    Symbol() {}

    Symbol(std::string str) :
        name(str) {}

    std::string to_string() {
        return '\'' + name + '\'';
    }

    std::string name;
};

struct Number {
    Number() {}

    Number(double d) :
        number(d) {}

    std::string to_string() {
        std::stringstream ss;
        ss << number;
        return ss.str();
    }

    double number;
};

struct String {
    String() {}
    String(std::string str) :
        str(str) {}

    std::string to_string() {
        return str;
    }

    std::string str;
};

using SExpression = boost::make_recursive_variant<
    Symbol,
    Number,
    String,
    std::vector<boost::recursive_variant_>
>::type;

std::ostream& operator<<(std::ostream& lhs, Symbol rhs) {
    lhs << rhs.to_string();
    return lhs;
}

std::ostream& operator<<(std::ostream& lhs, Number rhs) {
    lhs << rhs.to_string();
    return lhs;
}

std::ostream& operator<<(std::ostream& lhs, String rhs) {
    lhs << rhs.to_string();
    return lhs;
}

std::ostream& operator<<(std::ostream& lhs, std::vector<SExpression> rhs) {
    lhs << "(";
    for (auto it : rhs) {
        lhs << ' ' << it;
    }
    lhs << " )";
    return lhs;
}

using SExpressionList = std::vector<SExpression>;

} // namespace shaka



#endif // SHAKA_SEXPRESSION_H
