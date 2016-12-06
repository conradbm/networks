#include <stddef.h>
#include <iostream>

#include "event.cpp"

class LkList{
    
public:
    event *evlist;
    void insertEventLklist(event *p);
    LkList();
};

LkList::LkList(){
    LkList::evlist = NULL;
}

void LkList::insertEventLklist(event *p)
{
    event *q,*qold;

    q = LkList::evlist;
    
    if (q==NULL)
    {
        LkList::evlist=p;
        p->next=NULL;
        p->prev=NULL;
    }
    else
    {
        for (qold = q; q !=NULL && p->evtime > q->evtime; q=q->next)
            qold=q;
        
        if (q==NULL) {
            qold->next = p;
            p->prev = qold;
            p->next = NULL;
        }
        else if (q==LkList::evlist) { /* front of list */
            p->next=LkList::evlist;
            p->prev=NULL;
            p->next->prev=p;
            LkList::evlist = p;
        }
        else {
            p->next=q;
            p->prev=q->prev;
            q->prev->next=p;
            q->prev=p;
        }
    }
    
    //std::cout << "Correctly inserted!!" << std::endl;
    //std::cin.ignore();
}