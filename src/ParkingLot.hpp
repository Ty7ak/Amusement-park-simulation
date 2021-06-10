#pragma once
#include <vector>

#include "ParkingSpot.hpp"

class ParkingLot
{
    public:
        std::vector<ParkingSpot*> parkingSpots;
        ParkingLot(int count);
};