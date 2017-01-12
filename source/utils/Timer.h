#ifndef Algorithms_Timer_H_
#define Algorithms_Timer_H_

#include <chrono>

class Timer{
public:
    Timer();
    ~Timer();
private:
    std::chrono::time_point<std::chrono::system_clock> mStart;
};

#endif
