#ifndef RULE_BOOLEAN_H
#define RULE_BOOLEAN_H

#include <string>
#include <cctype>
#include <iostream>

#include "core/parser/primitives.h"
#include "core/parser/Tokenizer.h"
#include "core/parser/Token.h"

#include "../base/Data.h"
#include "../base/DataNode.h"

namespace shaka {
namespace parser {
namespace rule {

template <typename T>
bool boolean(
    InputStream&    in,
    NodePtr         root,
    T&              interm
);

} 
} 
} 

#endif //RULE_BOOLEAN_H
