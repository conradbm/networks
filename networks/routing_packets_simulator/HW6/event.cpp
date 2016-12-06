#include "rtpkt.cpp"

class event{
public:
    float evtime;             // event time
    int evtype;               // event type code
    int eventity;             // entity where event occurs
    struct rtpkt *rtpktptr;   // ptr to packet assoc w this event
    event *prev;
    event *next;
};

/*
struct event
{
    float evtime;             // event time
    int evtype;               // event type code
    int eventity;             // entity where event occurs
    struct rtpkt *rtpktptr;   // ptr to packet assoc w this event
    struct event *prev;
    struct event *next;
};
 */