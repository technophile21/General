//
//  Graphs.cpp
//  Practice
//
//  Created by Manik Singhal on 11/6/14.
//  Copyright (c) 2014 Manik Singhal. All rights reserved.
//

#include <stack>
#include <queue>
#include "Graphs.h"

//Refer for better approach: http://codereview.stackexchange.com/questions/36464/coding-and-printing-a-graph

namespace DS {

    //Declaring Vertex and Edge here will hide their structure from client.
    struct Vertex;

    struct Edge {
        int cost;
        struct Vertex* srcVertex;
        struct Vertex* dstVertex;
    };

    typedef std::list<Edge*> EdgeList;
    class Vertex {
    public:
        Vertex() {
            bVisited = false;
        }
        int data = 0;
        EdgeList edgeList;
        bool bVisited = false;   //In C++11 we can initialize member directly
    };
        
    Graph::Graph() {
        
    }

    Graph::~Graph() {
        for(Vertex* vertex: _verticesList) {
            std::list<Edge*> edgeList = vertex->edgeList;
            for(Edge *edge : edgeList) {
                delete edge;
            }
            
            delete vertex;
        }
    }

    // Const Correctness: http://www.cprogramming.com/tutorial/const_correctness.html
    bool Graph::isEmpty() const {
        return _verticesList.empty();
    }

    /* Exception safety:
     Here, you are allocating memory for a Vertex, then you try to add it at the end of _verticesList. When inserting an element in an std::list, a new node should be allocated. Unless otherwise specified, std::list uses std::allocator to allocate new memory, which is based on new and delete. In other words, if there is no more free memory to allocate for the new node, new will throw an std::bad_alloc exception and insert will rethrow the exception. In addVertex, if insert throws, then the newly allocated Vertex (node) will not be freed. This is a memory leak, and so your method fails to provide the basic exception safety (also known as no-leak guarantee).
     
     */
    void Graph::addVertex(int data) {
        Vertex* node = new Vertex();
        node->data = data;
        node->edgeList.clear();
        
        VerticesList::const_iterator iter = _verticesList.insert(_verticesList.end(), node);
        _dataVertexMap.insert(std::make_pair(data, iter));
    }

    Vertex* Graph::addAndGetVertex(int data) {
        Vertex* node = new Vertex();
        node->data = data;
        node->edgeList.clear();
        
        VerticesList::const_iterator iter = _verticesList.insert(_verticesList.end(), node);
        //TODO: Evaluate if this is right approach to insert in map i.e iterator
        _dataVertexMap.insert(std::make_pair(data, iter));
        
        return node;
    }
        
    void Graph::addEdge(int srcData, int dstData, int cost) {
        DataVertexMap::const_iterator srcIter = _dataVertexMap.find(srcData);
        DataVertexMap::const_iterator dstIter = _dataVertexMap.find(dstData);
        
        //Use nullptr
        Vertex* srcVertex = nullptr;
        Vertex* dstVertex = nullptr;
        if(srcIter == _dataVertexMap.end())
            srcVertex = addAndGetVertex(srcData);
        else
            srcVertex = *(srcIter->second);
        
        if(dstIter == _dataVertexMap.end())
            dstVertex = addAndGetVertex(dstData);
        else
            dstVertex = *(dstIter->second);
        
        Edge* newEdge = new Edge();
        newEdge->cost = cost;
        newEdge->srcVertex = srcVertex;
        newEdge->dstVertex = dstVertex;
        
        srcVertex->edgeList.push_back(newEdge);
        
    }

    int Graph::getCostForEdge(int srcData, int dstData) const {
        DataVertexMap::const_iterator srcIter = _dataVertexMap.find(srcData);
        DataVertexMap::const_iterator dstIter = _dataVertexMap.find(dstData);
        
        if(srcIter == _dataVertexMap.end() || dstIter == _dataVertexMap.end())
            return -1;
        
        EdgeList edgeList = (*(srcIter->second))->edgeList;
        
        //C++11: Range based for loop
        for (const Edge* edge : edgeList) {
            if(edge->dstVertex == *(dstIter->second))
                return edge->cost;
        }
        
        return -1;
    }
        
    void Graph::displayGraph() {
        
    }

    void Graph::dfsTraversal() {
        std::stack<Vertex*> vertexStack;
        vertexStack.push(_verticesList.front());
        
        while(!vertexStack.empty())
        {
            Vertex *vertex = vertexStack.top();
            vertexStack.pop();
            vertex->bVisited = true;
            printf("%d\n", vertex->data);
            const EdgeList edgeList = vertex->edgeList;
            for (const Edge* edge : edgeList) {
                Vertex *dstVertex = edge->dstVertex;
                if(!dstVertex->bVisited)
                    vertexStack.push(dstVertex);
            }
        }
        
        //TODO: mark visited back to false for each node.
        
    }
    
    void Graph::bfsTraversal() {
        std::queue<Vertex*> verticesQueue;
        verticesQueue.push(_verticesList.front());
        
        while(!verticesQueue.empty())
        {
            Vertex *vertex = verticesQueue.front();
            verticesQueue.pop();
            
            if(vertex->bVisited) continue;
            
            vertex->bVisited = true;
            printf("%d\n", vertex->data);
            const EdgeList edgeList = vertex->edgeList;
            for (const Edge* edge : edgeList) {
                Vertex *dstVertex = edge->dstVertex;
                if(!dstVertex->bVisited)
                    //we can also have a check here if vertex is already in queue, but since we are using pointer if a duplicate vertex is encountered later then it will have bVisited true.
                    verticesQueue.push(dstVertex);
            }
        }
        
        //TODO: mark visited back to false for each node.

    }

}