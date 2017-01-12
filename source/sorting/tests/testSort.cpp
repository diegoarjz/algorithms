#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Sorting

#include <boost/test/unit_test.hpp>

#include <random>

#include "../InsertionSort.h"

template<class T>
bool isSorted(const T& container){
    auto iter = std::begin(container);
    auto prev = iter;
    iter++;
    for(/**/; iter != std::end(container); ++iter, ++prev){
        if(*iter < *prev)
            return false;
    }
    return true;
}

struct fixture{
    std::list<int> smallList;
    std::list<int> hugeList;
    
    fixture(){
        smallList = std::list<int>{
            4,5,2,7,8,6,3
        };
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1000);
        
        for(auto i=0; i<10000; ++i){
            hugeList.push_back(dis(gen));
        }
    }
};

BOOST_AUTO_TEST_CASE(test_insertion_sort_small){
    fixture f;
    
    InsertionSort(std::begin(f.smallList), std::end(f.smallList));
    
    BOOST_CHECK( isSorted(f.smallList) );
}

BOOST_AUTO_TEST_CASE(test_insertion_sort_huge){
    fixture f;
    
    InsertionSort(std::begin(f.hugeList), std::end(f.hugeList));
    
    BOOST_CHECK( isSorted(f.hugeList) );
}
