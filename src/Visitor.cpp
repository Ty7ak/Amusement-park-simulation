#pragma once
#include "Visitor.hpp"
#include "ParkingSpot.hpp"

void Visitor::live()
{
    while(!exit)
    {
        think(thinkTime);
        wait();
        park(dineTime);
    }
}

void Visitor::think(int time)
{
    action = VisitorAction::Thinking;
    int part = std::uniform_int_distribution<int>(int(10*0.8*time), int(10*1.2*time))(rng);
    for(auto i = 1; i < part; i++)
    {
        if(exit)
        {
            return;
        }

        progress = ((double)i/part) * 100; 

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Visitor::park(int time)
{
    std::unique_lock<std::mutex> park_lock(parkingSpot.mtx);
 
    action = VisitorAction::Dining;
    int part = std::uniform_int_distribution<int>(int(10*0.8*time), int(10*1.2*time))(rng);
    for(auto i = 1; i < part; i++)
    {
        if(exit)
        {
            return;
        }

        progress = ((double)i/part) * 100; 

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    park_lock.unlock();
    hasParking = false;
}

void Visitor::wait()
{
    action = VisitorAction::waitingForSpots;
    if(exit)
    {
        return;
    }
}

