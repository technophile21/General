//
//  Queue.h
//  Practice
//
//  Created by Manik Singhal on 6/23/14.
//  Copyright (c) 2014 Manik Singhal. All rights reserved.
//

#ifndef Practice_Queue_h
#define Practice_Queue_h

namespace DS {
    
    //TODO: Implement factory pattern for getting different queues
    class Queue {
        virtual int remove() = 0;
        
        virtual void insert(int item) = 0;
        
        virtual bool isEmpty() = 0;
        
        virtual bool isFull() = 0;
    };
    
    class SimpleArrayQueue : public Queue {
    public:
        SimpleArrayQueue(int size = 50);
        ~SimpleArrayQueue();
        
        int remove();
        
        void insert(int item);
        
        bool isEmpty();
        
        bool isFull();
        
    private:
        int front;
        int rear;
        int *items;
        int capacity;
        
        /*Making copying private as we are deleting a dynamic object in destructor . If this class objects gets copied with default implementation of these methods then the dynamically allocated object will be deleted twice. 
         As an alternative we could define these methods and manage memory allocation for dynamic members. */
        
        SimpleArrayQueue(const SimpleArrayQueue&) {}
        void operator=(const SimpleArrayQueue&) {}
    };
    
    class QueueNode;
    
    class SimpleLinkedQueue : public Queue {
    public:
        SimpleLinkedQueue();
        ~SimpleLinkedQueue();
        
        int remove();
        
        void insert(int item);
        
        bool isEmpty();
        
        bool isFull();
        
    private:
        QueueNode *mpFront;
        QueueNode *mpRear;
        
        /*Making copying private as we are deleting a dynamic object in destructor . If this class objects gets copied with default implementation of these methods then the dynamically allocated object will be deleted twice.
         As an alternative we could define these methods and manage memory allocation for dynamic members. */
        
        SimpleLinkedQueue(const SimpleLinkedQueue&) {}
        void operator=(const SimpleLinkedQueue&) {}
    };

    
}


#endif
