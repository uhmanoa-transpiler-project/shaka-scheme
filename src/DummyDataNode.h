#ifndef SHAKA_DUMMYDATANODE_H
#define SHAKA_DUMMYDATANODE_H

#include <boost/variant.hpp>

#include "IDataNode.h"

struct DummyDataNode : public IDataNode {
    enum class DummyMetaTag : int {
        SET,
        GET
    };

    using DummyData = boost::variant<
        std::string,
        DummyMetaTag
    >;

    DummyDataNode(std::string str) :
        data(str) {}

    DummyDataNode(DummyMetaTag metatag) :
        data(metatag) {}

    DummyMetaTag    type_tag;
    DummyData            data;
};

#endif // SHAKA_DUMMYDATANODE_H
