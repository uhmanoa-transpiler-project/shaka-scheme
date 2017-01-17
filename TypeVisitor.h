#ifndef SHAKA_TYPEVISITOR_H
#define SHAKA_TYPEVISITOR_H

#include "SExpression.h"

class TypeVisitor :
    boost::static_visitor<> {
public:
    TypeVisitor(std::ostream& out) :
        out(out) {}

    void operator() (Number d) {
        out << "Number";
    }

    void operator() (Symbol s) {
        out << "Symbol";
    }

    void operator() (String s) {
        out << "String";
    }

    void operator() (std::vector<SExpression> expr) {
        out << "Vector(";
        for (auto it : expr) {
            out << ' ';
            TypeVisitor tv(out);
            boost::apply_visitor(tv, it);
        }
        out << " )";
    }

    std::ostream& get_ostream() {
        return out;
    }
private:
    std::ostream& out;
};

#endif // SHAKA_TYPEVISITOR_H