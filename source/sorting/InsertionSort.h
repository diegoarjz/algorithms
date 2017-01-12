#ifndef Algorithms_InsertionSort_H_
#define Algorithms_InsertionSort_H_

#include <iostream>

/**
 * Sorts the iterator range using Insertion Sort.
 */
template<class RandomAccessIterator>
void InsertionSort(RandomAccessIterator start, RandomAccessIterator end){
    
    auto sortedIter=start;
    auto reverseEnd = std::reverse_iterator<RandomAccessIterator>(start);

    for(auto unsortedIter = std::next(sortedIter); unsortedIter!=end; ++unsortedIter){
        auto unsortedValue = *unsortedIter;
        
        auto reverseIter = std::reverse_iterator<RandomAccessIterator>(std::next(sortedIter));
        
        // Find the best position for the item
        for(/**/; reverseIter!=reverseEnd && *reverseIter > unsortedValue; ++reverseIter){
            //std::swap(*std::prev(reverseIter), *reverseIter);
            *std::prev(reverseIter) = *reverseIter;
        }
        *std::prev(reverseIter) = unsortedValue;
        
        sortedIter++;
    }
}

#endif
