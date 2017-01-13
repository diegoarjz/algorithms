#ifndef Algorithms_QuickSort_H_
#define Algorithms_QuickSort_H_

/**
 * Sorts the items in the range using Quick Sort.
 *
 * Worst Case: O(n)
 * Average Case: O(n.Log(n))
 * Best Case: O(n.Log(n))
 */
template<class BidirectionalIterator>
void QuickSort(BidirectionalIterator start, BidirectionalIterator end){

    if(std::distance(start,end) == 1){
        return;
    }
    
    auto pivot = start;
    auto pivotPoint = std::next(start);
    
    for(auto unsorted=std::next(pivot); unsorted != end; ++unsorted){
        if(*unsorted < *pivot){
            std::swap(*unsorted, *pivotPoint);
            ++pivotPoint;
        }
    }
    std::swap(*pivot, *std::prev(pivotPoint));
    
    QuickSort(start, pivotPoint);
    QuickSort(pivotPoint, end);
}

#endif
