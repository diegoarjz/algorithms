#include "Timer.h"

#include <iostream>

Timer::Timer(){
    mStart = std::chrono::system_clock::now();
}

Timer::~Timer(){
    std::chrono::duration<double> diff = std::chrono::system_clock::now()-mStart;
    std::cout << "Elapsed time: " << diff.count() << "s" << std::endl;
}
