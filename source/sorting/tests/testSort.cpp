#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Sorting

#include <boost/test/unit_test.hpp>

#include <iostream>
#include <random>
#include <iterator>
#include <algorithm>

#include <Timer.h>

#include "../InsertionSort.h"
#include "../SelectSort.h"
#include "../BubbleSort.h"
#include "../MergeSort.h"
#include "../QuickSort.h"

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

/* ********************************
 * Standard Template Library Sort *
 * *******************************/
BOOST_AUTO_TEST_CASE(test_stl_sort_small){
    fixture f;
    
    {
        std::cout << "test_stl_sort_small: ";
        Timer t;
        f.smallList.sort();
    }
    
    BOOST_CHECK( isSorted(f.smallList) );
}

BOOST_AUTO_TEST_CASE(test_stl_sort_huge){
    fixture f;
    
    {
        std::cout << "test_stl_sort_huge: ";
        Timer t;
        f.hugeList.sort();
    }
    
    BOOST_CHECK( isSorted(f.hugeList) );
}

/* ****************
 * Insertion Sort *
 * ***************/
BOOST_AUTO_TEST_CASE(test_insertion_sort_small){
    fixture f;
    
    {
        std::cout << "test_insertion_sort_small: ";
        Timer t;
        InsertionSort(std::begin(f.smallList), std::end(f.smallList));
    }
    
    BOOST_CHECK( isSorted(f.smallList) );
}

BOOST_AUTO_TEST_CASE(test_insertion_sort_huge){
    fixture f;
    
    {
        std::cout << "test_insertion_sort_huge: ";
        Timer t;
        InsertionSort(std::begin(f.hugeList), std::end(f.hugeList));
    }
    
    BOOST_CHECK( isSorted(f.hugeList) );
}

/* *************
 * Select Sort *
 * ************/
BOOST_AUTO_TEST_CASE(test_select_sort_small){
    fixture f;
    
    {
        std::cout << "test_select_sort_small: ";
        Timer t;
        SelectSort(std::begin(f.smallList), std::end(f.smallList));
    }
    
    BOOST_CHECK( isSorted(f.smallList) );
}

BOOST_AUTO_TEST_CASE(test_select_sort_huge){
    fixture f;
    
    {
        std::cout << "test_select_sort_huge: ";
        Timer t;
        SelectSort(std::begin(f.hugeList), std::end(f.hugeList));
    }
    
    BOOST_CHECK( isSorted(f.hugeList) );
}

/* *************
 * Bubble Sort *
 * ************/
BOOST_AUTO_TEST_CASE(test_bubble_sort_small){
    fixture f;
    
    {
        std::cout << "test_bubble_sort_small: ";
        Timer t;
        BubbleSort(std::begin(f.smallList), std::end(f.smallList));
    }
    
    BOOST_CHECK( isSorted(f.smallList) );
}

BOOST_AUTO_TEST_CASE(test_bubble_sort_huge){
    fixture f;
    
    {
        std::cout << "test_bubble_sort_huge: ";
        Timer t;
        BubbleSort(std::begin(f.hugeList), std::end(f.hugeList));
    }
    
    BOOST_CHECK( isSorted(f.hugeList) );
}

/* ************
 * Merge Sort *
 * ***********/
BOOST_AUTO_TEST_CASE(test_merge_sort_small){
    fixture f;
    
    {
        std::cout << "test_merge_sort_small: ";
        Timer t;
        MergeSort(std::begin(f.smallList), std::end(f.smallList));
    }
    
    BOOST_CHECK( isSorted(f.smallList) );
}

BOOST_AUTO_TEST_CASE(test_merge_sort_huge){
    fixture f;
    
    {
        std::cout << "test_merge_sort_huge: ";
        Timer t;
        MergeSort(std::begin(f.hugeList), std::end(f.hugeList));
    }
    
    BOOST_CHECK( isSorted(f.hugeList) );
}

/* ************
 * Quick Sort *
 * ***********/
BOOST_AUTO_TEST_CASE(test_quik_sort_small){
    fixture f;
    
    {
        std::copy(std::begin(f.smallList), std::end(f.smallList), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        std::cout << "test_quick_sort_small: ";
        Timer t;
        QuickSort(std::begin(f.smallList), std::end(f.smallList));
    }
    
    BOOST_CHECK( isSorted(f.smallList) );
}

BOOST_AUTO_TEST_CASE(test_quick_sort_huge){
    fixture f;
    
    {
        std::cout << "test_quick_sort_huge: ";
        Timer t;
        QuickSort(std::begin(f.hugeList), std::end(f.hugeList));
    }
    
    BOOST_CHECK( isSorted(f.hugeList) );
}
