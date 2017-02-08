#ifndef SHAKA_DUMMYDATANODE_H
#define SHAKA_DUMMYDATANODE_H

#include <boost/variant.hpp>

#include "IDataNode.h"

namespace shaka {
    /*

enum class DummyMetaTag : int {
    SET,
    GET
};

using DummyData = boost::variant<
    std::string,
    DummyMetaTag
>;

template <>
struct DummyDataNode : public IDataNode<DummyData> {

    DummyDataNode(std::string str) :
        data(str) {}

    DummyDataNode(DummyMetaTag metatag) :
        data(metatag) {}
};
*/

} // namespace shaka

#endif // SHAKA_DUMMYDATANODE_H
