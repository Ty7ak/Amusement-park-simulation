#pragma once
#include <ncurses.h>
#include <iostream>
#include <vector>
#include <thread>

#include "ParkingLot.hpp"
#include "Visitor.hpp"
#include "Ui.hpp"
#include "ParkingSpot.hpp"

int parkTime = 2;
int stuffTime = 5;
int count;

std::vector<Visitor *> visitors;
std::vector<ParkingSpot *> parkingSpots;
bool end = false;

int main(int argc, char **argv)
{
    if (argc < 2) {

        std::cout << "Required args = Number of Visitors" << std::endl;
        return 3;
    }
    else {

        std::string arg1(argv[1]);
        count = std::stoi(arg1);

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
        Visitor *p = new Visitor(i + 1, parkTime, stuffTime, *parkingLot, *gate);
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
    