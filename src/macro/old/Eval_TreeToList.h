#ifndef SHAKA_EVAL_TREETOLIST_H
#define SHAKA_EVAL_TREETOLIST_H

namespace shaka {
namespace eval {


class TreeToList : public IEvaluatorStrategy {
public:
    using T = shaka::Data;
    using Key = shaka::Symbol;
    using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;

    Value evaluate(
        std::shared_ptr<IDataNode<T>> node,
        std::shared_ptr<IEnvironment<Key, Value>> env
    );

};

}
}

#endif // SHAKA_EVAL_TREETRANSFORM_H
