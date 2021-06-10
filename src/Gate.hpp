#pragma once
#include <condition_variable>
#include <mutex>
#include "ParkingLot.hpp"

class Gate
{
    public: 
        std::condition_variable cv_leftParking;
        std::condition_variable cv_enteredParking;
        std::mutex queueMutex;
        int emptySpots;

        Gate(ParkingLot &parkingLot);

};
