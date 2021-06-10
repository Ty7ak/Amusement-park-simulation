#pragma once
#include <condition_variable>
#include <mutex>
#include "ParkingLot.hpp"

class Gate
{
    public: 
        std::condition_variable cv;
        std::mutex m;
 
};
