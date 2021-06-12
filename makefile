compile: 
	g++ -std=c++0x -pthread src/main.cpp src/Ui.hpp src/Ui.cpp src/ParkingSpot.hpp src/Visitor.cpp src/Visitor.hpp src/ParkingLot.hpp src/ParkingLot.cpp src/Gate.hpp src/Ticket.hpp src/TicketBooth.cpp src/TicketBooth.hpp src/Seat.hpp src/Attraction.hpp src/Attraction.cpp -lncurses -Wall -Wextra -Wconversion -pedantic

run: 
	./a.out
