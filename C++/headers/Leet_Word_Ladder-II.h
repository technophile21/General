//
//  Leet_Word_Ladder-II.h
//  Practice
//
//  Created by Manik Singhal on 8/15/14.
//  Copyright (c) 2014 Manik Singhal. All rights reserved.
//

/* PROBLEM DESCRIPTION
 
Given two words (start and end), and a dictionary, find all shortest transformation sequence(s) from start to end, such that:

Only one letter can be changed at a time
Each intermediate word must exist in the dictionary
For example,

Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]
 
Return
[
 ["hit","hot","dot","dog","cog"],
 ["hit","hot","lot","log","cog"]
]
 
Note:
All words have the same length.
All words contain only lowercase alphabetic characters.
 
*/

#ifndef __Practice__Leet_Word_Ladder_II__
#define __Practice__Leet_Word_Ladder_II__

#include <iostream>
#include <stdio.h>
#include <vector>
#include <unordered_set>

using namespace std;

class WordLadderII {
public:
    WordLadderII() {}
    ~WordLadderII() {}
    vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict);
};

#endif /* defined(__Practice__Leet_Word_Ladder_II__) */
