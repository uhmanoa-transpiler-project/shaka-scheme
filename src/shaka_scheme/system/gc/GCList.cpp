//
// Created by Brandon Wong on 2/17/18.
//

#include "shaka_scheme/system/gc/GCData.hpp"
#include "shaka_scheme/system/gc/GCList.hpp"

namespace shaka {

    GCList::GCList() {
        this->size = 0;
        this->head = nullptr;
    }

    GCList::~GCList() {
        GCData *conductor = this->head; //GCData *conductor = set_next(head);

        while(conductor != nullptr) {
            GCData *newptr = conductor;
            conductor = conductor->get_next();
            delete newptr;
        }

    }

    bool GCList::is_empty() {
        return this->size == 0 && this->head == nullptr;
    }

    void GCList::add_data(GCData *data) {
        data->set_next(head);
        this->head = data;
    }

    void GCList::sweep() {
        /*GCData **ptp = this->head;

        if(this->is_empty()) return;


        while(conductor != nullptr) {
            if(!conductor->is_marked()) {
                GCData *newptr = conductor;
                conductor = conductor->get_next();
                delete newptr;
            }
            else
                conductor = conductor->get_next();
        }*/
    }
}