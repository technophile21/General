#include "Practice.h"
#include "Exceptions.h"

namespace Practice {
    size_t strlen(const char* str) {
        if(!str)
            return 0;
        
        size_t i = 0;
        size_t len = 0;
        while(str[i]) {
            len++;
            i++;
        }
        
        return len;
    }
    
    void strcpy(char *dest, const char* src) {
        if(!src || !dest) return;
        
        size_t i = 0;
        
        //while((dest[i++] = src[i++]));   //A necessary warning
        
        while(src[i]) {
            //dest[i++] = src[i]; // not a good statement still
            dest[i] = src[i];
            ++i;
        }
        
    }
    
    int strcmp(const char* src1, const char* src2) {
        if(!src1 && !src2) return 0;
        
        if(!src1) return (int)(0 - src2[0]);
        if(!src2) return (int)(src1[0]);
        
        size_t i = 0;
        while(src1[i] && src2[i] && src1[i] == src2[i])
            i++;
        
        return (int)(src1[i] - src2[i]);
        
    }
    
    int atoi(const char* str) {
        if(!str || !(*str)) throw InvalidArgumentException();
        
        char *tmp = const_cast<char*>(str);
        
        int val = 0;
        int sign = 1;
        while(*tmp) {
            if(*tmp == '+')
                ;
            else if (*tmp == '-')
                sign = -1;
            else if(*tmp >= '0' && *tmp <= '9') {
                val = val * 10 + (*tmp - '0');
            } else
                throw InvalidArgumentException();
            tmp++;
        }
        
        return val * sign;
    }
}