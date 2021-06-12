#pragma once
#include <random>
#include <thread>
#include <vector>
#include <condition_variable>
#include <mutex>

#include "ParkingSpot.hpp"
#include "ParkingLot.hpp"
#include "Gate.hpp"
#include "TicketBooth.hpp"

enum class VisitorAction
{
    Parking,
    waitingForSpots,
    waitingForTickets,
    gettingTickets,
    ridingAttraction,
    Leaving   
};

class Visitor
{
    public:
        int id;
        int parkTime;
        int stuffTime;
        ParkingLot &parkingLot;
        Gate &gate;
        TicketBooth &booth;
        ParkingSpot *parkingSpot;
        Ticket *ownTicket;
        std::condition_variable cv;
        std::thread t;
        std::mt19937 rng{std::random_device{}()};
        VisitorAction action;
        int progress = 0;
        bool hasParking = false;
        bool exit = false;

        Visitor(int i, int pt, int st, ParkingLot &lot, Gate &g, TicketBooth &tb): id(i), parkTime(pt), stuffTime(st), parkingLot(lot), gate(g), booth(tb), t(&Visitor::live, this) {};
        void live();
        void park(int parkTime);
        void waitParking();
        void waitTickets();
        void rideAttraction(int stuffTime);
        void getTickets(int parkTime);
        void leaveParking(int parkTime);
    
};