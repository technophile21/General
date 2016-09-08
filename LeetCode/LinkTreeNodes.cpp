//
//  LinkTreeNodes.cpp
//  Practice
//
//  Created by Manik Singhal on 3/12/15.
//  Copyright (c) 2015 Manik Singhal. All rights reserved.
//

/*
 Problem: Populating Next Right Pointers in Each Node
 
 Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
 
 Initially, all next pointers are set to NULL.
 
 Note:
 
 You may only use constant extra space.
 You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
 For example,
 Given the following perfect binary tree,
      1
    /  \
   2    3
  / \  / \
 4  5  6  7
 
 After calling your function, the tree should look like:
     1 -> NULL
   /  \
  2 -> 3 -> NULL
 / \  / \
 4 5  6  7 -> NULL

 */


#include <stdio.h>
#include <map>

struct TreeLinkNode {
    TreeLinkNode *left;
    TreeLinkNode *right;
    TreeLinkNode *next;
};

//Exceeding time limit for input tree: {-1,-2,0,-9,-7,0,8,-7,0,-2,0,-1,1,6,-9,-2,-1,1,-3,7,-4,-9,8,7,9,6,-4,-1,-5,-9,-8}
void connect1(TreeLinkNode* root) {
    static std::map<int, TreeLinkNode*> lastLevelNodeMap;
    //TODO: Need to see better handling for level tracking
    
    static int level = 0;
    
    if(lastLevelNodeMap.find(level) != lastLevelNodeMap.end()) {
        TreeLinkNode* node = lastLevelNodeMap[level];
        if(node) {
            node->next = root;
            lastLevelNodeMap[level] = root;
        }
    } else if(root){                    //[Mistake]: I added this else afterwards. Missed it in first go.
        lastLevelNodeMap[level] = root;
    }
    
    if(!root) {
        return;
    }
    level +=1;
    connect1(root->left);
    connect1(root->right);
    level -= 1;
}


//Using constant space
void connect2(TreeLinkNode* root) {
    if(!root || !root->left || !root->right ) return;
    
    root->left->next = root->right;
    if(root->next)
        root->right->next = root->next->left;
    
    connect2(root->left);
    connect2(root->right);
    
    
}