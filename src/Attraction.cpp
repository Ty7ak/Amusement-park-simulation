#pragma once
#include "Attraction.hpp"
#include "Seat.hpp"

Attraction::Attraction(int count)
{
    for(int i = 0; i < count; i++)
    {
        Seat *seat = new Seat();
        seats.push_back(seat);
        emptySeats++;
    }
    seatCount = count; 
}