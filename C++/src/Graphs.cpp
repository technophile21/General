//
//  Graphs.cpp
//  Practice
//
//  Created by Manik Singhal on 11/6/14.
//  Copyright (c) 2014 Manik Singhal. All rights reserved.
//

#include "Graphs.h"
#include <stack>
#include <queue>

//Refer for better approach: http://codereview.stackexchange.com/questions/36464/coding-and-printing-a-graph

namespace DS {

    //Declaring Vertex and Edge here will hide their structure from client.
    struct Vertex;

    typedef struct Edge {
        int cost;
        struct Vertex* srcVertex;
        struct Vertex* dstVertex;
    }Edge;

    typedef std::list<Edge*> EdgeList;
    class Vertex {
    public:
        Vertex() {
            bVisited = false;
        }
        int data;
        EdgeList edgeList;
        bool bVisited;
    };
        
    Graph::Graph() {
        
    }

    Graph::~Graph() {
        for (std::list<Vertex*>::const_iterator iter = _verticesList.begin(); iter != _verticesList.end(); ++iter) {
            Vertex * vertex = *iter;
            std::list<Edge*> edgeList = vertex->edgeList;
            for (std::list<Edge*>::const_iterator edgeIter = edgeList.begin(); edgeIter != edgeList.end(); ++edgeIter) {
                delete *edgeIter;
            }
            
            delete vertex;
        }
    }

    bool Graph::isEmpty() {
        return _verticesList.empty();
    }

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
        
        Vertex* srcVertex = NULL;
        Vertex* dstVertex = NULL;
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

    int Graph::getCostForEdge(int srcData, int dstData) {
        DataVertexMap::const_iterator srcIter = _dataVertexMap.find(srcData);
        DataVertexMap::const_iterator dstIter = _dataVertexMap.find(dstData);
        
        if(srcIter == _dataVertexMap.end() || dstIter == _dataVertexMap.end())
            return -1;
        
        EdgeList edgeList = (*(srcIter->second))->edgeList;
        for (EdgeList::const_iterator iter = edgeList.begin(); iter != edgeList.end(); ++iter) {
            Edge* edge  = *iter;
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
            for (EdgeList::const_iterator iter = edgeList.begin(); iter != edgeList.end(); ++iter) {
                Edge *edge = *iter;
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
            for (EdgeList::const_iterator iter = edgeList.begin(); iter != edgeList.end(); ++iter) {
                Edge *edge = *iter;
                Vertex *dstVertex = edge->dstVertex;
                if(!dstVertex->bVisited)
                    //we can also have a check here if vertex is already in queue, but since we are using pointer if a duplicate vertex is encountered later then it will have bVisited true.
                    verticesQueue.push(dstVertex);
            }
        }
        
        //TODO: mark visited back to false for each node.

    }

}