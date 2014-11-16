//
//  Graphs.h
//  Practice
//
//  Created by Manik Singhal on 11/6/14.
//  Copyright (c) 2014 Manik Singhal. All rights reserved.
//

#ifndef Practice_Graphs_h
#define Practice_Graphs_h

#include <list>
#include <map>

#include "boost/shared_ptr.hpp"

/* Exposing Vertex and Edge is not good as we might want to change graph implementation in future. So client shouldn't know this
struct Vertex;

typedef struct Edge {
    int weight;
    struct Vertex* vertex;
}Edge;

typedef struct Vertex {
    int data;
    std::list<Edge*> edgeList;
} Vertex;
*/

namespace DS {
    
    class Vertex;
    typedef std::list<boost::shared_ptr<Vertex>> VerticesList;
    typedef std::map<int, VerticesList::const_iterator> DataVertexMap;
    class Graph {
        
        VerticesList _verticesList;
        DataVertexMap _dataVertexMap;
        
        //TODO: Need some design to have this function internal only and not exposed to client
        boost::shared_ptr<Vertex> addAndGetVertex(int data);
    public:
        Graph();
        ~Graph();
        
        bool isEmpty() const;
        //We don't check for duplicate vertex
        void addVertex(int data);
        void addEdge(int srcData, int dstData, int cost);
        int getCostForEdge(int srcData, int dstData);
        void displayGraph();
        void dfsTraversal();
        void bfsTraversal();
    };
    
} //End namespace Graphs

#endif
