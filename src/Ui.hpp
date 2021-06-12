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
        std::vector<Visitor *>  visitors;
        Ui(std::vector<Visitor *> p, ParkingLot *pl, TicketBooth *tb);
        ~Ui();
        void update();
};