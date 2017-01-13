#ifndef Algorithms_SelectSort_H_
#define Algorithms_SelectSort_H_

/**
 * Sorts the items in the given range using Select Sort.
 *
 * Worst Case: O(n^2)
 * Average Case: O(n^2)
 * Best Case: O(n^2)
 */
template<class BidirectionalIterator>
void SelectSort(BidirectionalIterator start, BidirectionalIterator end){
    for(auto sorted=start; sorted!=end; ++sorted){
        
        auto min = sorted;
        for(auto unsorted = std::next(sorted); unsorted != end; ++unsorted){
            if(*unsorted < *min){
                min = unsorted;
            }
        }
        
        std::swap(*min, *sorted);
    }
}

#endif
