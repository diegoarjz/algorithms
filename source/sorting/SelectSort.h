#ifndef Algorithms_SelectSort_H_
#define Algorithms_SelectSort_H_

template<class RandomAccessIterator>
void SelectSort(RandomAccessIterator start, RandomAccessIterator end){
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
