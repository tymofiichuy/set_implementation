#include <iostream>

#include "set.h"

using namespace std;

bool multitype_set::set_search(variants el){
    node* temp = head;
    while (temp->link != nullptr){
        if (typeid(el).name() == typeid(temp->data).name()){
            if (el == temp->data){
                return true;
            }
        }
    }
}