//
//  Node.cpp
//  
//
//  Created by Blake Conrad on 3/8/16.
//
//

#include "Node.h"


Node::Node(event *e){
    data = new event;
    next = NULL;
    data = e;
}