#ifndef Algorithms_MergeSort_H_
#define Algorithms_MergeSort_H_

/**
 * Sorts the items in the range using Merge Sort.
 *
 * Worst Case: O(n.Log(n))
 * Average Case: O(n.Log(n))
 * Best Case: O(n.Log(n))
 */
template<class BidirectionalIterator>
void MergeSort(BidirectionalIterator start, BidirectionalIterator end){
    auto size = std::distance(start, end);
    
    if(size == 1){
        return;
    }
    
    auto middle = start;
    std::advance(middle, size*0.5);
    
    MergeSort(start, middle);
    MergeSort(middle, end);
    
    auto leftStartIter = start;
    auto rightStartIter = middle;
    
    std::vector<typename BidirectionalIterator::value_type> container(size);
    auto inserter = std::back_inserter(container);
    
    while(leftStartIter != middle && rightStartIter != end){
        if( *leftStartIter < *rightStartIter ){
            inserter = *leftStartIter;
            ++leftStartIter;
        }
        else{
            inserter = *rightStartIter;
            ++rightStartIter;
        }
    }
    
    while(leftStartIter != middle){
        inserter = *leftStartIter;
        ++leftStartIter;
    }
    
    while(rightStartIter != end){
        inserter = *rightStartIter;
        ++rightStartIter;
    }
    
    auto containerIter = std::begin(container);
    for(auto iter=start; iter!=end; ++iter, ++containerIter){
        *iter = *containerIter;
    }
}

#endif
