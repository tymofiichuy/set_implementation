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
    while (temp){
        if (temp->data_comparison(el)){
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void multitype_set::set_insert(variants el){
    if (!this->set_search(el)){
        this->set_unsafe_insert(el);
    }
    else{
        throw invalid_argument("Element is already in set");
    }
}

//Insert without check of element existance in a set
void multitype_set::set_unsafe_insert(variants el){
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

void multitype_set::set_delete(variants el){
    node* res = this->set_search(el);
    if (res){
        if (res == head){
            head = res->next;
            if(head){
                head->prev = nullptr;  
            }
            delete res;
        }
        else{
            res->prev->next = res->next;
            if (res->next){
                res->next->prev = res->prev;  
            }
            delete res;  
        }
    }
    else{
        throw invalid_argument("Nothing to delete");
    }
}

void multitype_set::set_clear(){
    while (head){
        this->set_delete(head->data);
    }
}

multitype_set::~multitype_set(){
    this->set_clear();
}

bool multitype_set::is_subset(multitype_set& set){
    node* temp = set.head;
    while (temp){
        if (!this->set_search(temp->data)){
            return false;
        }
        temp = temp->next; 
    }
    return true;
}

bool multitype_set::operator==(multitype_set& set){
    return(this->is_subset(set) && set.is_subset(*this));
}

multitype_set* multitype_set::set_union(multitype_set& set){
    multitype_set* S = new multitype_set;
    node* temp = head;
    while (temp){
        S->set_unsafe_insert(temp->data);
        temp = temp->next;
    }
    temp = set.head;
    while (temp){
        try{
            S->set_insert(temp->data);   
        }
        catch(const invalid_argument&){
        }
        temp = temp->next;
    }
    return S;
}

multitype_set* multitype_set::set_intersection(multitype_set& set){
    multitype_set* S = new multitype_set;
    node* temp = head;
    while (temp){
        if (set.set_search(temp->data)){
            S->set_unsafe_insert(temp->data);
        }
        temp = temp->next;        
    }
    return S;
}

multitype_set* multitype_set::set_difference(multitype_set& set){
    multitype_set* S = new multitype_set;
    node* temp = head; 
    while (temp){
        if (!set.set_search(temp->data)){
            S->set_unsafe_insert(temp->data);
        }
        temp = temp->next;         
    }
    return S;   
}

multitype_set* multitype_set::set_sym_difference(multitype_set& set){
    multitype_set* S;
    multitype_set* u_set = this->set_union(set);
    multitype_set* i_set = this->set_intersection(set);
    S = u_set->set_difference(*i_set);

    delete u_set;
    delete i_set;
    return S;
}