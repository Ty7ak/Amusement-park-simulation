#pragma once
#include <vector>
#include <mutex>
#include <condition_variable>

#include "Gate.hpp"

Gate::Gate(ParkingLot &parkingLot)
{
    emptySpots = parkingLot.parkingSpots.size();
}