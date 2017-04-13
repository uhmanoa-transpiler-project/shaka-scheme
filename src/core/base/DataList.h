#ifndef SHAKA_CORE_BASE_IDATALIST_H
#define SHAKA_CORE_BASE_IDATALIST_H

#include <boost/variant.hpp>

namespace shaka {

using boost::get;

class DataList;
class Symbol;
class Number;
class String;
class Boolean;

using Data = boost::variant<
    std::shared_ptr<DataList>
//    shaka::Symbol,
//    shaka::Number,
//    shaka::String,
//    shaka::Boolean
>;

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

    void set_cdr (Ptr p) {
        tail = p;
    }

    bool is_null() const {
        return tail == nullptr;
    }

    bool is_list() const {

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

    



private:
    // The two storage cells in a list.
    Ptr head;
    Ptr tail;
};

}

#endif // SHAKA_CORE_BASE_IDATALIST_H
