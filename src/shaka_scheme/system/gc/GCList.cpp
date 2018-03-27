//
// Created by Brandon Wong on 2/17/18.
//

#include "shaka_scheme/system/gc/GCData.hpp"
#include "shaka_scheme/system/gc/GCList.hpp"
#include <utility>

namespace shaka {
    namespace gc {

        GCList::GCList() :
            list_size(0),
            head(nullptr) {}

        GCList::~GCList() {
            GCData *conductor = this->head;

            while (conductor != nullptr) {
                GCData *temp = conductor;
                conductor = conductor->get_next();
                delete temp;
                //this->size--;
            }
        }
    
        GCList::GCList(GCList&& other) : list_size(0), head(nullptr) {
            swap(*this, other);
        }

        bool GCList::is_empty() {
            return this->list_size == 0 && this->head == nullptr;
        }

        int GCList::get_size() {
            return this->list_size;
        }

        void GCList::add_data(shaka::gc::GCData *data) {
            data->set_next(head);
            this->head = data;
            this->list_size++;
        }

        void GCList::sweep() {
            GCData *prev = nullptr;
            GCData *curr = this->head;

            //Check if the GCList is empty, return the list
            if (this->is_empty()) {
                return;
            }

            //While the GCList is not empty, traverse the list
            while (curr != nullptr) {

                //If the current GCData is not marked, remove it from GCList
                if (!curr->is_marked()) {

                    //Check if the head GCData object in GCList is an
                  // unmarked object
                    if (curr == this->head) {
                        head = head->get_next();
                        GCData *temp = curr;
                        curr = curr->get_next();
                        delete temp;
                        this->list_size--;

                    //Remove the GCData object if it is unmarked
                    } else {
                        prev->set_next(curr->get_next());
                        GCData *temp = curr;
                        curr = curr->get_next();
                        delete temp;
                        this->list_size--;
                    }

                    //If the GCData object is marked, unmark it then move on
                } else {
                    curr->unmark();
                    prev = curr;
                    curr = curr->get_next();
                }
            }
        }
        
        void GCList::swap(GCList& list1, GCList& list2) {
            using std::swap;
            swap(list1.list_size, list2.list_size);
            swap(list1.head, list2.head);
        }
    }
}