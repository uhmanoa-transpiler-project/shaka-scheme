#ifndef SHAKA_CORE_BASE_IDATALIST_H
#define SHAKA_CORE_BASE_IDATALIST_H

class DataList {
    using Ptr = std::shared_ptr<DataList>;

    DataList (Ptr head, Ptr tail) {
         
    }

    /// @brief Overloadable virtual destructor
    virtual ~IDataList() {}

    Ptr car () { return head; }
    Ptr cdr () { return tail; }
    Ptr cons (Ptr h, Ptr t) {
        return std::make_shared<DataList>(h, t);
    }

    // The two storage cells in a list.
    Ptr head;
    Ptr tail;
};

#endif // SHAKA_CORE_BASE_IDATALIST_H
