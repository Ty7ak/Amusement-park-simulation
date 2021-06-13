#include <ncurses.h>
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

#include "ParkingLot.hpp"
#include "Visitor.hpp"
#include "Ui.hpp"
#include "ParkingSpot.hpp"
#include "Attraction.hpp"

int count;
int parkingSpotCount = 10;
float parkTime = 0.5;
float rideTime = 3.0;
float ticketTime = 0.5;

int ticketAmount = 4;
int ticketFrequency = 2;

int seatCount = 5;

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

    std::atomic_bool *exit = new std::atomic_bool{false};
    ParkingLot *parkingLot = new ParkingLot(parkingSpotCount);
    TicketBooth *ticketBooth = new TicketBooth(ticketAmount, ticketFrequency, *exit);
    Gate *gate = new Gate();
    Attraction *attraction = new Attraction(seatCount);
    
    for(auto i = 0; i < count ; i++)
    {
        Visitor *p = new Visitor(i + 1, parkTime, rideTime, ticketTime, *parkingLot, *gate, *ticketBooth, *attraction, *exit);
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
    