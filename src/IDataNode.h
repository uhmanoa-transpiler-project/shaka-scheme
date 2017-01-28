#ifndef SHAKA_IDATANODE_H
#define SHAKA_IDATANODE_H

#include <boost/variant/get.hpp>

class IDataNode {
public:
    ~IDataNode() {}

};

using boost::get;


#endif // SHAKA_IDATANODE_H