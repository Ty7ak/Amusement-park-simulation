#pragma once
#include <mutex>

class Seat
{
    public: 
        std::mutex mtx;
};
