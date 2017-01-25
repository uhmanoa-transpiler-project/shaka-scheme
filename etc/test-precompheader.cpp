#include "SExpression.h"
#include "TypeVisitor.h"
#include "Lambda.h"

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

    // 
    Lambda doubler ([&doubler](SExpression& expr) -> SExpression {
        if (Number* ptr = boost::get<Number>(&expr)) {
            ptr->number *= 2;
        } else if (String* ptr = boost::get<String>(&expr)) {
            ptr->str += ptr->str;
        } else if (Symbol* ptr = boost::get<Symbol>(&expr)) {
            ptr->name += ptr->name;
        } else if (SExpressionList* ptr = boost::get<SExpressionList>(&expr)) {
            for (auto& it : *ptr) {
                doubler(it);
            }
        } else {
            throw std::runtime_error("func is wrong");
        }
        return expr;
    });

    TypeVisitor type_cout(std::cout);

    boost::apply_visitor(type_cout, sexpr);
    type_cout.get_ostream() << std::endl;

    doubler(sexpr);


    std::cout << sexpr << std::endl;

}
