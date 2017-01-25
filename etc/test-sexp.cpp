#include <iostream>
#include <sstream>
#include <vector>

#include <boost/variant.hpp>

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

class TypeVisitor :
    boost::static_visitor<> {
public:
    TypeVisitor(std::ostream& out) :
        out(out) {}

    void operator() (Number d) {
        out << d.to_string();
    }

    void operator() (Symbol s) {
        out << s.to_string();
    }

    void operator() (std::vector<SExpression> expr) {
        out << "(";
        for (auto it : expr) {
            out << ' ' << it;
        }
        out << " )";
    }
private:
    std::ostream& out;
};

using SExpressionList = std::vector<SExpression>;

int main() {
    std::cout << "Hello world!" << std::endl;

    SExpression sexpr;

    sexpr = std::vector<SExpression>();
    auto& vec = boost::get<std::vector<SExpression>>(sexpr);

    vec.push_back(SExpression(1.0));
    vec.push_back(SExpression(Symbol("hello")));
    vec.push_back(
        SExpressionList()
    );


    std::stringstream ss;
    ss << sexpr;
    std::cout << ss.str() << std::endl;


    std::cout << sexpr << std::endl;

}