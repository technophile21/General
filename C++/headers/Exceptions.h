//
//  PracticeUtil.h
//  Practice
//
//  Created by Manik Singhal on 6/7/14.
//  Copyright (c) 2014 Manik Singhal. All rights reserved.
//

#ifndef __Exceptions__
#define __Exceptions__

namespace Exceptions {
    class MyException {
    public:
        MyException() {}
        ~MyException() {}
        
    };
    
    class InvalidArgumentException:public MyException {
    public:
        InvalidArgumentException();
        ~InvalidArgumentException();
    };
    
    class DivideByZero:public MyException {
    public:
        DivideByZero();
        ~DivideByZero();
    };
    
    class Underflow:public MyException {
    public:
        Underflow():MyException() {}
        ~Underflow() {}
    };
    
    class OverFlow:public MyException {
    public:
        OverFlow():MyException() {}
        ~OverFlow() {}
    };
}

#endif /* defined(__Exceptions__) */
