#ifndef Algorithms_BubbleSort_H_
#define Algorithms_BubbleSort_H_

/**
 * Sorts the range between the iterators using Bubble Sort.
 *
 * Worst Case: O(n^2)
 * Average Case: O(n^2)
 * Best Case: O(n)
 */
template<class BidirectionalIterator>
void BubbleSort(BidirectionalIterator start, BidirectionalIterator end){
    bool swapped = false;
    auto lastUnsorted = end;
    do{
        swapped = false;
        
        for(auto right = std::next(start); right!=lastUnsorted; ++right){
            auto left = std::prev(right);
            
            if(*left > *right){
                std::swap(*left,*right);
                swapped = true;
            }
        }
        lastUnsorted--;
    } while(swapped);
}

#endif
