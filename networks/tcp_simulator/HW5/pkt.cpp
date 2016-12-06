//pkt.cpp
#include "pkt.h"

pkt::pkt(){
    pdata = new char[20];
}

/**  Setters  **/
void pkt::setseqnum(int i)
{
    seqnum = i;
}
void pkt::setacknum(int i)
{
    acknum = i;
}
void pkt::setchecksum(int i)
{
    checksum = i;
}
void pkt::setpdata(char *data)
{
    pdata = data;
}
void pkt::setpdata2(int i, char c)
{
     pdata[i] = c;
}

/**  Getters  **/
int pkt::getseqnum()
{
    return seqnum;
}
int pkt::getacknum()
{
    return acknum;
}
int pkt::getchecksum()
{
    return checksum;
}
char* pkt::getpdata()
{
    return pdata;
}
char pkt::getpdata2(int i)
{
     return pdata[i];
}
