#ifndef SHAKA_CORE_BASE_IDATALIST_H
#define SHAKA_CORE_BASE_IDATALIST_H

#include <boost/variant.hpp>

#include "core/base/Data.h"

namespace shaka {

class DataList {
public:
    using Ptr = std::shared_ptr<Data>;

    /// @brief Used for cons
    DataList (Ptr head, Ptr tail) :
        head(head),
        tail(tail) {}

    DataList (Data d) :
        head(std::make_shared<Data>(d)),
        tail(nullptr) {}

    /// @brief Overloadable virtual destructor
    virtual ~DataList () {}

    Ptr car () { return head; }

    Ptr cdr () { return tail; }

    Ptr cons (Ptr h, Ptr t) {
        return std::make_shared<Data>(std::make_shared<DataList>(h, t));
    }

    void set_car (Ptr p) {
        head = p;
    }

    void set_car (Data d) {
        head = std::make_shared<Data>(d);
    }

    void set_cdr (Ptr p) {
        tail = p;
    }

    void set_cdr (Data d) {
        tail = std::make_shared<Data>(d);
    }

    bool is_pair () const {
        return tail != nullptr;
    }

    bool is_null () const {
        return head == nullptr;
    }

    bool is_list () const {
        if (tail->type() == typeid(std::shared_ptr<DataList>)) {
            if (shaka::get<std::shared_ptr<DataList>>(*tail)) {
                auto data_tail = shaka::get<std::shared_ptr<DataList>>(*tail);
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

private:

    std::size_t length_recursive (std::size_t length) const {
        // If the tail is another pair, check it.
        if (tail->type() == typeid(std::shared_ptr<DataList>)) {
            // If the tail is another pair, continue.
            auto data_tail = shaka::get<std::shared_ptr<DataList>>(*tail);
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
    Ptr head;
    Ptr tail;
};

}


#endif // SHAKA_CORE_BASE_IDATALIST_H
