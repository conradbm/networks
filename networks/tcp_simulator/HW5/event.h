//event.h
#include "pkt.h"

class event{
private:
    float evtime;
    int evtype;        // TCP_LAYER or PRINT_LAYER 
    int eventity;     // to A or B   
    
public:
    pkt *pktptr;
    event *prev;
    event *next;
    
    event();
    //setters
    void setevtime(float f);
    void setevtype(int i);
    void seteventity(int i);
    
    //getters
    float getevtime();
    int getevtype();
    int geteventity();

};
