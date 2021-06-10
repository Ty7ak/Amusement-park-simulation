#pragma once
#include <random>
#include <thread>
#include <vector>
#include <condition_variable>

#include "ParkingSpot.hpp"
#include "ParkingLot.hpp"
#include "Gate.hpp"

enum class VisitorAction
{
    Thinking,
    Dining,
    waitingForSpots   
};

class Visitor
{
    public:
        int id;
        int thinkTime;
        int dineTime;
        ParkingSpot &parkingSpot;
        std::thread t;
        std::mt19937 rng{std::random_device{}()};
        VisitorAction action;
        int progress = 0;
        bool hasParking = false;
        bool exit = false;

        Visitor(int i, int tt, int et, ParkingSpot &spot): id(i), thinkTime(tt), dineTime(et), parkingSpot(spot), t(&Visitor::live, this) {};
        void live();
        void park(int dineTime);
        void wait();
        void think(int thinkTime);
    
};