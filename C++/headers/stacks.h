//
//  stacks.h
//  Practice
//
//  Created by Manik Singhal on 6/7/14.
//  Copyright (c) 2014 Manik Singhal. All rights reserved.
//

#ifndef __Practice__stacks__
#define __Practice__stacks__

#include <memory>
#include "Exceptions.h"
#include "StacksImpl.h"

/* Templates need to have definitions present at the point where they are instantiated for *first time* in any part of program. 
    http://www.codeproject.com/Articles/48575/How-to-define-a-template-class-in-a-h-file-and-imp
 */

namespace DS {
    
    template<class A> class StackImpl;   //Important
    
    template<class T>
    class Stack {
    public:
        Stack(int size);
        ~Stack();
        void push (const T&);
        T pop();
        T getTop();
        bool isEmpty();
    private:
        //StackImpl<T> *mpImpl;
        std::auto_ptr<StackImpl<T>> mpImpl;
    };

    template<class T>
    Stack<T>::Stack(int size)
    :mpImpl(new StackImpl<T>(size)){
        
    }
    
    template<class T>
    Stack<T>::~Stack(){
        // delete mpImpl;
    }
    
    template<class T>
    void Stack<T>::push (const T& item) {
        mpImpl->push(item);
    }
    
    template<class T>
    T Stack<T>::pop() {
        return mpImpl->pop();
    }
    
    template<class T>
    T Stack<T>::getTop() {
        return mpImpl->getTop();
    }
    
    template<class A>
    bool Stack<A>::isEmpty() {
        return mpImpl->isEmpty();
    }
    
}

#endif /* defined(__Practice__stacks__) */
