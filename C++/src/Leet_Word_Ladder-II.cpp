//
//  Leet_Word_Ladder-II.cpp
//  Practice
//
//  Created by Manik Singhal on 8/15/14.
//  Copyright (c) 2014 Manik Singhal. All rights reserved.
//

#include "Leet_Word_Ladder-II.h"
#include <unordered_map>
#include <list>

typedef list<unordered_set<string>::const_iterator> STRINGLIST;
typedef pair<string, STRINGLIST> LISTELEMENT;
typedef unordered_map<string, STRINGLIST> ADJLIST;

bool isAdjacent(string a, string b) {
    if(a.length() != b.length()) return false;
    
    int diffCharCount = 0;
    for(int i = 0; i < a.length(); i++) {
        if(a[i] != b[i])
            diffCharCount++;
        if(diffCharCount > 1)
            return false;
    }
    
    return diffCharCount == 1;
}

vector<vector<string>> WordLadderII::findLadders(string start, string end, unordered_set<string> &dict) {
 
    vector<vector<string>> result;
    unordered_set<string> newDict = dict;
    newDict.insert(end);
    
    ADJLIST adjList;

    adjList.insert(LISTELEMENT(start, STRINGLIST()));
    
    unordered_set<string>::const_iterator iter = dict.begin();
    
    for(int i = 0; i < dict.size(); ++i) {
        adjList.insert(LISTELEMENT(*iter, STRINGLIST()));
        ++iter;
    }
    
    adjList.insert(LISTELEMENT(end, STRINGLIST()));
    
    for(ADJLIST::const_iterator i = adjList.begin(); i != adjList.end(); i++) {
        string a = i->first;
        for(unordered_set<string>::const_iterator j = newDict.begin(); j != newDict.end(); ++j) {
            string b = *j;
            if(isAdjacent(a, b)) {
                STRINGLIST& aList = const_cast<STRINGLIST&>(i->second);
                aList.push_back(j);
               /* if(i != 0 && *j != end) {
                    list<const string&>& bList = j->second;
                    bList.push_back(i);

                } */
            }
        }
    }
    
    
    return result;
    
}

