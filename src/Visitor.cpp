#include "Visitor.hpp"
#include "ParkingSpot.hpp"

#include <iostream>

void Visitor::live()
{
    while(!exit.load())
    {
        waitParking();
        park(parkTime);

        while(amountOfRides > 0 && !exit.load())
        {
            waitTickets();
            getTickets(ticketTime);
            waitAttraction();
            rideAttraction(rideTime);
        }

        leaveParking(parkTime);
        action = VisitorAction::Left;
        exit=true;
    }
}

void Visitor::waitParking() 
{
    action = VisitorAction::waitingForSpots;

    amountOfRides = std::uniform_int_distribution<int>(1, 3)(rng);

    std::unique_lock<std::mutex> wait_lock(gate.m_entry);

    while(exit.load()!=true)
    {
        gate.cv.wait(wait_lock, [&]() {return parkingLot.emptySpots.load() > 0;});
        return;
        
    }

}

void Visitor::park(float time)
{
    std::unique_lock<std::mutex> parked_lock(gate.m_entry);

    for(ParkingSpot* spot : parkingLot.parkingSpots)
    {        
        if(spot->mtx.try_lock())
        {
        parkingSpot = spot;
        parkingLot.emptySpots--;
        break;
        }
    }

    action = VisitorAction::Parking;
    int part = std::uniform_int_distribution<int>(int(10*0.8*time), int(10*1.2*time))(rng);
    for(auto i = 1; i <= part; i++)
    {
        if(exit.load())
        {
            return;
        }

        progress = ((double)i/part) * 100; 

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

}

void Visitor::waitTickets()
{
    action = VisitorAction::waitingForTickets;
        
    std::unique_lock<std::mutex> wait_lock(booth.mtx);
    while(exit.load()!=true)
    {
        booth.cv.wait(wait_lock, [&]() {return booth.ticketsLeft.load() > 0;});
        return;
        
    }

}    
    

void Visitor::getTickets(float time)
{
    std::unique_lock<std::mutex> get_lock(booth.mtx);
    booth.ticketsLeft--;

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
        if(exit.load())
        {
            return;
        }

        progress = ((double)i/part) * 100; 

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

}

void Visitor::waitAttraction()
{
    action = VisitorAction::waitingForAttraction;

    std::unique_lock<std::mutex> wait_lock(attraction.m_entry);
    while(exit.load()!=true)
    {
        attraction.cv.wait(wait_lock, [&]() {return attraction.emptySeats.load() > 0;});
        return;
        
    }    
}



void Visitor::rideAttraction(float time)
{
    for(Seat* seat : attraction.seats)
    {        
        if(seat->mtx.try_lock())
        {
        ownSeat = seat;
        attraction.emptySeats--; 
        break;
        }
    }

    action = VisitorAction::ridingAttraction;
    int part = std::uniform_int_distribution<int>(int(10*0.8*time), int(10*1.2*time))(rng);
    for(auto i = 1; i < part; i++)
    {
        if(exit.load())
        {
            return;
        }

        progress = ((double)i/part) * 100; 

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    amountOfRides--;
    ownSeat->mtx.unlock();
    attraction.emptySeats++;
    attraction.cv.notify_one();
}

void Visitor::leaveParking(float time)
{
    action = VisitorAction::Leaving;
    std::unique_lock<std::mutex> wait_lock(gate.m_leave);
    
    int part = std::uniform_int_distribution<int>(int(10*0.8*time), int(10*1.2*time))(rng);
    for(auto i = 1; i <= part; i++)
    {
        if(exit.load())
        {
            return;
        }

        progress = ((double)i/part) * 100; 

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    
    parkingSpot->mtx.unlock();
    parkingLot.emptySpots++;
    gate.cv.notify_one();
}

