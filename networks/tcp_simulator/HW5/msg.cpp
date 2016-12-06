//msg.cpp
#include "msg.h"
msg::msg()
{
    mdata=new char[20];
}
char* msg::getmdata()
{
       return mdata;
}
char msg::getmdata2(int i)
{
     return mdata[i];
}
void msg::setmdata(char *data)
{
       mdata = data;
}

void msg::setmdata2(int i, char c)
{
     mdata[i] = c; 
}
