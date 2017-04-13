//File name: rule_if.h

#ifndef RULE_IF_H
#define RULE_IF_H

#include <cctype>
#include <exception>
#include <functional>
#include <stack>
#include <string>

#include "Number.h"
#include "Symbol.h"
#include "Data.h"
#include "IDataNode.h"
#include "ASCII_String.h"

#include "Environment.h"
#include "Evaluator.h"
#include "Procedure.h"
#include "Eval_Expression.h"
#include "Eval_Variable_impl.h"
#include "Eval_PrintTree.h"

#include "parser/primitives.h"
#include "parser/Tokenizer.h"
#include "parser/Token.h"

namespace shaka {
namespace parser {
namespace rule {

template <typename T>

bool rule_if(
	InputStream&	in,
	NodePtr		root,
	T&		interm
);

}
}
}

#endif //RULE_IF_H