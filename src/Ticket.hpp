#pragma once
#include <mutex>

class Ticket
{
    public: 
        std::mutex mtx;
};
