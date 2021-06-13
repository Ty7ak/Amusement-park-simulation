#include "Ui.hpp"

Ui::Ui(std::vector<Visitor *> p, ParkingLot *pl, TicketBooth *tb, Attraction *at)
{
    visitors = p;
    ticketBooth = tb;
    parkingLot = pl;
    attraction = at;
    initscr();
    noecho();
    raw();
    nodelay(stdscr, true);
    start_color();
    use_default_colors();
    curs_set(0);
    // lines
    init_pair(1, COLOR_WHITE, -1);
    // waiting
    init_pair(2, COLOR_RED, -1);
    // entering/getting tickets
    init_pair(3, COLOR_GREEN, -1);
    // riding
    init_pair(4, COLOR_MAGENTA, -1);
    // leaving
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

        attron(COLOR_PAIR(1));
        
        mvprintw(0, 5, "Parking queue");

        mvvline(0, 21, 0, 50);

        mvprintw(0, 24, "Parking");
        mvprintw(1, 24, "[%2d/%2d]", parkingLot->spotsCount.load()-parkingLot->emptySpots.load(), parkingLot->spotsCount.load());

        mvvline(0, 34, 0, 50);

        mvprintw(0, 37, "Ticket booth queue");
        mvprintw(1, 39, "Tickets:%2d", ticketBooth->ticketsLeft.load());

        mvvline(0, 58, 0, 50);

        mvprintw(0, 61, "Ticket booth");
        attron(COLOR_PAIR(3));        
        mvprintw(1, 65, "[%2d%%]", ticketBooth->progress.load());
        attroff(COLOR_PAIR(3));

        mvvline(0, 76, 0, 50);

        mvprintw(0, 79, "Attraction queue");
        mvvline(0, 98, 0, 50);

        mvprintw(0, 101, "Attraction");
        mvprintw(1, 102, "Seats:%2d", attraction->emptySeats.load());

        mvvline(0, 114, 0, 50);

        mvprintw(0, 117, "Leaving");

        mvhline(2, 0, 0, 140);

        attroff(COLOR_PAIR(1));
        refresh();
        
        for(auto p : visitors)
        {
            move(3+p->id, 0);
            clrtoeol();
            if(p->action == VisitorAction::waitingForSpots)
            {
                attron(COLOR_PAIR(2));
                mvprintw(3+p->id.load(), 8, "[%2d]", p->id.load());
                attroff(COLOR_PAIR(2));
                clrtoeol();
            }

            else if(p->action == VisitorAction::Parking)
            {
                attron(COLOR_PAIR(3));
                mvprintw(3+p->parkingSpot->id.load()+1, 25,"[%2d]", p->id.load());
                mvprintw(3+p->parkingSpot->id.load()+1, 30,"%d%%", p->progress.load());
                attroff(COLOR_PAIR(3));
                clrtoeol();
            }

            else if(p->action == VisitorAction::waitingForTickets)
            {
                attron(COLOR_PAIR(2));
                mvprintw(3+p->id.load(), 42 ,"[%2d]", p->id.load());
                attroff(COLOR_PAIR(2));
                clrtoeol();
            }

            else if(p->action == VisitorAction::gettingTickets)
            {
                attron(COLOR_PAIR(3));
                mvprintw(3+p->id.load(), 63,"[%2d]", p->id.load());
                mvprintw(3+p->id.load(), 68 ,"%d%%", p->progress.load());
                attroff(COLOR_PAIR(3));
                clrtoeol();
            }

            else if(p->action == VisitorAction::waitingForAttraction)
            {
                attron(COLOR_PAIR(2));
                mvprintw(3+p->id.load(), 83,"[%2d]", p->id.load());
                //mvprintw(3+wtAmount, 86,"Rides left: %d", p->amountOfRides.load());
                attroff(COLOR_PAIR(2));
                clrtoeol();
            }

            else if(p->action == VisitorAction::ridingAttraction)
            {
                attron(COLOR_PAIR(4));
                mvprintw(3+p->id.load(), 102,"[%2d]", p->id.load());
                mvprintw(3+p->id.load(), 107,"%d%%", p->progress.load());
                //mvprintw(3+p->id.load(), 70,"Rides left: %d", p->amountOfRides.load());
                attroff(COLOR_PAIR(4));
                clrtoeol();
            }
            else if(p->action == VisitorAction::Leaving)
            {
                attron(COLOR_PAIR(5));
                mvprintw(3+p->id.load(), 117,"[%2d]", p->id.load());
                mvprintw(3+p->id.load(), 123,"%d%%", p->progress.load());
                attroff(COLOR_PAIR(5));
                clrtoeol();
            }
                
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}