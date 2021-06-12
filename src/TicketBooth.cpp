#pragma once
#include "TicketBooth.hpp"
#include <iostream>

void TicketBooth::createTickets()
{
    ticketsFrequency = ticketsFrequency * 10;
    progress = 0;

    while(!exit)
    {
    // convert to seconds
    for(auto i = 1; i < ticketsFrequency; i++)
    {
        if(exit)
        {
            return;
        }
        progress = ((double)i/ticketsFrequency) * 100; 
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::unique_lock<std::mutex> ticket_lock(mtx);
    for(int i = 0; i < ticketsPerResupply; i++)
    {
        Ticket *ticket = new Ticket();
        tickets.push_back(ticket);
        ticketsLeft++;

    }

    cv.notify_all();
    ticket_lock.unlock();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
}
