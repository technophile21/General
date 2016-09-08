//
//  GeeksForGeeks.h
//  Practice
//
//  Created by Manik Singhal on 06/26/16.
//  Copyright (c) 2016 Manik Singhal. All rights reserved.
//

#ifndef __Practice__Geeks_For_Geeks__
#define __Practice__Geeks_For_Geeks__

#include<iostream>
#include <list>

using namespace std;

namespace GeeksForGeeks {
    
    struct EdgeNode {
        int vertexIdx;
        int cost;
        EdgeNode(int idx, int edgeCost) {
            vertexIdx = idx;
            cost = edgeCost;
        }
    };
    
    // This class represents a directed graph using adjacency list representation
    class Graph
    {
        int V;    // No. of vertices
        list<EdgeNode> *adj;    // Pointer to an array containing adjacency lists
    public:
        Graph(int V);  // Constructor
        ~Graph();
        void addEdge(int v, int w, int cost = 1); // function to add an edge to graph
    };
    
}

#endif