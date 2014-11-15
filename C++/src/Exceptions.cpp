//
//  PracticeUtil.cpp
//  Practice
//
//  Created by Manik Singhal on 6/7/14.
//  Copyright (c) 2014 Manik Singhal. All rights reserved.
//

#include "Exceptions.h"

namespace Exceptions {
    InvalidArgumentException::InvalidArgumentException():MyException() { }
    InvalidArgumentException::~InvalidArgumentException() {}

    DivideByZero::DivideByZero():MyException() { }
    DivideByZero::~DivideByZero() {}

}
