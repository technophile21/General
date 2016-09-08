//
//  GeeksForGeeks.cpp
//  Practice
//
//  Created by Manik Singhal on 06/26/16.
//  Copyright (c) 2016 Manik Singhal. All rights reserved.
//

#include "GeeksForGeeks.h"

namespace GeeksForGeeks {
    
    Graph::Graph(int V)
    {
        this->V = V;
        adj = new list<EdgeNode>[V];
    }
    
    Graph::~Graph() {
        delete[] adj;
    }
    
    void Graph::addEdge(int v, int w, int cost /* = 1 */)
    {
        EdgeNode node(w, cost);
        adj[v].push_back(node); // Add w to v’s list.
    }
    
}