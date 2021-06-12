#pragma once
#include <condition_variable>
#include <mutex>
#include <vector>
#include <atomic>

#include "Seat.hpp"

class Attraction
{
    public:
        Attraction(int count); 
        std::condition_variable cv;
        std::mutex m_entry;
        std::mutex m_leave;
        std::vector<Seat*> seats;
        std::atomic<int> emptySeats;
        std::atomic<int> seatCount;
 
};