#include <iostream>

#include "multitype_set.h"

using namespace std;

bool node::data_comparison(variants d){
    if (typeid(data).name() == typeid(d).name()){
            if (data == d){
                return true;
            }
            else{
               return false;
            }
        }
        else{
            return false;
        } 
}

node* multitype_set::set_search(variants el){
    if (head == nullptr){
        return nullptr;
    }

    node* temp = head;
    while (temp->next != nullptr){
        if (temp->data_comparison(el)){
            return temp;
        };
        temp = temp->next;
    }
    if (temp->data_comparison(el)){
         return temp;
    }
    else{
        return nullptr;
    }
}

void multitype_set::set_insert(variants el){
    if (!this->set_search(el)){
        node* ref = new node;
        ref->data = el;
        if (head == nullptr){
            ref->next = nullptr;
            ref->prev = nullptr;
            head = ref;
        }
        else{
            ref->next = head;
            ref->prev = nullptr;
            head->prev = ref;
            head = ref;  
        }
    }
    else{
        cerr << "Element is already in set";
    }
}

void multitype_set::set_delete(variants el){
    node* res = this->set_search(el);
    if (res){
        if (res == head){
            head = res->next;
            delete res;
        }
        else{
            res->prev->next = res->next;
            delete res;  
        }
    }
    else{
        cerr << "Nothing to delete";
    }
}

void multitype_set::set_clear(){
    while(head){
        this->set_delete(head->data);
    }
}

multitype_set::~multitype_set(){
    this->set_clear();
}

bool multitype_set::is_subset(multitype_set set){
    while(set.head){
        if(!this->set_search(set.head->data)){
            return false;
        }
    }
    return true;
}

bool multitype_set::operator==(multitype_set set){
    return(this->is_subset(set) && set.is_subset(*this));
}