#pragma once
#include <mutex>

class ParkingSpot
{
    public: 
        std::mutex mtx;
};
