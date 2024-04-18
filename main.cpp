#include <iostream>
#include "bi_list_test.h"

int main() {

    test_push_pop();
    test_insert_erase();
    test_find();
    test_filter();
    test_join();
    test_unique();
    test_shuffle();
    test_subtract();
    std::cout<<"All tests passed!"<<std::endl;
    return 0;
}
