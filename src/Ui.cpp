#pragma once
#include "Ui.hpp"

Ui::Ui(std::vector<Visitor *> p, ParkingLot *pl, TicketBooth *tb)
{
    visitors = p;
    ticketBooth = tb;
    parkingLot = pl;
    initscr();
    noecho();
    raw();
    nodelay(stdscr, true);
    start_color();
    use_default_colors();
    curs_set(0);
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_CYAN, -1);
    init_pair(3, COLOR_GREEN, -1);
    init_pair(4, COLOR_MAGENTA, -1);
    init_pair(5, COLOR_WHITE, -1);
}

Ui::~Ui()
{
    endwin();
}

void Ui::update()
{
    while(true)
    {
        int c = getch();
        if(c == 113)
        {   
            ticketBooth->exit = true;
            for(auto p : visitors)
            {
                p->exit = true;
            }
            return;
        }

        attron(COLOR_PAIR(5));
        mvprintw(0, 18, "|---------------------------|");
        mvprintw(1, 18, "|    Maciej Tylak 248884    |");
        mvprintw(2, 18, "|---------------------------|");
        mvprintw(1, 60, "Press q to exit");  

        mvprintw(3, 60, "Parking spots left %3d/%3d", parkingLot->emptySpots, parkingLot->spotsCount);
        mvprintw(4, 60, "Tickets left %d", ticketBooth->ticketsLeft.load());
        attroff(COLOR_PAIR(5));
        refresh();

        clrtoeol();

        for(auto p : visitors)
        {
            move(4 + p->id, 0);
            clrtoeol();
            attron(COLOR_PAIR((int)p->action));
            if(p->action == VisitorAction::waitingForSpots)
            {
                attron(COLOR_PAIR(1));
                mvprintw(4 + p->id, 0, "Visitor %d is waiting for spots", p->id);
                attroff(COLOR_PAIR(1));
                clrtoeol();
            }

            else if(p->action == VisitorAction::Parking)
            {
                attron(COLOR_PAIR(3));
                mvprintw(4 + p->id, 0,"Visitor %d is parking", p->id);
                mvprintw(4 + p->id, 50 ," progress: %d %%", p->progress);
                attroff(COLOR_PAIR(3));
                clrtoeol();
            }

            else if(p->action == VisitorAction::waitingForTickets)
            {
                attron(COLOR_PAIR(1));
                mvprintw(4 + p->id, 0,"Visitor %d is waiting for a ticket", p->id);
                mvprintw(4 + p->id, 70,"Rides left: %d", p->amountOfRides);
                attroff(COLOR_PAIR(1));
                clrtoeol();
            }

            else if(p->action == VisitorAction::gettingTickets)
            {
                attron(COLOR_PAIR(3));
                mvprintw(4 + p->id, 0,"Visitor %d is getting a ticket", p->id);
                mvprintw(4 + p->id, 50 ," progress: %d %%", p->progress);
                mvprintw(4 + p->id, 70,"Rides left: %d", p->amountOfRides);
                attroff(COLOR_PAIR(3));
                clrtoeol();
            }

            else if(p->action == VisitorAction::waitingForAttraction)
            {
                attron(COLOR_PAIR(1));
                mvprintw(4 + p->id, 0,"Visitor %d is waiting for seats", p->id);
                mvprintw(4 + p->id, 70,"Rides left: %d", p->amountOfRides);
                attroff(COLOR_PAIR(1));
                clrtoeol();
            }

            else if(p->action == VisitorAction::ridingAttraction)
            {
                attron(COLOR_PAIR(2));
                mvprintw(4 + p->id, 0,"Visitor %d is having fun!", p->id);
                mvprintw(4 + p->id, 40, "Spot #%d", p->parkingSpot->id+1);
                mvprintw(4 + p->id, 50 ," progress: %d %%", p->progress);
                mvprintw(4 + p->id, 70,"Rides left: %d", p->amountOfRides);
                attroff(COLOR_PAIR(2));
                clrtoeol();
            }
            else if(p->action == VisitorAction::Leaving)
            {
                attron(COLOR_PAIR(4));
                mvprintw(4 + p->id, 0,"Visitor %d is leaving Parking", p->id);
                mvprintw(4 + p->id, 50 ," progress: %d %%", p->progress);
                attroff(COLOR_PAIR(4));
                clrtoeol();
                if(p->progress)
                {
                    attron(COLOR_PAIR(4));
                    mvprintw(4 + p->id, 0,"Visitor %d has left the park", p->id);
                    attroff(COLOR_PAIR(4));
                    clrtoeol();    
                }
            }                 
            refresh();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}