#ifndef SHAKA_CORE_BASE_DATANODE_H
#define SHAKA_CORE_BASE_DATANODE_H

#include <boost/variant.hpp>

#include "core/base/Data.h"

namespace shaka {

class DataNode : public std::enable_shared_from_this<DataNode>{
public:

    /// @brief Used for cons
    // DataNode (Ptr head, Ptr tail = nullptr) :
    //     head(head),
    //     tail(tail) {}

    DataNode (Data head, Data tail = nullptr) :
        head(head),
        tail(tail) {}

    /// @brief Overloadable virtual destructor
    virtual ~DataNode () {}

    Data car () {
        return head;
    }

    Data cdr () { return tail; }

    Data cons (Data t) {
        return std::make_shared<DataNode>(
            this->shared_from_this(),
            t
        );
    }

    void set_car (Data p) {
        head = p;
    }

    void set_cdr (Data p) {
        tail = p;
    }

    bool is_pair () const {
        if (auto* ptr = shaka::get<std::shared_ptr<DataNode>>(&tail)) {
            return *ptr != nullptr;
        }
        return true;
    }

    bool is_null () const {
        return *this == DataNode(nullptr, nullptr);
    }

    bool is_list () const {
        if (tail.type() == typeid(std::shared_ptr<DataNode>)) {
            if (shaka::get<std::shared_ptr<DataNode>>(tail)) {
                auto data_tail = shaka::get<std::shared_ptr<DataNode>>(tail);
                if (!data_tail) { return true; }
                else { return data_tail->is_list(); }
            } else {
                return false;
            }
        }
    }

    std::size_t length () const {
        if (this->is_null()) { return 0; }
        return length_recursive(1);
    }

    friend bool operator== (DataNode lhs, DataNode rhs);
    friend bool operator!= (DataNode lhs, DataNode rhs);
private:

    std::size_t length_recursive (std::size_t length) const {
        // If the tail is another pair, check it.
        if (tail.type() == typeid(std::shared_ptr<DataNode>)) {
            // If the tail is another pair, continue.
            auto data_tail = shaka::get<std::shared_ptr<DataNode>>(tail);
            // If the tail is null, we have the list length already.
            if (!data_tail) { return length; }
            // Otherwise, we need to get one more with the child.
            else { return data_tail->length_recursive(length+1); }
        }
        // Otherwise, stop.
        else {
            return length;
        }
    }

    // The two storage cells in a list.
    Data head;
    Data tail;
};

bool operator== (shaka::DataNode lhs, shaka::DataNode rhs) {
    return lhs.head == rhs.head && lhs.tail == rhs.tail;
}

bool operator!= (shaka::DataNode lhs, shaka::DataNode rhs) {
    return !operator==(lhs, rhs);
}

}



#endif // SHAKA_CORE_BASE_DATANODE_H
