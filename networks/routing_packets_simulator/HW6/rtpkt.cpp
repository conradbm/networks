class rtpkt{
public:
    int sourceid;       // id of sending router sending this pkt
    int destid;         // id of router to which pkt being sent
    
    int mincost[4];    // min cost to routers: 0 ... 3
};

/*
struct rtpkt
{
    int sourceid;       // id of sending router sending this pkt
    int destid;         // id of router to which pkt being sent
    
    int mincost[4];    // min cost to routers: 0 ... 3
};
 */