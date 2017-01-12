#ifndef Algorithms_BubbleSort_H_
#define Algorithms_BubbleSort_H_

template<class RandomAccessIterator>
void BubbleSort(RandomAccessIterator start, RandomAccessIterator end){
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
