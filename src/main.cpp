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
    if (argc < 4) {

        std::cout << "Required args = Number of Visitors | Thinking Time | Eating time" << std::endl;
        return 3;
    }
    else {

        std::string arg1(argv[1]);
        count = std::stoi(arg1);

        std::string arg2(argv[2]);
        thinkTime = std::stoi(arg2);

        std::string arg3(argv[3]);
        dineTime = std::stoi(arg3);
    }

    for(auto i = 0; i < count; i++)
    {
        ParkingSpot *parkingSpot = new ParkingSpot();
        parkingSpots.push_back(parkingSpot);
    }

    ParkingLot *parkingLot = new ParkingLot(count);

    Gate *gate = new Gate(*parkingLot);
    
    for(auto i = 0; i < count ; i++)
    {
        Visitor *p = new Visitor(i + 1, thinkTime, dineTime, *parkingLot->parkingSpots[i]);
        visitors.push_back(p);
    }

    std::thread tu(&Ui::update, new Ui(visitors));

    tu.join();

    for(auto p : visitors)
    {
        p->t.join();
    }
    endwin(); 

    std::cout << "test";

    return 0;
}
    