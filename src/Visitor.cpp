#pragma once
#include "Visitor.hpp"
#include "ParkingSpot.hpp"

void Visitor::live()
{
    while(!exit)
    {
        waitParking();
        park(parkTime);

        while(amountOfRides > 0)
        {
            waitTickets();
            getTickets(parkTime);
            waitAttraction();
            rideAttraction(stuffTime);
        }

        leaveParking(parkTime);
        exit=true;
    }
}

void Visitor::waitParking()
{
    action = VisitorAction::waitingForSpots;

    amountOfRides = std::uniform_int_distribution<int>(1, 3)(rng);

    while (!exit)
    {
        std::unique_lock<std::mutex> wait_lock(gate.m_entry);
        gate.cv.wait(wait_lock, [&]() {return parkingLot.emptySpots > 0;});

        parkingLot.emptySpots--;
        break;    
    }
    
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

void Visitor::getTickets(int time)
{
    std::unique_lock<std::mutex> parked_lock(booth.mtx);

    for(Ticket* ticket : booth.tickets)
    {        
        if(ticket->mtx.try_lock())
        {
        ownTicket = ticket;
        break;
        }
    }

    action = VisitorAction::gettingTickets;
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

void Visitor::waitAttraction()
{
    action = VisitorAction::waitingForAttraction;
    
    if(exit)
    {
        return;
    }

    
    std::unique_lock<std::mutex> wait_lock(attraction.m_entry);
    attraction.cv.wait(wait_lock, [&]() {return attraction.emptySeats > 0;});

    attraction.emptySeats--; 
}



void Visitor::rideAttraction(int time)
{
    for(Seat* seat : attraction.seats)
    {        
        if(seat->mtx.try_lock())
        {
        ownSeat = seat;
        break;
        }
    }

    action = VisitorAction::ridingAttraction;
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

    amountOfRides--;
    ownSeat->mtx.unlock();
    attraction.emptySeats++;
    attraction.cv.notify_all();
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

