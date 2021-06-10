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
    Dining,
    waitingForSpots   
};

class Visitor
{
    public:
        int id;
        int dineTime;
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

        Visitor(int i, int et, ParkingLot &lot, Gate &g): id(i), dineTime(et), parkingLot(lot), gate(g), t(&Visitor::live, this) {};
        void live();
        void park(int dineTime);
        void waitParking();
    
};