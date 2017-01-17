#ifndef SHAKA_LAMBDA_H
#define SHAKA_LAMBDA_H

#include <functional>

#include "SExpression.h"

class Lambda {
public:
    Lambda(std::function<SExpression(SExpression&)> func) :
        func(func) {}

    SExpression operator() (SExpression& expr) {
        return func(expr);
    }

private:
    std::function< SExpression(SExpression&) > func;
};


#endif // SHAKA_LAMBDA_H