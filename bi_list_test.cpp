//
// Created by aleks on 29.11.2023.
//

#include <iostream>
#include "bi_list_test.h"
#include "bi_list.h"
#include "bi_list_use.h"
void test_push_pop() {
    bi_list<int, int> ring;
    int checkKey = 1;
    // Test push_front and push_back
    auto it = ring.push_front(checkKey, checkKey);
    if (ring.getSize() != 1) {
        std::cerr << "Error in size after calling push_front. Should be " << checkKey << " instead of " << ring.getSize() << std::endl;
    }
    if(it.returnKey()!=checkKey){
        std::cerr<<"Error in Key value after push front. Should be "<<checkKey<<" instead of "<<it.returnKey()<<std::endl;
    }
    if(it.returnInfo()!=checkKey){
        std::cerr<<"Error in Key value after push front. Should be "<<checkKey<<" instead of "<<it.returnInfo()<<std::endl;
    }

    auto it2=ring.push_back(checkKey, checkKey);
    if (ring.getSize() != 2) std::cerr << "Error in size after calling push_back\n";

    if (it2.returnKey() != checkKey)std::cerr << "Error in Key value after push back. Should be " << checkKey << " instead of " << it2.returnKey()<< std::endl;
    if (it2.returnInfo() != checkKey) std::cerr << "Error in Key value after push back. Should be " << checkKey << " instead of " << it2.returnInfo() << std::endl;
    if(++it!=it2)std::cerr << "Error in iterator continuity" << std::endl;

    // Test pop_front
    it=ring.pop_front();

    if (ring.getSize() != 1) {
        std::cerr << "Error in pop_front\n";
    }
    if(it.returnKey()!=checkKey){
        std::cerr<<"Error in Key value after pop front. Should be "<<checkKey<<" instead of "<<it.returnKey()<<std::endl;
    }
    if(it.returnInfo()!=checkKey){
        std::cerr<<"Error in Key value after pop front. Should be "<<checkKey<<" instead of "<<it.returnInfo()<<std::endl;
    }

    ring.pop_front();

    // Test pop_front on an empty list
    ring.pop_front();

    // Test getSize after pop_front on an empty list
    if (ring.getSize() != 0) {
        std::cerr << "Error in size after calling pop_front on an empty list\n";
    }

    ring.push_back(1, 1);
    ring.push_back(1, 1);
    ring.push_back(1, 1);

    checkKey = 3;
    int checkClear = ring.clear();
    if (ring.getSize() != 0) {
        std::cerr << "Error in size after calling clear. Should be" << 0 << " instead of " << ring.getSize() << std::endl;
    }
    if(checkClear!=checkKey) std::cerr<<"Error in return value of clear method. Should return "<<checkKey<<" instead of "<<checkClear<<std::endl;
}

void test_insert_erase() {
    bi_list<int, int> ring;
    int checkKey = 1;
    // Test insert
    auto it = ring.begin();
    it = ring.insert(it, 1, 1);

    // Test getSize after insert
    if (ring.getSize() != 1) {
        std::cerr << "Error in insert\n";
    }
    if(it.returnKey()!=checkKey){
        std::cerr<<"Error in Key value after insert. Should be "<<checkKey<<" instead of "<<it.returnKey()<<std::endl;
    }
    if(it.returnInfo()!=checkKey){
        std::cerr<<"Error in Key value after insert. Should be "<<checkKey<<" instead of "<<it.returnInfo()<<std::endl;
    }

    auto it2 = ring.push_front(1, 1);
    // Test erase
    it2 = ring.erase(it2);


    if (ring.getSize() != 1) {
        std::cerr << "Error in size after calling erase. Should be 1 instead of "<<ring.getSize()<<std::endl;
    }
    if (it!=it2) std::cerr<<"Error in erase return value"<<std::endl;


    // Test erase on an empty list
    ring.clear();
    it = ring.erase(it);

    // Test getSize after erase on an empty list
    if (ring.getSize() != 0) {
        std::cerr << "Error in erase on an empty list\n";
    }
    if(it!=++it) std::cerr<<"Error in erase return value on an empty list"<<std::endl;
}

void test_find() {
    bi_list<int, int> ring;

    ring.push_back(1, 101);
    ring.push_back(2, 102);
    ring.push_back(1, 103);

    // Test find
    auto it = ring.find(ring.numberOfOccurrences(1), 1);
    if (it.returnKey() != 1 || it.returnInfo() != 103) {
        std::cerr << "Error in find. Should return iterator with key=1, info=103, instead of "<<it.returnKey()<<", "<<it.returnInfo()<<std::endl;
    }

    // Test find with non-existent value
    try {
        ring.find(2, 1);
    } catch (const std::out_of_range& e) {
        // Expected exception
    }

    // Test find with occurrence larger than the actual occurrences
    try {
        ring.find(2, 2);
    } catch (const std::out_of_range& e) {
        // Expected exception
    }
}

void test_filter() {
    bi_list<int, int> ring;
    ring.push_back(1, 10);
    ring.push_back(2, 20);
    ring.push_back(3, 30);


    bi_list<int, int> filteredRing = filter<int, int>(ring, [](const int& key) { return key % 2 == 0; });

    // Test filteredRing size
    if (filteredRing.getSize() != 1) {
        std::cerr << "Error in filter - incorrect size. Should be 1 instead of "<<filteredRing.getSize()<<std::endl;
    }

    // Test filteredRing content
    const auto it = filteredRing.begin();
    if (it.returnKey() != 2 || it.returnInfo() != 20) {
        std::cerr << "Error in filter - incorrect content. Should be key = 2, info = 20 instead of "<<it.returnKey()<<", "<<it.returnInfo()<<std::endl;
    }
}

void test_join() {
    bi_list<int, int> first;
    first.push_back(1, 10);
    first.push_back(2, 20);

    bi_list<int, int>  second;
    second.push_back(3, 10);
    second.push_back(3, 20);

    bi_list<int, int>  joinedRing = join(first, second);

    // Test joinedRing size
    if (joinedRing.getSize() != 3) {
        std::cerr << "Error in join - incorrect size. Should be 1 instead of "<<joinedRing.getSize()<<std::endl;
    }

    // Test joinedRing content
    auto it = joinedRing.begin();
    for (int i = 1; i <= joinedRing.getSize(); ++i) {
        if (it.returnKey() != i || it.returnInfo() != 10*i) {
            std::cerr << "Error in join - incorrect content. Node "<<i<<" Should be key = "<<i<<", info ="<<10*i<<" instead of "<<it.returnKey()<<", "<<it.returnInfo()<<std::endl;
        }
        ++it;
    }
}

void test_unique() {
    bi_list<int, int>  source;
    int checkKey=1;
    source.push_back(checkKey, checkKey);
    source.push_back(1+checkKey, 4);
    source.push_back(checkKey, checkKey);


    bi_list<int, int> uniqueRing = unique<int, int>(source, [](const int& a, const int& b) { return a + b; });

    // Test uniqueRing size
    if (uniqueRing.getSize() != 2) {
        std::cerr << "Error in unique - incorrect size. Should be 2 instead of "<<uniqueRing.getSize()<<std::endl;
    }

    // Test uniqueRing content
    auto it = uniqueRing.begin();
    for (checkKey=1; checkKey<= 2; ++checkKey) {
        if (it.returnKey() != checkKey || it.returnInfo() != 2*checkKey) {
            std::cerr << "Error in unique - incorrect content. Node " << checkKey
                      << " Should be key = "<<checkKey<<", info ="<<2*checkKey<<" instead of " << it.returnKey() << ", " << it.returnInfo()
                      << std::endl;
        }
        ++it;
    }
}

void test_shuffle() {
    bi_list<int, int> first;
    first.push_back(1, 10);
    first.push_back(2, 20);

    bi_list<int, int> second;
    second.push_back(3, 30);
    second.push_back(4, 40);

    bi_list<int, int> shuffledRing = shuffle(first, 1, second, 2, 2);

    // Test shuffledRing size
    if (shuffledRing.getSize() != 6) {
        std::cerr << "Error in shuffle - incorrect size. Should be 5 instead of "<<shuffledRing.getSize()<<std::endl;
    }

    // Test shuffledRing content
    auto it = shuffledRing.begin();
    if (it.returnKey() != 1 || it.returnInfo() != 10) {
        std::cerr << "Error in shuffle - incorrect content. Node "<<1<<" Should be key = 1, info = 10 instead of "<<it.returnKey()<<", "<<it.returnInfo()<<std::endl;
    }
    ++it;
    if (it.returnKey() != 3 || it.returnInfo() != 30) {
        std::cerr << "Error in shuffle - incorrect content. Node "<<2<<" Should be key = 3, info = 30 instead of "<<it.returnKey()<<", "<<it.returnInfo()<<std::endl;
    }
    ++it;
    if (it.returnKey() != 4 || it.returnInfo() != 40) {
        std::cerr << "Error in shuffle - incorrect content. Node "<<3<<" Should be key = 4, info = 40 instead of "<<it.returnKey()<<", "<<it.returnInfo()<<std::endl;
    }
    ++it;
    if (it.returnKey() != 2 || it.returnInfo() != 20) {
        std::cerr << "Error in shuffle - incorrect content. Node "<<5<<"Should be key = 2, info = 20 instead of "<<it.returnKey()<<", "<<it.returnInfo()<<std::endl;
    }
    ++it;
    if (it.returnKey() != 3 || it.returnInfo() != 30) {
        std::cerr << "Error in shuffle - incorrect content. Node "<<6<<" Should be key = 3, info = 30 instead of "<<it.returnKey()<<", "<<it.returnInfo()<<std::endl;
    }
    ++it;
    if (it.returnKey() != 4 || it.returnInfo() != 40) {
        std::cerr << "Error in shuffle - incorrect content. Node "<<7<<" Should be key = 4, info = 40 instead of "<<it.returnKey()<<", "<<it.returnInfo()<<std::endl;
    }

}

void test_subtract(){
    bi_list<float, float> first;
    bi_list<float, float> second;
    for (int i = 1; i < 10; i+=2) {
        first.push_back((float)(i), (float)(i));
    }
    second.push_back(3.0,7.0);
    subtract(first, second);
}


