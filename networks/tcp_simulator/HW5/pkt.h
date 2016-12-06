//pkt.h

class pkt{
private:
    int seqnum;
    int acknum;
    int checksum;
    char *pdata;
public:
       
       pkt();
    //setter
    void setseqnum(int i);
    void setacknum(int i);
    void setchecksum(int i);
    void setpdata(char *data);
    void setpdata2(int i, char c);
    
    //getter
    int getseqnum();
    int getacknum();
    int getchecksum();
    char* getpdata();
    char getpdata2(int i);
};
