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
#include <queue>

typedef list<unordered_set<string>::const_iterator> STRINGLIST;
typedef pair<string, STRINGLIST> LISTELEMENT;
typedef unordered_map<string, STRINGLIST> ADJLIST;

enum State {
    eNotExplored,
    eDiscovered,
    eProcessed
};

typedef unordered_map<string, State> NodeStateMap;
typedef unordered_map<string, std::vector<std::string>> ParentMap;

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
        if(a == end) continue;
        
        for(unordered_set<string>::const_iterator j = newDict.begin(); j != newDict.end(); ++j) {
            string b = *j;
            if(isAdjacent(a, b)) {
                STRINGLIST& aList = const_cast<STRINGLIST&>(i->second);
                aList.push_back(j);
            }
        }
    }
    
    std::queue<std::string> qu;
    NodeStateMap nodeState;
    ParentMap parent;
    for(ADJLIST::const_iterator i = adjList.begin(); i != adjList.end(); i++) {
        nodeState[i->first] = eNotExplored;
        parent[i->first] = std::vector<std::string>();
    }
    

    qu.push(start);
    
    while(!qu.empty()) {
        std::string node = qu.front();
        nodeState[node] = eDiscovered;
    
        STRINGLIST& aList = const_cast<STRINGLIST&>(adjList[node]);
        for(STRINGLIST::const_iterator iter = aList.begin(); iter != aList.end(); ++iter) {
            
            std::string curNode = **iter;
            
            parent[curNode].push_back(node);
            
            if(nodeState[curNode] != eNotExplored) continue;

            nodeState[curNode] = eDiscovered;
            qu.push(curNode);
        }
    }
    
    std::string currentNode = end;
    std::vector<std::string> resultItem;
    resultItem.push_back(currentNode);
    
    for(auto& parentNode : parent[currentNode]) {
        
    }
    
    return result;
    
}

