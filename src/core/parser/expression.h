#ifndef SHAKA_CORE_PARSER_EXPRESSION_H_
#define SHAKA_CORE_PARSER_EXPRESSION_H_

#include "core/base/Core.h"
#include "core/parser/primitives.h"
#include "core/parser/list.h"
#include "core/parser/rule_number_impl.h"
#include "core/parser/rule_string_impl.h"

namespace shaka {
namespace parser {

template <typename T>
bool expression(
	InputStream& 	in,
	NodePtr		root,
	T&		interm
) {
	DataNode node1(NodePtr(nullptr));
	DataNode node2(NodePtr(nullptr));

	switch(in.peek().type) {
		case shaka::Token::Type::PAREN_START:
			node1 = list(in);

			if(node1 == node2) return false;

			break;

		case shaka::Token::Type::NUMBER:
/*			if(rule::number_integer(in, root, interm)) {
				return true;
			}
*/
			if(!rule::number_rational(in, root, interm) &&
			   !rule::number_real(in, root, interm)    &&
			   !rule::number_integer(in, root, interm)) {
				return false;
			}

/*			else if(rule::number_real(in, root, interm)) {
				return true;
			}
*/
			break;

		case shaka::Token::Type::STRING:
			if(!rule::string(in, root, interm))	return false;
			break;

		default:
			throw std::runtime_error("Error: Expression Default");
			break;
	}  //end switch

	return true; 

}  //expression

}  //parser
}  //shaka

#endif //SHAKA_CORE_PARSER_LIST_H_
