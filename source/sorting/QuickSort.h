#ifndef Algorithms_QuickSort_H_
#define Algorithms_QuickSort_H_

template<class RandomAccessIterator>
void QuickSort(RandomAccessIterator start, RandomAccessIterator end){
//    std::copy(start,end, std::ostream_iterator<int>(std::cout, " "));std::cout << std::endl;

//    std::cout << (start==end) << ": " << std::distance(start, end) << " " << *start << " " << *end << std::endl;
    if(std::distance(start,end) == 1){
        return;
    }
    
    auto pivot = start;
//    std::cout << "pV: " << *pivot << std::endl;
    auto pivotPoint = std::next(start);
    
    for(auto unsorted=std::next(pivot); unsorted != end; ++unsorted){
//        std::cout << "u: " << *unsorted << std::endl;
        if(*unsorted < *pivot){
            std::swap(*unsorted, *pivotPoint);
            ++pivotPoint;
        }
//        std::copy(start,end, std::ostream_iterator<int>(std::cout, " "));std::cout << std::endl;
    }
    std::swap(*pivot, *std::prev(pivotPoint));
//    std::copy(start,end, std::ostream_iterator<int>(std::cout, " "));std::cout << std::endl;
    
    QuickSort(start, pivotPoint);
    QuickSort(pivotPoint, end);
}

#endif
