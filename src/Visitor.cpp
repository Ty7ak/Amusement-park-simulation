#pragma once
#include "Visitor.hpp"
#include "ParkingSpot.hpp"

void Visitor::live()
{
    while(!exit)
    {
        waitParking();
        park(parkTime);
        waitTickets();
        doStuff(stuffTime);
        leaveParking(parkTime);
        exit=true;
    }
}

void Visitor::waitParking()
{
    action = VisitorAction::waitingForSpots;
    
    if(exit)
    {
        return;
    }

    
    std::unique_lock<std::mutex> wait_lock(gate.m_entry);
    gate.cv.wait(wait_lock, [&]() {return parkingLot.emptySpots > 0;});

    parkingLot.emptySpots--;
    
}

void Visitor::park(int time)
{
    std::unique_lock<std::mutex> parked_lock(gate.m_entry);

    for(ParkingSpot* spot : parkingLot.parkingSpots)
    {        
        if(spot->mtx.try_lock())
        {
        parkingSpot = spot;
        break;
        }
    }

    action = VisitorAction::Parking;
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

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

}

void Visitor::waitTickets()
{
    action = VisitorAction::waitingForTickets;
    
    if(exit)
    {
        return;
    }

    
    std::unique_lock<std::mutex> wait_lock(booth.mtx);
    booth.cv.wait(wait_lock, [&]() {return booth.ticketsLeft > 0;});

    booth.ticketsLeft--;
    
}

void Visitor::doStuff(int time)
{
    action = VisitorAction::doingStuff;
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

void Visitor::leaveParking(int time)
{
    std::unique_lock<std::mutex> wait_lock(gate.m_leave);
    
    action = VisitorAction::Leaving;
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

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    parkingSpot->mtx.unlock();
    parkingLot.emptySpots++;
    gate.cv.notify_all();
}

