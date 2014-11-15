//
//  StacksImpl.h
//  Practice
//
//  Created by Manik Singhal on 6/23/14.
//  Copyright (c) 2014 Manik Singhal. All rights reserved.
//

#ifndef Practice_StacksImpl_h
#define Practice_StacksImpl_h

namespace DS {
        
    template<class A>
    class StackImpl {
    public:
        StackImpl(int size):
        mSize(size),
        mTop(-1)
        {
            mStackArr = new A[mSize];
        }
        
        ~StackImpl() {
            delete [] mStackArr;
        }
        
        void push (const A&);
        A pop();
        A getTop();
        bool isEmpty();
        
    private:
        int mSize;
        A *mStackArr;
        int mTop;
    };
    
    template<class A>
    void StackImpl<A>::push (const A& item) {
        if(mTop >= mSize - 1) {
            throw Exceptions::OverFlow(); //Exception
        }
        
        mStackArr[++mTop] = item;
    }
    
    template<class A>
    A StackImpl<A>::pop() {
        A item;
        if(mTop < 0) {
            throw Exceptions::Underflow();//exception
        }
        item = mStackArr[mTop--];
        return item;
    }
    
    
    template<class A>
    A StackImpl<A>::getTop() {
        A item;
        if(mTop < 0) {
            return NULL;
        }
        item = mStackArr[mTop];
        return item;
    }
    
    template<class A>
    bool StackImpl<A>::isEmpty() {
        return mTop == -1;
    }

}


#endif
