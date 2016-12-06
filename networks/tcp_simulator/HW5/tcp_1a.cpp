// HW5_Blake_TCP_With_Classes.cpp
// HW5_Blake_tcp_Classes.cpp
// class msg,pkt,evnt, and lklist classes
// In class it was mentioned "Your Node is an event" so I kept my event class as my Node
// separate all of them into several files with .h and .cpp's


/*** Create Msg Class ***/
// -- msg.h -> class msg { ... }
// -- msg.cpp -> msg::msg(){ ... }

/*** Create Pkt Class ***/
// -- pkt.h -> class pkt { ... }
// -- pkt.cpp -> pkt::pkt(){ ... }

/*** Create Event Class ***/
// -- event.h -> class event { ... }
// -- event.cpp -> event::event() { ... }

/*** Create Lklist Class ***/
// -- lklist.h -> class lklist { ... }
// -- lklist.cpp -> lklist::lklist() { ... }

#include <iostream>
#include <cstdlib>
#include <fstream>
#include "msg.h"
//#include "event.h"
#include "lklist.h"

using namespace std;

fstream outFile;

#define NOTUSED 0
#define NACK -1
#define   A    0
#define   B    1

#define  PRINT_LAYER     1
#define  TCP_LAYER       2

int nrMsgs = 0;              
int maxNrMsgs = 0;          
float time1 = 0.0;             
float avgTime;  
int   nrTCP_LAYER;                               
int expectedseqnum;          
int nextseqnum;                   
            
lklist ls1;

void init();
void A_init();
void B_init();
void A_input(pkt packet);
void B_input(pkt packet);
void A_output(msg message);
void B_output(msg message);
void TCP_ProcPkt(int AorB, pkt packet);
void Print_Msg(int AorB, char datasent[20]);
void insertEventLklist(event *p);
void generate_next_message();
float GenerateRandNr();


/**************************************************************/
/************************* Main *******************************/
/**************************************************************/
int main()
{

    ls1.evlist = NULL;

// BEGIN PROGRAM
   event *eventptr;
   msg  msg1;
   pkt  pkt1;
   
   int i,j;
   outFile.open("outTCP.txt", ios::out);

   init();
   A_init();
   B_init();
   
   while (1) 
   {
        eventptr = ls1.evlist;      // get next event
        
        if (eventptr==NULL)
           goto terminate;

        ls1.evlist = ls1.evlist->next;  // remove this event from lklist of events

        if (ls1.evlist!=NULL)
           ls1.evlist->prev=NULL;
        
        cout<<"EvTime: "<<eventptr->getevtime()<<" EvType: "<<eventptr->getevtype()<<" EvEntity: "<<eventptr->geteventity()<<endl;
        outFile<<"nEvTime: "<<eventptr->getevtime()<<" EvType: "<<eventptr->getevtype()<<" EvEntity: "<<eventptr->geteventity()<<endl;
       cout << endl;
        time1 = eventptr->getevtime();  // update time to next event time

        if (nrMsgs==maxNrMsgs)
			break;                        

		if (eventptr->getevtype() == PRINT_LAYER ) 
		{
            generate_next_message();  

            // fill in msg
            j = nrMsgs % 26; 
            for (i=0; i<20; i++)  
               msg1.setmdata2(i, 97 + j);

            for (i=0; i<20; i++) 
			{
               cout<<msg1.getmdata2(i);
               outFile<<msg1.getmdata2(i);
			}

            cout<<endl;
            outFile<<endl;
	     
            nrMsgs++;

            if (eventptr->geteventity() == A) 
                A_output(msg1);  
            else
                B_output(msg1);  
          }

          else if (eventptr->getevtype() ==  TCP_LAYER) 
		  {
            pkt1.setseqnum(eventptr->pktptr->getseqnum());
            pkt1.setacknum(eventptr->pktptr->getacknum());
            pkt1.setchecksum(eventptr->pktptr->getchecksum());

            for (i=0; i<20; i++)  
                pkt1.setpdata2(i, eventptr->pktptr->getpdata2(i));
                //pkt1.pdata[i] = eventptr->pktptr->pdata[i];
                
			if (eventptr->geteventity() ==A)    
   				A_input(pkt1);            
            else
   				B_input(pkt1);

			free(eventptr->pktptr);  
          }

          else  
		  {
			  cout<<"\nError: unknown event type \n";
			  outFile<<"\nError: unknown event type \n";
          }
        free(eventptr);
       
       cout << endl << endl;
   }

terminate:
   cout<<" \n\nEnd of the TCP Algor. at time "<<time1<<"\n after sending "<<nrMsgs<<" msgs."<<endl;
   outFile<<" \n\nEnd of the TCP Algor. at time "<<time1<<"\n after sending "<<nrMsgs<<" msgs!!!"<<endl;

   system("pause");
}


/**************************************************************/
/************************* Init *******************************/
/**************************************************************/
void init()  
{
  int i;
  float sum, avg;
  //float GenerateRandNr();
  
   cout<<"-----  Welcome to TCP Netw Algorithm  -------- \n\n";
   outFile<<"-----  Welcome to TCP Netw Algorithm  -------- \n\n";

   cout<<"Enter number of msgs: ";
   outFile<<"Enter number of msgs: ";
   cin>>maxNrMsgs;

   cout<<"Enter time betw msgs [>0.0]:";
   outFile<<"Enter time betw msgs [>0.0]:";
   cin>>avgTime;

cout<<"Nr of msgs="<<maxNrMsgs<<"; time betw msgs="<<avgTime<<endl<<endl;
outFile<<"Nr of msgs="<<maxNrMsgs<<"; time betw msgs="<<avgTime<<endl<<endl;


   srand(9999);             
   sum = 0.0;                
   for (i=0; i<1000; i++)
      sum=sum+GenerateRandNr();    

   avg = sum/1000.0;

   if (avg < 0.25 || avg > 0.75) 
   {
      cout<<"Error: Rand nr generation failed\n"; 
      system("pause"); exit(1);}

   nrTCP_LAYER = 0;
   time1=0.0;


   generate_next_message();   // init event lklist
}


/************************************************************************/
/************************* GenerateRandNr *******************************/
/************************************************************************/
float GenerateRandNr() 
{
  double mm = 10000;  
  float x;                  

  x = (float)(rand()%10000+1)/mm;

  return x;
}  

/***********************************************************************/
/*********************** generate_next_message *************************/
/***********************************************************************/
void generate_next_message()
{
   double x;
   event *evptr;

   cout<<"Generate Next MSG\n";
   outFile<<"Generate Next MSG\n";
 
   x = avgTime*GenerateRandNr()*2;  
                             
   evptr = new event;

/*** USE SET GET FUNCS ***/

   evptr->setevtime(time1 + x);
   //cout << "getevtime " << evptr->getevtime() << endl;
   evptr->setevtype(PRINT_LAYER);
   //cout << "getevtype " << evptr->getevtype() << endl;
   evptr->seteventity(A);
   //cout << "geteventity " << evptr->geteventity() << endl;

/*** INSERT TO MY PUBLIC LINKED LIST ***/
   //insertEventLklist(evptr);
    std::cout<<"\ninsert Event in Lklist at time: "<<time1<<std::endl;
    outFile<<"\ninsert Event in Lklist at time: "<<time1<<std::endl;
    Node *node=new Node(evptr);
    ls1.insertNode(node);
    ls1.insert(evptr);
    
}

/************************************************************/
/*********************** A_init *****************************/
/************************************************************/
void A_init()
{
   nextseqnum = 0;
}

/**************************************************************/
/*********************** A_INPUT *****************************/
/**************************************************************/
void A_input(pkt packet)
{
     
}

/**************************************************************/
/*********************** A_output *****************************/
/**************************************************************/
void A_output(msg msg1)
{
   int i;
   pkt sendpkt;

   cout<<"---A_output: New msg arrives, send new msg to TCP_LAYER!\n";
   outFile<<"---A_output: New msg arrives, send new msg to TCP_LAYER!\n";

   // create packet
   sendpkt.setseqnum(nextseqnum);
   sendpkt.setacknum(NOTUSED);
   for ( i=0; i<20 ; i++ ) 
       sendpkt.setpdata2(i, msg1.getmdata2(i));

   // send out packet
   TCP_ProcPkt(A, sendpkt);

   nextseqnum = nextseqnum+1;
}

/************************************************************/
/*********************** B_init *****************************/
/************************************************************/
void B_init()
{
  expectedseqnum = 0;
}

/**************************************************************/
/*********************** B_INPUT *****************************/
/**************************************************************/
void B_input(pkt packet)
{
  pkt sendpkt;
  int i;

  if ( packet.getseqnum() == expectedseqnum)
  {
       cout<<"----B_input: packet "<<packet.getseqnum()<<" is correctly rcvd, send ACK!"<<endl;
       outFile<<"----B_input: packet "<<packet.getseqnum()<<" is correctly rcvd, send ACK!"<<endl;

	   sendpkt.setseqnum(NOTUSED);
       sendpkt.setacknum(expectedseqnum);
       for ( i=0; i<20 ; i++ ) 
            sendpkt.setpdata2(i,'X');
              
       TCP_ProcPkt(B, sendpkt);
       
       expectedseqnum = expectedseqnum+1;        
       
       Print_Msg(B,packet.getpdata());
  }
}

/**************************************************************/
/*********************** B_output *****************************/
/**************************************************************/
void B_output(msg message)  
{

}

//////////  insertEventLklist  //////////////////
/*
void insertEventLklist(event *p)
{
     
   event *q,*qold;

   cout<<"\n        insert Event in Lklist at time: "<<time1<<endl;
   outFile<<"\n        insert Event in Lklist at time: "<<time1<<endl;

   q = evlist;     

   if (q==NULL) 
   {   
        evlist=p;
        p->next=NULL;
        p->prev=NULL;
        }
     else {
        for (qold = q; q !=NULL && p->getevtime() > q->getevtime(); q=q->next)
              qold=q; 
        if (q==NULL) {  
             qold->next = p;
             p->prev = qold;
             p->next = NULL;
             }
           else if (q==evlist) { // front of lklist
             p->next=evlist;
             p->prev=NULL;
             p->next->prev=p;
             evlist = p;
             }
           else {    
             p->next=q;
             p->prev=q->prev;
             q->prev->next=p;
             q->prev=p;
             }
         }
}*/

/*********************************************************************/
/*********************** TCP_Process_Pkt *****************************/
/*********************************************************************/
void TCP_ProcPkt(int AorB, pkt packet1)
{
  pkt *mypktptr;
  event *evptr,*q;
  float lastime;
  int i;

  nrTCP_LAYER++;

 cout<<"TCP_ProcPkt was called: "<<nrTCP_LAYER<<" times"<<endl;
  outFile<<"TCP_ProcPkt: was called: "<<nrTCP_LAYER<<" times"<<endl;

 /*** USE SETTER GETTER FUNCTIONS ***/
 
 mypktptr = new pkt;
 mypktptr->setseqnum(packet1.getseqnum());
 mypktptr->setacknum(packet1.getacknum());
 mypktptr->setchecksum(packet1.getchecksum());

 for (i=0; i<20; i++)
    mypktptr->setpdata2(i, packet1.getpdata2(i));

  cout<<"TCP_LAYER: seq: "<<mypktptr->getseqnum()<<", ack "<<mypktptr->getacknum()<<", checksum: "<<mypktptr->getchecksum()<<endl;
  outFile<<"TCP_LAYER: seq: "<<mypktptr->getseqnum()<<", ack "<<mypktptr->getacknum()<<", checksum: "<<mypktptr->getchecksum()<<endl;

  for (i=0; i<20; i++)
  {
        cout<<mypktptr->getpdata2(i);
        outFile<<mypktptr->getpdata2(i);
  }

  cout<<endl;
  outFile<<endl;

 /*** USE SETTER GETTER FUNCTIONS ***/
  evptr = new event;
  evptr->setevtype(TCP_LAYER);   
  evptr->seteventity((AorB+1) % 2); 
  evptr->pktptr = mypktptr;       

 lastime = time1;

 for (q=ls1.evlist; q!=NULL ; q = q->next)
    if ( (q->getevtype()==TCP_LAYER  && q->geteventity()==evptr->geteventity()) ) 
      lastime = q->getevtime();

 /*** USE SETTER GETTER FUNCTIONS ***/
  evptr->setevtime(lastime + 1 + 9*GenerateRandNr());
 
 /*** INSERT TO MY PUBLIC LINKED LIST ***/
  //insertEventLklist(evptr);
    std::cout<<"*** insert Event in Lklist at time: "<<time1<<std::endl;
    outFile<<"*** insert Event in Lklist at time: "<<time1<<std::endl;
    //Node *evNode = new Node(evptr);
    //ls1.insertNode(evNode);
    ls1.insert(evptr);
}

/*******************************************************************/
/*********************** Print Message *****************************/
/*******************************************************************/
void Print_Msg(int AorB, char msg1[20])
{
  int i;  

  cout<<"--- DATA RECEIVED: ";
  outFile<<"--- DATA RECEIVED: ";

  for (i=0; i<20; i++)
  {
      cout<<msg1[i];
      outFile<<msg1[i];
  }

  cout<<endl; 
  outFile<<endl; 
}

