#pragma once
#include <condition_variable>
#include <mutex>
#include <vector>

#include "Seat.hpp"

class Attraction
{
    public:
        Attraction(int count); 
        std::condition_variable cv;
        std::mutex m_entry;
        std::mutex m_leave;
        std::vector<Seat*> seats;
        int emptySeats;
        int seatCount;
 
};