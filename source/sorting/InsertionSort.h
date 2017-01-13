#ifndef Algorithms_InsertionSort_H_
#define Algorithms_InsertionSort_H_

/**
 * Sorts the iterator range using Insertion Sort.
 *
 * Worst Case: O(n^2)
 * Average Case: O(n^2)
 * Best Case: O(n)
 */
template<class BidirectionalIterator>
void InsertionSort(BidirectionalIterator start, BidirectionalIterator end){
    
    auto sortedIter=start;
    auto reverseEnd = std::reverse_iterator<BidirectionalIterator>(start);

    for(auto unsortedIter = std::next(sortedIter); unsortedIter!=end; ++unsortedIter){
        auto unsortedValue = *unsortedIter;
        
        auto reverseIter = std::reverse_iterator<BidirectionalIterator>(std::next(sortedIter));
        
        // Find the best position for the item
        for(/**/; reverseIter!=reverseEnd && *reverseIter > unsortedValue; ++reverseIter){
            *std::prev(reverseIter) = *reverseIter;
        }
        *std::prev(reverseIter) = unsortedValue;
        
        sortedIter++;
    }
}

#endif
