#pragma once
#include <mutex>
#include <atomic>

class ParkingSpot
{
    public: 
        std::atomic<int> id;
        std::mutex mtx;
        ParkingSpot(int i): id(i){};
};
