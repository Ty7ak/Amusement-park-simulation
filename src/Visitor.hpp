#pragma once
#include <random>
#include <thread>
#include <vector>

#include "ParkingSpot.hpp"
#include "ParkingLot.hpp"
#include "Gate.hpp"
#include "TicketBooth.hpp"
#include "Attraction.hpp"

enum class VisitorAction
{
    Parking,
    waitingForSpots,
    waitingForTickets,
    gettingTickets,
    waitingForAttraction,
    ridingAttraction,
    Leaving   
};

class Visitor
{
    public:
        std::atomic<int> id;
        int parkTime;
        int rideTime;
        int amountOfRides;

        ParkingLot &parkingLot;
        Gate &gate;
        TicketBooth &booth;
        Attraction &attraction;

        ParkingSpot *parkingSpot;
        Ticket *ownTicket;
        Seat *ownSeat;

        std::thread t;
        std::mt19937 rng{std::random_device{}()};
        VisitorAction action;
        std::atomic<int> progress {0};

        bool exit = false;

        Visitor(int i, int pt, int st, ParkingLot &lot, Gate &g, TicketBooth &tb, Attraction &at): 
        id(i), parkTime(pt), rideTime(st), parkingLot(lot), gate(g), booth(tb), attraction(at), t(&Visitor::live, this) {};

        void live();
        void park(int parkTime);
        void waitParking();
        void waitTickets();
        void rideAttraction(int rideTime);
        void waitAttraction();
        void getTickets(int parkTime);
        void leaveParking(int parkTime);
    
};