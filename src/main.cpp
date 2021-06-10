#pragma once
#include <ncurses.h>
#include <iostream>
#include <vector>
#include <thread>

#include "ParkingLot.hpp"
#include "Visitor.hpp"
#include "Ui.hpp"
#include "ParkingSpot.hpp"

int count, thinkTime, dineTime;

std::vector<Visitor *> visitors;
std::vector<ParkingSpot *> parkingSpots;
bool end = false;

int main(int argc, char **argv)
{
    if (argc < 3) {

        std::cout << "Required args = Number of Visitors | Eating time" << std::endl;
        return 3;
    }
    else {

        std::string arg1(argv[1]);
        count = std::stoi(arg1);

        std::string arg2(argv[2]);
        dineTime = std::stoi(arg2);
    }

    for(auto i = 0; i < count; i++)
    {
        ParkingSpot *parkingSpot = new ParkingSpot();
        parkingSpots.push_back(parkingSpot);
    }

    ParkingLot *parkingLot = new ParkingLot(count);

    Gate *gate = new Gate();
    
    for(auto i = 0; i < count+2 ; i++)
    {
        Visitor *p = new Visitor(i + 1, dineTime, *parkingLot, *gate);
        visitors.push_back(p);
    }

    std::thread tu(&Ui::update, new Ui(visitors));

    tu.join();

    for(auto p : visitors)
    {
        p->t.join();
    }
    endwin(); 

    return 0;
}
    