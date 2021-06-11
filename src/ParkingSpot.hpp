#pragma once
#include <mutex>

class ParkingSpot
{
    public: 
        int id;
        std::mutex mtx;
        ParkingSpot(int i): id(i){};
};
