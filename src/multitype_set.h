#pragma once

#include<variant>
#include<string>

#define variants variant<char, int, float, string, multitype_set>

class node{
public:
    variants data;
    node* next;
    node* prev;

    bool data_comparison(variants d);
};

class multitype_set{
public:
    node* head;

    void set_insert(variants);
    void set_delete(variants);
    node* set_search(variants);
    void set_clear();

    //pass by reference?
    multitype_set set_union(multitype_set);
    multitype_set set_intersection(multitype_set);
    multitype_set set_difference(multitype_set);
    multitype_set set_sym_difference(multitype_set);
    bool is_subset(multitype_set);

    bool operator==(multitype_set);

    ~multitype_set();
};