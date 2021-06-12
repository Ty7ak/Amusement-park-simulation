#pragma once
#include <mutex>
#include <ncurses.h>
#include <vector>
#include "Visitor.hpp"
#include "TicketBooth.hpp"

class Ui
{
    public:
        int x;
        int y;
        std::mutex m;
        TicketBooth *ticketBooth;
        ParkingLot *parkingLot;
        Attraction *attraction;
        std::vector<Visitor *>  visitors;
        Ui(std::vector<Visitor *> p, ParkingLot *pl, TicketBooth *tb, Attraction *at);
        ~Ui();
        void update();
};