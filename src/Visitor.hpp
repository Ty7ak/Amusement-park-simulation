#pragma once
#include <random>
#include <thread>
#include <vector>
#include <condition_variable>
#include <mutex>

#include "ParkingSpot.hpp"
#include "ParkingLot.hpp"
#include "Gate.hpp"

enum class VisitorAction
{
    Parking,
    waitingForSpots,
    doingStuff,
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
        ParkingSpot *parkingSpot;
        std::condition_variable cv;
        std::thread t;
        std::mt19937 rng{std::random_device{}()};
        VisitorAction action;
        int progress = 0;
        bool hasParking = false;
        bool exit = false;

        Visitor(int i, int pt, int st, ParkingLot &lot, Gate &g): id(i), parkTime(pt), stuffTime(st), parkingLot(lot), gate(g), t(&Visitor::live, this) {};
        void live();
        void park(int parkTime);
        void waitParking();
        void doStuff(int stuffTime);
        void leaveParking(int parkTime);
    
};