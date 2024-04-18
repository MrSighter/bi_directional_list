//
// Created by aleks on 21.03.2024.
//

#ifndef RING_BI_LIST_USE_H
#define RING_BI_LIST_USE_H

#include "bi_list.h"

//a function that returns a ring with only those elements that passed the predicate
template <typename Key, typename Info>
bi_list<Key, Info> filter(const bi_list<Key, Info>& source, bool pred(const Key&)){
    bi_list<Key, Info> filteredRing;
    for(auto it= source.begin();it!=source.end();it++){
        if(pred(it.returnKey())) filteredRing.push_back(it.returnKey(),it.returnInfo());
    }
    return filteredRing;
}

//a function that returns a joined ring of two given rings, keeping only unique key values
//if a given key exists function adds info to the info of that key
template <typename Key, typename Info>
bi_list<Key, Info> join(const bi_list<Key, Info>& first, const bi_list<Key, Info>& second){
    bi_list<Key, Info> joinedRing;
    joinedRing=first;
    bool added;
    for ( auto it = second.begin(); it != second.end(); ++it) {
        added=false;
        for (auto itJoin = joinedRing.begin(); itJoin != joinedRing.end(); ++itJoin){
            if(it.returnKey()==itJoin.returnKey()) {
                itJoin.addInfo(it.returnInfo());
                added=true;
                break;
            }
        }
        if(!added)joinedRing.push_back(it.returnKey(), it.returnInfo());
    }
    return joinedRing;
}

//a function returning a list that keeps unique keys only
template <typename Key, typename Info>
bi_list<Key, Info> unique(const bi_list<Key, Info>& source, Info aggregate(const Info&, const Info&)){
    bi_list<Key, Info> uniqueRing;

    for(auto it = source.begin();it!=source.end();++it){
        bool added=false;
        for(auto itUnique=uniqueRing.begin();itUnique!=uniqueRing.end();++itUnique){
            if(it.returnKey()==itUnique.returnKey()){
                itUnique.updateInfo(aggregate(it.returnInfo(), itUnique.returnInfo()));
                added=true;
                break;
            }
        }
        if(!added) uniqueRing.push_back(it.returnKey(), it.returnInfo());

    }
    return uniqueRing;
}
//a function returning a joined list, joining the next fcnt and scnt elements reps times
//Ex: list1 = {1,2,3,4,5}, list = {6,7,8,9,0}, fcnt=2,scnt=1,reps=3
//ReurnedList = {1,2,6,3,4,7,5,1,8}
//I wrote only the Key part of a node, because info is not important for this function
template <typename Key, typename Info>
bi_list<Key, Info> shuffle(const bi_list<Key, Info>& first, unsigned int fcnt, const bi_list<Key, Info>& second, unsigned int scnt, unsigned int reps){
    auto itFirst = first.begin();
    auto endFirst = first.end();
    if(itFirst==endFirst) throw std::logic_error("First list is empty. There is nothing to shuffle");
    auto itSecond = second.begin();
    auto endSecond = second.end();
    if(itSecond==endSecond) throw std::logic_error("Second list is empty. There is nothing to shuffle");
    bi_list<Key, Info> shuffledRing;
    for (int i = 0; i < reps; ++i) {
        for (int j = 0; j < fcnt; ++j) {
            shuffledRing.push_back(itFirst.returnKey(),itFirst.returnInfo());
            ++itFirst;
            if(itFirst==endFirst)++itFirst;
        }
        for (int j = 0; j < scnt; ++j) {
            shuffledRing.push_back(itSecond.returnKey(),itSecond.returnInfo());
            ++itSecond;
            if(itSecond==endSecond)++itSecond;
        }
    }
    return shuffledRing;
}

//a function that returns a list of elements that exist in the first ring but do not exist in the second one
template <typename num>
bi_list<num, num> subtract(const bi_list<num, num>& first, const bi_list<num,num>& second){
    bi_list<num,num> result;
    if(first.getSize()==0) return result;
    result=first;
    num resultBegin, resultEnd, secondBegin, secondEnd;
    if(second.getSize()==0) return result;
    for (auto it2 = second.begin(); it2 != second.end(); ++it2) {
        for (auto it = result.begin(); it != result.end() ; ++it) {
            resultBegin = it.returnKey();
            resultEnd = resultBegin + it.returnInfo();
            secondBegin = it2.returnKey();
            secondEnd = secondBegin+it2.returnInfo();
            if(resultBegin >= secondEnd) break;
            if(resultEnd<=secondBegin) continue;
            if(resultBegin<secondBegin&&resultEnd>secondBegin){
                it.updateInfo(it2.returnKey());
                continue;
            }
            if(resultBegin>=secondBegin&&resultEnd<=secondEnd){
                it=result.erase(it);
                it--;
                continue;
            }
            if(resultBegin>secondBegin){
                it=result.erase(it);
                it=result.insert(it,secondEnd,resultEnd);
                continue;
            }
            it.updateInfo(it2.returnKey());
            result.insert(++it,secondEnd,resultEnd);
            it--;
        }
    }
    return result;
}
#endif //RING_BI_LIST_USE_H
