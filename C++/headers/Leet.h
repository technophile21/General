//
//  Leet.h
//  Practice
//
//  Created by Manik Singhal on 5/9/15.
//  Copyright (c) 2015 Manik Singhal. All rights reserved.
//

#ifndef Practice_Leet_h
#define Practice_Leet_h

#include <stdio.h>
#include <iostream>
#include <vector>

#include "types.h"

using namespace std;

struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

namespace Solution {
    string fractionToDecimal(int numerator, int denominator);
    void reorderList(ListNode* head);
    vector<vector<int>> permuteUnique(vector<int>& nums);
    int firstMissingPositive(vector<int>& nums);
    string longestCommonPrefix(vector<string>& strs);
    string longestPalindrome(string s);
   
    /*Given a collection of intervals, merge all overlapping intervals.
    
    For example,
    Given [1,3],[2,6],[8,10],[15,18],
    return [1,6],[8,10],[15,18].*/
    vector<Interval> merge(vector<Interval>& intervals) ;
    
    //Increasing Triplet Subsequence
    bool increasingTriplet(vector<int>& nums);
    
    //3Sum
    vector<vector<int>> threeSum(vector<int>& nums);
    
    TreeNode* sortedListToBST(ListNode* head);
    
    int integerBreak(int n);
    
    void surroundingRegions(vector<vector<char>>& board);
    
    namespace test {
        void testThreeSum();
        void testSortedListToBST();
        void testIntegerBreak();
        void testSurroundingRegions();
    }
}

#endif
