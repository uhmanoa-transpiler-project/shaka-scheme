#ifndef SHAKA_IDATANODE_H
#define SHAKA_IDATANODE_H

#include <boost/variant/get.hpp>

namespace shaka {

class IDataNode {
public:
    ~IDataNode() {}

};

using boost::get;

} // namespace shaka


#endif // SHAKA_IDATANODE_H