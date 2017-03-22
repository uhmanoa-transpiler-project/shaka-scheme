#ifndef SHAKA_PARSER_RULES_RULE_DEFINE_H
#define SHAKA_PARSER_RULES_RULE_DEFINE_H

#include <cctype>
#include <exception>
#include <functional>
#include <stack>
#include <string>

#include "Number.h"
#include "Symbol.h"
#include "Data.h"
#include "IDataNode.h"

#include "Environment.h"
#include "Evaluator.h"
#include "Eval_Define.h"
#include "Procedure.h"
#include "Eval_Expression.h"
#include "Eval_Define_impl.h"
#include "Eval_Variable_impl.h"
#include "Eval_PrintTree.h"

#include "parser/primitives.h"
#include "parser/Tokenizer.h"
#include "parser/Token.h"

namespace shaka {
namespace parser {
namespace rule {

// Define using tokens
template <typename T>
bool define(
    InputStream&    in,
    NodePtr         root, // shared ptr to IDataNode<Data>
    T&              interm
);


} // namespace rule
} // namespace parser
} // namespace shaka


#endif // SHAKA_PARSER_RULE_DEFINE_H
