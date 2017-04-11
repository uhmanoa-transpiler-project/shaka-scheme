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

bool conditional(
	InputStream&	in,
	NodePtr		root,
	T&		interm
);

}
}
}
