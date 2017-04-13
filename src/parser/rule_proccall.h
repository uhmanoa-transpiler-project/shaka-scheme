#ifndef SHAKA_PARSER_RULES_RULE_PROCCALL_H
#define SHAKA_PARSER_RULES_RULE_PROCCALL_H

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

// BNF:
// <procedure call> := (<operator> <operand>*)
// <operator>       := <expression>
// <operand>        := <expression>
//
// <expression> := <variable> | quote<datum> | '<datum> |
//                 <procedure call> | lambda<formals> <body> |
//                 if <test> <consequent> <alternative> |
//                 if <test> <consequent> | set! <variable> <expression> |
//                 derived expressions
template <typename T>
bool proc_call(InputStream& in, NodePtr root, T& interm);

} // namespace rule
} // namespace parser
} // namespace shaka


#endif // SHAKA_PARSER_RULE_RULE_PROCCALL_H
