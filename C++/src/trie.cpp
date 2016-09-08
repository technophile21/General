//
//  trie.cpp
//  Practice
//
//  Created by Manik Singhal on 5/31/15.
//  Copyright (c) 2015 Manik Singhal. All rights reserved.
//

#include <stdio.h>
#include "trie.h"
#include <assert.h>
#include <ctype.h>

TrieNode::TrieNode(const std::string& newValue, bool isWorldEnd)
:bIsWordEnd(isWorldEnd)
,bHasAnyChild(false)
{
    value = newValue;
    for(int i = 0; i < ALPHABET_SIZE; ++i) {
        childNodes.push_back(nullptr);
    }
}

TrieNode::~TrieNode() {
    for(int i = 0; i < ALPHABET_SIZE; ++i) {
        if(childNodes[i]) {
            delete childNodes[i];
            childNodes[i] = NULL;
        }
    }
}

int TrieNode::getChildIndex(char value) {
        return value - 'a';  //only for small letters
}

TrieNode* TrieNode::getChildNode(char value) {
    int idx = getChildIndex(value);
    return childNodes[idx];
}

TrieNode* TrieNode::insertChildNode(TrieNode* trieNode) {
    if(!trieNode) return NULL;
    
    int idx = getChildIndex(trieNode->getValue()[0]);
    
    if(!childNodes[idx]) {
        childNodes[idx] = trieNode;
    } else
        assert(false);
    
    return trieNode;
}

/*TrieNode* TrieNode::insertChild(char val) {
    int idx = getChildIndex(val);
    
    if(!childNodes[idx]) {
        childNodes[idx] = new TrieNode(val, false);
    } else
        assert(false);
    
    return childNodes[idx];
}*/

std::string TrieNode::getValue() {
    return value;
}

bool TrieNode::isWordEnd() const {
    return bIsWordEnd;
}

void TrieNode::setWordEnd() {
    bIsWordEnd = true;
}

void TrieNode::unsetWordEnd() {
    bIsWordEnd = false;
}


Trie::Trie()
:root(NULL)
,nodeCount(0)
{
    
}

Trie::~Trie() {
    if(root) {
        delete  root;
        root = NULL;
    }
}

void Trie::insertWord(const std::string& word) {
    if(!root) {
        root = new TrieNode("a", false);
    }
    
    size_t len = word.length();
    TrieNode *tmpNode = root;
    for(size_t i = 0; i < len; ++i) {
        char c = tolower(word[i]);
        TrieNode* node = tmpNode->getChildNode(c);
        if(node) {
            tmpNode = node;
        } else {
            nodeCount++;
            std::string val = "";
            val += c;
            TrieNode* newNode = new TrieNode(val, i == len - 1);
            tmpNode->insertChildNode(newNode);
            tmpNode = newNode;
        }
        if(i == len - 1)
            tmpNode->setWordEnd();
    }
}

bool Trie::containsWord(const std::string& word) {
    if(!root) return false;
    
    
    size_t len = word.length();
    TrieNode *tmpNode = root;
    bool bContains = false;
    for(size_t i = 0; i < len; ++i) {
        char c = tolower(word[i]);
        TrieNode* node = tmpNode->getChildNode(c);
        if(node) {
            tmpNode = node;
            if(i == len - 1) {
                bContains = node->isWordEnd();
            }
        } else {
            break;
        }
    }

    return bContains;
}

//TODO: not complete
void printWordsHelper(TrieNode* root) {
    static std::string wordString = "";
    if(!root) return;
    
    wordString.push_back(root->getValue()[0]);
    
    if(root->isWordEnd())
        printf("\n%s\n", wordString.c_str());
    
    std::vector<TrieNode*> childNodes = root->getChildNodes();
    for(int i = 0; i < childNodes.size(); ++i)
        if(childNodes[i])
            printWordsHelper(childNodes[i]);
    
    wordString.pop_back();
    
}

void Trie::printAllWords() {
    if(!root) return;
    
    std::vector<TrieNode*> childNodes = root->getChildNodes();
    for(int i = 0; i < childNodes.size(); ++i)
        if(childNodes[i])
            printWordsHelper(childNodes[i]);
    
}

