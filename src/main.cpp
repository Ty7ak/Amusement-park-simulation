#include <ncurses.h>
#include <iostream>
#include <vector>
#include <thread>

#include "ParkingLot.hpp"
#include "Visitor.hpp"
#include "Ui.hpp"
#include "ParkingSpot.hpp"
#include "Attraction.hpp"

int count;
int parkingSpotCount = 10;
float parkTime = 1.0;
float rideTime = 3.0;
float ticketTime = 1.0;

int ticketAmount = 2;
int ticketFrequency = 1;

int seatCount = 2;

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

    ParkingLot *parkingLot = new ParkingLot(parkingSpotCount);
    TicketBooth *ticketBooth = new TicketBooth(ticketAmount, ticketFrequency);
    Gate *gate = new Gate();
    Attraction *attraction = new Attraction(seatCount);
    
    for(auto i = 0; i < count ; i++)
    {
        Visitor *p = new Visitor(i + 1, parkTime, rideTime, ticketTime, *parkingLot, *gate, *ticketBooth, *attraction);
        visitors.push_back(p);
    }
    std::thread tu(&Ui::update, new Ui(visitors, parkingLot, ticketBooth, attraction));

    tu.join();

    for(auto p : visitors)
    {
        p->t.join();
    }

    ticketBooth->t.join();

    endwin(); 

    return 0;
}
    