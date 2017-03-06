#ifndef EVAL_PROC_CALL_H
#define EVAL_PROC_CALL_H

#include "IEvaluatorStrategy.h"
#include "IDataNode.h"
#include "IEnvironment.h"
#include "IProcedure.h"
#include "Procedure.h"
#include <vector>
#include <memory>
#include <type_traits>

// attempts to get the procedure bound in the current environment
// and call it on the arguments condained as the child nodes of the
// list node that the procedure is called on
// returns a pointer to the list node with its child nodes
// updated to be the result(s) of the procedure call


template <typename T, typename Key, typename Value>
class Proc_Call : public shaka::IEvaluatorStrategy<T, Key, Value> {

	std::shared_ptr<shaka::IDataNode<T>> evaluate(std::shared_ptr<shaka::IDataNode<T>>& node,
			std::shared_ptr<shaka::IEnvironment<Key, Value>> env) {
		shaka::IProcedure<T> proc = env->get_value(shaka::get<Key>(*node->get_child(0)->get_data()));
		if (proc) {
			std::vector<T> args;
			std::shared_ptr<shaka::IDataNode<T>> list_node = node->get_child(1);
			std::shared_ptr<shaka::IDataNode<T>> next_argument;
			for (int i = 0; i < list_node->get_num_children(); i++) {
				next_argument = list_node->get_child(i);
				args.push_back(*next_argument->get_data());
			}

			std::vector<T> result = proc->call(args);
			for (int i = 0; i < list_node->get_num_children(); i++) {
				list_node->remove_child(i);
		
			}

			for (int i = 0; i < result.size(); i++) {
				list_node->insert_child(i, std::make_shared<Value>(result[i]));
			}

			return list_node;
		}

		else {
			return nullptr;
		}

};

#endif
