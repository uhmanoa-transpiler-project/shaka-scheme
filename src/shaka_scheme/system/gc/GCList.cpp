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
        GCData *conductor = this->head;

        while(conductor != nullptr) {
            GCData *temp = conductor;
            conductor = conductor->get_next();
            delete temp;
            this->size--;
        }
    }

    bool GCList::is_empty() {
        return this->size == 0 && this->head == nullptr;
    }

    int GCList::get_size() {
        return this->size;
    }

    void GCList::add_data(GCData *data) {
        data->set_next(head);
        this->head = data;
        this->size++;
    }

    void GCList::sweep() {
        GCData *prev = nullptr;
        GCData *curr = this->head;

        if(this->is_empty()) return;

        while(curr != nullptr) {
            if(!curr->is_marked()) {
                if(curr == this->head) {
                    head = head->get_next();
                    GCData *temp = curr;
                    curr = curr->get_next();
                    delete temp;
                    this->size--;
                }
                else {
                    prev->set_next(curr->get_next());
                    GCData *temp = curr;
                    curr = curr->get_next();
                    delete temp;
                    this->size--;
                }
            }
            else {
                curr->unmark();
                prev = curr;
                curr = curr->get_next();
            }
        }
    }
}