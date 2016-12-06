
//lklist.h
#include "event.h"
#include "Node.h"
#include <iostream>

// He said our Node is our event?

class lklist
{
public:
    Node *evlist2;
    event *evlist;
    lklist();
    void insert(event *p);
    void insertNode(Node *p_node);

};
