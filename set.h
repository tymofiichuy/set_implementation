#pragma once
//#include<variant>
#include<any>

struct node{
    //variant<bool, int, float, char, multitype_set> data;
    any data;
    node* link;
};

class multitype_set{
public:
    node* head;
    void set_insert(any el);
    void set_delete(any el);
    bool set_search(any el);
    void set_clear();
    multitype_set set_union(multitype_set);
    multitype_set set_union(multitype_set);
    multitype_set set_intersection(multitype_set);
    multitype_set set_difference(multitype_set);
    multitype_set set_sym_difference(multitype_set);
    bool is_subset(multitype_set);
};