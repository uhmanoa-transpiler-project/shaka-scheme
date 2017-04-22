#ifndef SHAKA_CORE_BASE_DATANODE_IMPL_H
#define SHAKA_CORE_BASE_DATANODE_IMPL_H

namespace shaka {

bool DataNode::is_scheme_procedure() const {
    return !this->is_pair() && this->head.type() == typeid(Procedure);
}

bool DataNode::is_native_procedure() const {
    return !this->is_pair() && this->head.type() == typeid(NativeProcedure);
}

bool DataNode::is_primitive_procedure() const {
    return !this->is_pair() &&
        this->head.type() == typeid(PrimitiveProcedure);
}

bool DataNode::is_procedure() const {
    return !this->is_pair() && (
        this->head.type() == typeid(Procedure) || 
        this->head.type() == typeid(NativeProcedure) || 
        this->head.type() == typeid(PrimitiveProcedure)
    );
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
        else if (rhs.is_procedure()) {
            lhs << "#<procedure>";
        }
        /*
        else {
            auto data = get<NodePtr>(rhs.head);
            lhs << *data;
            lhs << rhs.head.type().name();
        }
        */
    
    }
    // Otherwise, this is some sort of list
    else {
        // Print out the first item.
        lhs << "("; 
        lhs << *rhs.car();
        // Then continue to print out the
        // other items.
        auto tail = *rhs.cdr();
        while (tail.is_pair()) {
            lhs << ' ' << *tail.car();
            tail = *tail.cdr();
        }
        // If this is a proper list, just close it.
        if (tail.is_null()) {
            auto last = get<ListPtr>(tail.tail);
            if (!last) { lhs << ")"; }
        }
        // Otherwise, this is an improper list,
        // and we must print out the last element.
        else {
            auto last = DataNode(tail.head);
            lhs << " . " << last << ")";
        }
    }
    return lhs;
}

} // namespace shaka

#endif //  SHAKA_CORE_BASE_DATANODE_IMPL_H
