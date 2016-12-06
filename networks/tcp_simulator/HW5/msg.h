// msg.h

class msg{

private:
  char *mdata;    

public:
    msg();
       
    //getter
    char* getmdata();
    char getmdata2(int i);
    //setter
    void setmdata(char *data);    
    void setmdata2(int i, char c);  
};
