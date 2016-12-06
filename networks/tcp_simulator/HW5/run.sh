rm *.o
g++ -c pkt.cpp
g++ -c msg.cpp
g++ -c event.cpp
g++ -c lklist.cpp
g++ -c tcp_1a.cpp
g++ pkt.o msg.o event.o lklist.o tcp_1a.o
./a.out

