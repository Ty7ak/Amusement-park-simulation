#pragma once
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include "Ticket.hpp"

class TicketBooth
{
    public:
        std::vector<Ticket*> tickets;
        std::atomic<int> ticketsLeft{0};
        std::thread t;
        std::condition_variable cv;
        std::mutex mtx;
        std::atomic<int> progress {0};
        int ticketsPerResupply;
        int ticketsFrequency;
        bool *exit;

        TicketBooth(int i, int f, bool *ext): ticketsPerResupply(i), ticketsFrequency(f), exit(ext), t(&TicketBooth::createTickets, this){};

        void createTickets();

};