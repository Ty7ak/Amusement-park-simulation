#include "ParkingLot.hpp"

ParkingLot::ParkingLot(int count)
{
    for(int i = 0; i < count; i++)
    {
        ParkingSpot *parkingSpot = new ParkingSpot(i);
        parkingSpots.push_back(parkingSpot);
        emptySpots++;
    }
    spotsCount = count; 
}
