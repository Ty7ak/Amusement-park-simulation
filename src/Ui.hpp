#pragma once
#include <mutex>
#include <ncurses.h>
#include <vector>
#include "Visitor.hpp"

class Ui
{
    public:
        int x;
        int y;
        std::mutex m;
        std::vector<Visitor *>  visitors;
        Ui(std::vector<Visitor *> p);
        ~Ui();
        void update();
};