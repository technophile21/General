#include "CommonHeaders.h"
#include "Exceptions.h"
#include "stacks.h"

#ifndef __PRACTICE__
#define __PRACTICE__

#include <memory>

namespace Practice {
    using namespace Exceptions;
    
    using DS::Stack;
    
	void swap(int*, int*);
    
    size_t strlen(const char* str);
    
    void strcpy(char *dest, const char* src);
    
    int strcmp(const char* src1, const char* src2);
    
    int atoi(const char* str);
    
    double evalPostfix(const std::string& expr);
    
    std::string getPostfixFromInfix(const std::string& infixExpr);
    
   }

#endif //__PRACTICE__