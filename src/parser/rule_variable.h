#ifndef RULE_VARIABLE_H
#define RULE_VARIABLE_H

#include <cctype>
#include <iostream>

#include "parser/primitives.h"
#include "parser/Tokenizer.h"

#include "Data.h"
#include "DataNode.h"
#include "Procedure.h"

namespace shaka {
namespace parser {
namespace rule {

template <typename T>
bool variable(
    InputStream&    in,
    NodePtr         root,
    T&              interm
);

}
}
}

#endif 
