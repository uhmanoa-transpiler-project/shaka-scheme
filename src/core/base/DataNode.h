#ifndef SHAKA_CORE_BASE_DATANODE_H
#define SHAKA_CORE_BASE_DATANODE_H

#include <boost/variant.hpp>

#include "core/base/Data.h"

namespace shaka {

/// @brief Implements the basic list and literal data structure
///        for Scheme. It is closely related to the pair.
class DataNode : public std::enable_shared_from_this<DataNode>{
public:

    /// @brief Used for cons
    // DataNode (Ptr head, Ptr tail = nullptr) :
    //     head(head),
    //     tail(tail) {}
    DataNode (Data head) :
        head(head),
        tail(nullptr) {}

    DataNode (DataNode left, DataNode right) {
        auto h = std::make_shared<DataNode>(left.head);
        h->tail = left.tail;

        auto t = std::make_shared<DataNode>(right.head);
        t->tail = right.tail;

        head = h;
        tail = t;
    }

    //DataNode (const DataNode& other) :
    //    head(other.car()),
    //    tail(other.cdr()) {}

    bool is_null() const {
        if (head.type() == typeid(ListPtr)) {
            if (tail.type() == typeid(ListPtr)) {
                return !get<ListPtr>(head) && !get<ListPtr>(tail);
            }
        }
        return false;
    }

    bool is_pair() const {
        if (head.type() == typeid(ListPtr)) {
            if (tail.type() == typeid(ListPtr)) {
                return get<ListPtr>(head) && get<ListPtr>(tail);
            }
        }
        return false;
    }

    static DataNode cons (DataNode left, DataNode right) {
        return DataNode(left, right);
    }

    ListPtr car() const {
        if (this->is_pair()) {
            if (head.type() == typeid(ListPtr)) {
                return get<ListPtr>(head);
            }
        } else {
            throw std::runtime_error("DataNode.cdr: argument is not pair");
            return nullptr;
        }
    }

    ListPtr cdr() const {
        if (this->is_pair()) {
            if (tail.type() == typeid(ListPtr)) {
                return get<ListPtr>(tail);
            }
        } else {
            throw std::runtime_error("DataNode.cdr: argument is not pair");
            return nullptr;
        }
    }

    bool is_list() const {
        if (this->is_null()) { return true; }
        else if (this->is_pair()) {
            return this->cdr()->is_list();
        }
    }

    bool is_number() const {
        return !this->is_pair() && this->head.type() == typeid(shaka::Number);
    }

    bool is_string() const {
        return !this->is_pair() && this->head.type() == typeid(shaka::String);
    }

    bool is_symbol() const {
        return !this->is_pair() && this->head.type() == typeid(shaka::Symbol);
    }

    bool is_boolean() const {
        return !this->is_pair() && this->head.type() == typeid(shaka::Boolean);
    }
    
    bool is_environment() const {
        return !this->is_pair() && this->head.type() == typeid(shaka::Environment);
    }

    /// @brief Overloadable virtual destructor
    virtual ~DataNode () {}

    friend bool operator== (DataNode lhs, DataNode rhs);
    friend bool operator!= (DataNode lhs, DataNode rhs);
    friend std::ostream& operator<< (std::ostream& lhs, const DataNode& rhs);
private:

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


std::ostream& operator<< (std::ostream& lhs, const DataNode& rhs) {
    // If the current one is a single
    if (!rhs.is_pair()) {
        // null list ==> ()
        if (rhs.is_null()) {
            lhs << "()";
        }
        else if (rhs.is_number()) {
            auto data = get<Number>(rhs.head);
            lhs << data;
        }
        else if (rhs.is_string()) {
            auto data = get<String>(rhs.head);
            lhs << data;
        }
        else if (rhs.is_symbol()) {
            auto data = get<Symbol>(rhs.head);
            lhs << data;
        }
        else if (rhs.is_boolean()) {
            auto data = get<Boolean>(rhs.head);
            lhs << data;
        }
        else if (rhs.is_environment()) {
            lhs << "#<environment>";
        }
    }
    return lhs;
}

}


#endif // SHAKA_CORE_BASE_DATANODE_H
