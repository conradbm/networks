//event.cpp
#include "event.h"

event::event(){
               
    pktptr=0;
    prev=0;
    next=0;
}

// Setters
void event::setevtime(float f)
{
     evtime = f;
}

void event::setevtype(int i)
{
    evtype = i;
}
void event::seteventity(int i)
{
    eventity = i;
}

// Getters
float event::getevtime()
{
      return evtime;
}
int event::getevtype()
{
      return evtype;
}
int event::geteventity()
{
      return eventity;
}

