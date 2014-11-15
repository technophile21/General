//
//  Queue.cpp
//  Practice
//
//  Created by Manik Singhal on 6/23/14.
//  Copyright (c) 2014 Manik Singhal. All rights reserved.
//

#include "Queue.h"
#include "Exceptions.h"

namespace DS {
    
    class QueueNode {
    public:
        QueueNode()
        :nextNode(nullptr)
        {
        }
        
        int info;
        QueueNode* nextNode;
    };
    
    SimpleArrayQueue::SimpleArrayQueue(int size)
    : Queue(),
    front(-1),
    rear(0),
    capacity(size)
    {
        items = new int[size];
    }
    
    SimpleArrayQueue::~SimpleArrayQueue() {
        if(items)
            delete [] items;
    }
    
    int SimpleArrayQueue::remove() {
        if(isEmpty())
            throw Exceptions::Underflow();
        
        int item = items[front];
        front = (front+1) % capacity;
        if(front == rear)
            front = -1;             //rear is empty pos, so if front becomes rear after removing an element, that means queue is empty
        
        return item;
    }
    
    void SimpleArrayQueue::insert(int item) {
        if(isFull())                           //important
            throw Exceptions::OverFlow();
        
        items[rear] = item;
        
        if(front == -1)
            front = rear;    //for handling case were rear is in between array, else we could have front = 0
        
        rear = (rear+1) % capacity;                 //important
    }
    
    bool SimpleArrayQueue::isEmpty() {
        return front == -1;
    }
    
    bool SimpleArrayQueue::isFull() {
        return rear == front;
    }
    
    
    
    /***** Linked Queue *****/
    
    SimpleLinkedQueue::SimpleLinkedQueue()
    : Queue(),
    mpFront(nullptr),
    mpRear(nullptr)
    {
        
    }
    
    SimpleLinkedQueue::~SimpleLinkedQueue() {
        //Free all remaining nodes
        while(mpFront)
            remove();
    }
    
    int SimpleLinkedQueue::remove() {
        if(isEmpty())
            throw Exceptions::Underflow();
        
        int item = mpFront->info;
        QueueNode * frontNode = mpFront;
        mpFront = mpFront->nextNode;
        
        if(mpFront == nullptr)                 //important
            mpRear = nullptr;
        
        delete frontNode;
        
        return item;
    }
    
    void SimpleLinkedQueue::insert(int item) {
        
        QueueNode* newNode = new QueueNode();
        if(newNode) {
            newNode->info = item;
            if(mpRear)
                mpRear->nextNode = newNode;
            mpRear = newNode;
            
            if(mpFront == nullptr)
                mpFront = newNode;
        } else
             throw Exceptions::OverFlow();
    }
    
    bool SimpleLinkedQueue::isEmpty() {
        return mpFront == nullptr;
    }
    
    bool SimpleLinkedQueue::isFull() {
        return false;
    }

}
