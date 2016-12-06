#include "lklist.h"

lklist::lklist(){
    //lklist::pl = NULL;
}

void lklist::insert(event *p){
    event *q,*qold;
    
    q = lklist::evlist;
    
    if (q==NULL)
    {
        lklist::evlist=p;
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
        else if (q==lklist::evlist) { // front of lklist
            p->next=lklist::evlist;
            p->prev=NULL;
            p->next->prev=p;
            lklist::evlist = p;
        }
        else {
            p->next=q;
            p->prev=q->prev;
            q->prev->next=p;
            q->prev=p;
        }
    }
}

void lklist::insertNode(Node *p){
    event *q,*qold;
    
    q = &lklist::evlist2->data;
    
    if (q==NULL)
    {
        lklist::evlist2->data=p->data;
        p->data.next=NULL;
        p->data.prev=NULL;
    }
    else {
        for (qold = q; q !=NULL && p->data.getevtime() > q->getevtime(); q=q->next)
            qold=q;
        if (q==NULL) {
            qold->next = &p->data;
            p->data.prev = qold;
            p->data.next = NULL;
        }
        else if (q==&lklist::evlist2->data) { // front of lklist
            p->data.next=&lklist::evlist2->data;
            p->data.prev=NULL;
            p->data.next->prev=&p->data;
            lklist::evlist2->data = p->data;
        }
        else {
            p->data.next=q;
            p->data.prev=q->prev;
            q->prev->next=&p->data;
            q->prev=&p->data;
        }
    }
}

//Insert a node p_node
    // get it's p_node->data to access the current event, and use its p_node->next as a lklist