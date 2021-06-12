#pragma once
#include <vector>
#include <atomic>

#include "ParkingSpot.hpp"

class ParkingLot
{
    public:
        std::vector<ParkingSpot*> parkingSpots;
        ParkingLot(int count);
        std::atomic<int> emptySpots {0};
        std::atomic<int> spotsCount {0};
};