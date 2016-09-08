//
//  Microsoft.cpp
//  Practice
//
//  Created by Manik Singhal on 1/2/15.
//  Copyright (c) 2015 Manik Singhal. All rights reserved.
//

#include "Microsoft.h"
#include <stdio.h>
#include <ctype.h>
#include "Practice.h"

void removeDup(std::string& srcStr) {
    //assuming ascii string
    int a[26] = {0};
    int shiftIdx = 0;
    int i = 0;
    for(;i < Practice::strlen(srcStr.c_str()); ++i) {
        char x = tolower(srcStr[i]);
        if(x != ' ') {
            if(a[x-'a'])
                shiftIdx++;
            else {
                a[x-'a'] = 1;
                srcStr[i-shiftIdx] = x;
            }
        } else
            srcStr[i-shiftIdx] = x;
    }
    
    srcStr[i-shiftIdx] = '\0';
    
    printf("Modified String: %s", srcStr.c_str());
}

/*Not work for test case  { 1, 1, 1, 1, 1, 1, 0, 1, 1,1,1}
Refer: http://stackoverflow.com/questions/4773807/searching-in-an-sorted-and-rotated-array
*/
int findEleRotatedSortedArr(int a[], int len, int key) {
    int low = 0, high = len - 1;
    int mid, iter = 0;
    while (low <= high && low >= 0 && high < len) {
        mid = (low + high) / 2;
        iter++;
        if(a[mid] == key ) {
            printf("No. of iterations: %d\n", iter);
            return mid;
        }
        
        if(a[mid] < key) {
            if(a[mid] < a[low] && a[low] <= key)
                high = mid - 1;
            else
                low = mid + 1;
        }
        else if(a[mid] > key) {
            if(a[mid] > a[high] && a[high] >= key)
                low = mid + 1;
            else
                high = mid - 1;
        }
    }
    
    printf("No. of iterations: %d\n", iter);
    return -1;
}