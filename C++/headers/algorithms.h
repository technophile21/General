//
//  trie.h
//  Practice
//
//  Created by Manik Singhal on 6/19/16.
//  Copyright (c) 2016 Manik Singhal. All rights reserved.
//

#ifndef Practice_Algorithms_h
#define Practice_Algorithms_h

#include <stdio.h>
#include <iostream>

namespace Algorithms {
    //get longest common subsequence
    int getLCS(const std::string& a, const std::string& b, std::string& result);
    
    //E should implement [] operator
    template<class E, typename T>
    int binSearch(const E& items, int startIdx, int endIdx, const T& searchVal) {
        //assuming sorted input
        
        int low = startIdx;
        int high = endIdx;
        
        while(low <= high && low <= endIdx && high >= startIdx) {
            int mid = (low + high) / 2;
            if(items[mid] == searchVal) return mid;
            
            if(items[mid] > searchVal){
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        
        return -1;
    }
    
    namespace test {
        void testLCS();
    }
}


#endif
