#include<iostream>
#include<random>
#include<chrono>
#include<string>

#include "multitype_set.h"

using namespace std;

string random_string(mt19937& mt){
    uniform_int_distribution<int> dist_ch (0, 25);
    uniform_int_distribution<int> dist_len (0, 255);

    string r_string;
    int len = dist_len(mt);
    r_string.reserve(len);

    for(int i = 0; i <= len; i++){
        char ch = static_cast<char>('a' + dist_ch(mt));
        r_string += ch;
    }
    return r_string;
}

float random_float(mt19937& mt){
    uniform_real_distribution<float> dist_f (0.0F, 1.0F);

    return dist_f(mt);
}

multitype_set* random_set(mt19937& mt, int size, multitype_set* set){
    uniform_int_distribution<int> dist_i (1, 100000);
    uniform_int_distribution<int> dist_var (0, 2);

    bool flag = false;

    for(int i_counter = 0; i_counter < size; i_counter++){
        int var = dist_var(mt);
        
        switch(var){
            case 0:
                while (!flag){
                    int i = dist_i(mt);
                    try{
                        set->set_insert(i);
                        flag = true;
                    }
                    catch(const invalid_argument&){ 
                        continue; 
                    }
                }
                flag = false;
                break;
            case 1:
                while (!flag){
                    string s = random_string(mt);
                    try{
                        set->set_insert(s);
                        flag = true;
                    }
                    catch(const invalid_argument&){   
                        continue;
                    }
                }
                flag = false;
                break;
            case 2:
                while (!flag){
                    float f = random_float(mt);
                    try{
                        set->set_insert(f);
                        flag = true;
                    }
                    catch(const invalid_argument&){   
                        continue;
                    }
                    }
                    flag = false;
                    break;
        }
    }
    return set;
}

multitype_set* random_set_with_fixed_element (mt19937& mt, int size, multitype_set* set, variants el){
    uniform_int_distribution<int> dist_s (0, size - 1);
    int h_size = dist_s(mt);

    random_set(mt, h_size, set);
    set->set_insert(el);
    random_set(mt, size - h_size - 1, set);

    return set;
}

int main(){
    random_device rd;
    mt19937 mt (rd());

    multitype_set* A = new multitype_set;
    multitype_set* B = new multitype_set;
    multitype_set* C = new multitype_set;
    int init_size = 25;

    for (int s_counter = 0; s_counter <= 2; s_counter++){
        A = random_set(mt, init_size, A);
        B = random_set(mt, init_size, B);
        C = random_set_with_fixed_element(mt, init_size, C, 0);

        chrono::microseconds s_np_total(0);
        chrono::microseconds s_p_total(0);
        chrono::microseconds d_total(0);

        for(int i = 0; i < 1000; i++){
            auto start = chrono::high_resolution_clock::now();
            A->set_search(0);
            auto end = chrono::high_resolution_clock::now();
            s_np_total += chrono::duration_cast<chrono::microseconds>(end - start);

            start = chrono::high_resolution_clock::now();
            C->set_search(0);
            end = chrono::high_resolution_clock::now();
            s_p_total += chrono::duration_cast<chrono::microseconds>(end - start);

            start = chrono::high_resolution_clock::now();
            delete A->set_difference(*B);
            end = chrono::high_resolution_clock::now();
            d_total += chrono::duration_cast<chrono::microseconds>(end - start);
        }

        A->set_clear();
        B->set_clear();
        C->set_clear();

        cout << "Search test (element not present) for " << init_size << " elements: " << s_np_total.count()/1000 << " microseconds\n" <<
        "Search test (element present) for " << init_size << " elements: " << s_p_total.count()/1000 << " microseconds\n" <<
        "Difference test for " << init_size << " elements: " << d_total.count()/1000 << " microseconds\n\n";

        init_size += 100;
    }

    delete A;
    delete B;
    delete C;

    return 0;
}