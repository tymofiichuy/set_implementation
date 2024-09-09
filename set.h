#pragma once
#include<variant>
#include<string>
//#include<any>

#define variants variant<string, int, float, char, multitype_set>

struct node{
    variants data;
    //any data;
    node* link;
};

class multitype_set{
public:
    node* head;
    void set_insert(variants el);
    void set_delete(variants el);
    bool set_search(variants el);
    void set_clear();
    multitype_set set_union(multitype_set);
    multitype_set set_union(multitype_set);
    multitype_set set_intersection(multitype_set);
    multitype_set set_difference(multitype_set);
    multitype_set set_sym_difference(multitype_set);
    bool is_subset(multitype_set);
};