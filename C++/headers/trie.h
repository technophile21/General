//
//  trie.h
//  Practice
//
//  Created by Manik Singhal on 5/31/15.
//  Copyright (c) 2015 Manik Singhal. All rights reserved.
//

#ifndef Practice_trie_h
#define Practice_trie_h

#include <stdio.h>
#include <iostream>
#include <vector>

#define ALPHABET_SIZE 26

class TrieNode {
    std::vector<TrieNode*> childNodes;
    bool bIsWordEnd;
    std::string value;
    bool bHasAnyChild;
public:
    TrieNode(const std::string& value, bool isWorldEnd);
    virtual ~TrieNode();
    TrieNode* getChildNode(char val);
    TrieNode* insertChildNode(TrieNode* childNode);
//    TrieNode* insertChild(const std::string val);
    std::vector<TrieNode*> getChildNodes() {return childNodes;}
    std::string getValue();
    bool isWordEnd() const;
    void setWordEnd();
    void unsetWordEnd();
    bool hasAnyChild() const { return bHasAnyChild; }
    
private:
    int getChildIndex(char value);
};

class Trie {
    TrieNode *root;
    int nodeCount;
public:
    Trie();
    ~Trie();
    void insertWord(const std::string& word);
    bool containsWord(const std::string& word);
    void printAllWords();
};

#endif
