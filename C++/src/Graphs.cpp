//
//  Graphs.cpp
//  Practice
//
//  Created by Manik Singhal on 11/6/14.
//  Copyright (c) 2014 Manik Singhal. All rights reserved.
//

#include <stack>
#include <queue>
#include <set>
#include <map>
#include "Graphs.h"
#include "boost/scoped_ptr.hpp"
#include "boost/weak_ptr.hpp"

#define INFINITY 99999
//Refer for better approach: http://codereview.stackexchange.com/questions/36464/coding-and-printing-a-graph

namespace DS {

    //Declaring Vertex and Edge here will hide their structure from client.
    class Vertex;

    struct Edge {
        int cost;
        boost::weak_ptr<Vertex> srcVertex;
        boost::weak_ptr<Vertex> dstVertex;
    };

    typedef std::list<boost::shared_ptr<Edge>> EdgeList;
    
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
        /*for(Vertex* vertex: _verticesList) {
            std::list<Edge*> edgeList = vertex->edgeList;
            for(Edge *edge : edgeList) {
                delete edge;
            }
            
            delete vertex;
        }*/
    }

    // Const Correctness: http://www.cprogramming.com/tutorial/const_correctness.html
    bool Graph::isEmpty() const {
        return _verticesList.empty();
    }

    /* Exception safety:
     Here, you are allocating memory for a Vertex, then you try to add it at the end of _verticesList. When inserting an element in an std::list, a new node should be allocated. Unless otherwise specified, std::list uses std::allocator to allocate new memory, which is based on new and delete. In other words, if there is no more free memory to allocate for the new node, new will throw an std::bad_alloc exception and insert will rethrow the exception. In addVertex, if insert throws, then the newly allocated Vertex (node) will not be freed. This is a memory leak, and so your method fails to provide the basic exception safety (also known as no-leak guarantee).
     
     */
    void Graph::addVertex(int data) {
        boost::shared_ptr<Vertex> node(new Vertex());
        node->data = data;
        node->edgeList.clear();
        
        VerticesList::const_iterator iter = _verticesList.insert(_verticesList.end(), node);
        _dataVertexMap.insert(std::make_pair(data, iter));
    }

    boost::shared_ptr<Vertex> Graph::addAndGetVertex(int data) {
        boost::shared_ptr<Vertex> node(new Vertex());
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
        
        boost::shared_ptr<Vertex> srcVertex(nullptr);
        boost::shared_ptr<Vertex> dstVertex(nullptr);
        if(srcIter == _dataVertexMap.end())
            srcVertex = addAndGetVertex(srcData);
        else
            srcVertex = *(srcIter->second);
        
        if(dstIter == _dataVertexMap.end())
            dstVertex = addAndGetVertex(dstData);
        else
            dstVertex = *(dstIter->second);
        
        boost::shared_ptr<Edge> newEdge(new Edge());
        newEdge->cost = cost;
        newEdge->srcVertex = srcVertex;
        newEdge->dstVertex = dstVertex;
        
        //list will make a copy of newEdge shared ptr
        srcVertex->edgeList.push_back(newEdge);
        
    }

    int Graph::getCostForEdge(int srcData, int dstData) {
        DataVertexMap::const_iterator srcIter = _dataVertexMap.find(srcData);
        DataVertexMap::const_iterator dstIter = _dataVertexMap.find(dstData);
        
        if(srcIter == _dataVertexMap.end() || dstIter == _dataVertexMap.end())
            return INFINITY;
        
        EdgeList edgeList = (*(srcIter->second))->edgeList;
        
        //C++11: Range based for loop
        for (boost::shared_ptr<Edge> edge : edgeList) {
            //Notice the comparison syntax
            if((edge->dstVertex).lock().get()  == (*(dstIter->second)).get())
                return edge->cost;
        }
        
        return INFINITY;
    }
        
    void Graph::displayGraph() {
        
    }

    void Graph::dfsTraversal() {
        std::stack<boost::weak_ptr<Vertex>> vertexStack;
        vertexStack.push(_verticesList.front());
        
        while(!vertexStack.empty())
        {
            boost::shared_ptr<Vertex> vertex = vertexStack.top().lock();
            vertexStack.pop();
            
            assert(vertex.get() != nullptr);
            
            vertex->bVisited = true;
            printf("%d\n", vertex->data);
            const EdgeList edgeList = vertex->edgeList;
            for (boost::shared_ptr<Edge> edge : edgeList) {
                boost::shared_ptr<Vertex> dstVertex = (edge->dstVertex).lock();
                assert(dstVertex.get() != nullptr);
                if(!dstVertex->bVisited)
                    vertexStack.push(dstVertex);
            }
        }
        
        //TODO: mark visited back to false for each node.
        
    }
    
    void Graph::bfsTraversal() {
        std::queue<boost::weak_ptr<Vertex>> verticesQueue;
        verticesQueue.push(_verticesList.front());
        
        while(!verticesQueue.empty())
        {
            boost::shared_ptr<Vertex> vertex = (verticesQueue.front()).lock();
            verticesQueue.pop();
            
            assert(vertex.get() != nullptr);
            
            if(vertex->bVisited) continue;
            
            vertex->bVisited = true;
            printf("%d\n", vertex->data);
            const EdgeList edgeList = vertex->edgeList;
            for (boost::shared_ptr<Edge> edge : edgeList) {
                boost::shared_ptr<Vertex> dstVertex = (edge->dstVertex).lock();
                assert(dstVertex.get() != nullptr);
                if(!dstVertex->bVisited)
                    //we can also have a check here if vertex is already in queue, but since we are using pointer if a duplicate vertex is encountered later then it will have bVisited true.
                    verticesQueue.push(dstVertex);
            }
        }
        
        //TODO: mark visited back to false for each node.

    }
    
    void Graph::findShortestPath(int srcData, int dstData) {
        DataVertexMap::const_iterator srcIter = _dataVertexMap.find(srcData);
        DataVertexMap::const_iterator dstIter = _dataVertexMap.find(dstData);
        if(srcIter == _dataVertexMap.end() || dstIter == _dataVertexMap.end())
            assert(false);
    
        boost::shared_ptr<Vertex> srcVertex(*(srcIter->second));
        boost::shared_ptr<Vertex> dstVertex(*(dstIter->second));
        
        struct VertexInfo {
            bool bGotMinDistance = false;
            boost::weak_ptr<Vertex> precedingVertex;
            int distanceFromSource = INFINITY;
        };
        
        boost::shared_ptr<Vertex> currentVertex = srcVertex;
        
        typedef std::map<boost::shared_ptr<Vertex>, VertexInfo> VertexInfoMap;
        VertexInfoMap vertexInfoMap;
        for(boost::shared_ptr<Vertex> vertex : _verticesList) {
            VertexInfo info;
            if(vertex.get() == srcVertex.get()) {
                info.bGotMinDistance = true;
                info.distanceFromSource = 0;
                info.precedingVertex = boost::weak_ptr<Vertex> ();
            }
            vertexInfoMap.insert(std::make_pair(vertex, info));
        }
        
        
        while(currentVertex.get() != dstVertex.get()) {
            VertexInfo& curVertexInfo = vertexInfoMap[currentVertex];
            curVertexInfo.bGotMinDistance = true;
            boost::shared_ptr<Vertex> minDistVertex = currentVertex;
            int curMinDist  = INFINITY;
            for(auto iter = vertexInfoMap.begin(); iter != vertexInfoMap.end(); ++iter) {
                boost::shared_ptr<Vertex> vertex = iter->first;
                VertexInfo& vertexInfo = iter->second;
                if(!vertexInfo.bGotMinDistance) {
                    int distFromCurToVertex = getCostForEdge(currentVertex->data, vertex->data);
                    if(vertexInfo.distanceFromSource > distFromCurToVertex + curVertexInfo.distanceFromSource) {
                        vertexInfo.distanceFromSource = distFromCurToVertex + curVertexInfo.distanceFromSource;
                        vertexInfo.precedingVertex = currentVertex;
                    }
                
                    if(vertexInfo.distanceFromSource < curMinDist) {
                        curMinDist = vertexInfo.distanceFromSource;
                        minDistVertex = vertex;
                    }
                }
            }
            currentVertex = minDistVertex;
            //WRONG: A reference variable cannot be reassigned
            //curVertexInfo = vertexInfoMap[currentVertex];//vertexInfoMap.find(currentVertex)->second;
        }
        
        for(boost::shared_ptr<Vertex> vertex = dstVertex; vertex.get() != srcVertex.get(); ) {
            printf("%d\n", vertex->data);
            VertexInfo info = vertexInfoMap[vertex];
            vertex = info.precedingVertex.lock();
        }
        printf("%d\n", srcVertex->data);
        
    }
    
    class CompareEdge {
    public:
        bool operator() (const boost::shared_ptr<Edge> & e1, const boost::shared_ptr<Edge> & e2) const{
            if(e1->cost == e2->cost)
                return e1.get() < e2.get();  //similar to default comparator less<T>
            
            return e1->cost < e2->cost;
        }
    };
    
    typedef std::map<boost::shared_ptr<Vertex>, boost::shared_ptr<Vertex>> ParentMap;
    // A utility function to find the subset of an element i
    boost::shared_ptr<Vertex> find(const ParentMap& parentMap, const boost::shared_ptr<Vertex>& vertex)
    {
        ParentMap::const_iterator iter = parentMap.find(vertex);
        if (!(iter->second).get())
            return vertex;
        return find(parentMap, iter->second);
    }
    
    // A utility function to do union of two subsets
    void Union(ParentMap& parentMap, const boost::shared_ptr<Vertex>& x, const boost::shared_ptr<Vertex>& y)
    {
        const boost::shared_ptr<Vertex> xset = find(parentMap, x);
        const boost::shared_ptr<Vertex> yset = find(parentMap, y);
        parentMap[x] = y;
    }
    
    
    // The main function to check whether a given graph contains cycle or not
    bool isCycle(const VerticesList& verticesList, const EdgeList& allEdgeList)
    {
        // Allocate memory for creating V subsets
        ParentMap parent;
        
        for(boost::shared_ptr<Vertex> vertex : verticesList) {
            parent.insert(std::make_pair(vertex, nullptr));
        }
        
        // Iterate through all edges of graph, find subset of both
        // vertices of every edge, if both subsets are same, then there is
        // cycle in graph.
        for(boost::shared_ptr<Edge> edge : allEdgeList)
        {
            boost::shared_ptr<Vertex> x = find(parent, (edge->srcVertex).lock());
            boost::shared_ptr<Vertex> y = find(parent, (edge->dstVertex).lock());
            
            if (x.get() == y.get())
                return true;
            
            Union(parent, x, y);
        }
        return false;
    }
    
    void Graph::kruskalMST() {
        std::set<boost::shared_ptr<Edge>, CompareEdge> allEdgeList;
        for(boost::shared_ptr<Vertex> vertex : _verticesList) {
            EdgeList vertexEdgeList = vertex->edgeList;
            allEdgeList.insert(vertexEdgeList.begin(), vertexEdgeList.end());
        }
        
        EdgeList mstEdgeList;
        for(boost::shared_ptr<Edge> edge : allEdgeList) {
            if(mstEdgeList.size() == _verticesList.size() - 1) break;
            mstEdgeList.push_front(edge);
            if(isCycle(_verticesList, mstEdgeList)) {
                mstEdgeList.pop_front();
            }
        }
        
        // print the contents of result[] to display the built MST
        printf("Following are the edges in the constructed MST\n");
        for (boost::shared_ptr<Edge> edge : mstEdgeList)
            printf("%d -- %d == %d\n", (edge->srcVertex).lock()->data, (edge->dstVertex).lock()->data,
                   edge->cost);
        return;
    }
    
    boost::shared_ptr<Edge> getMinEdge(EdgeList& edgeList) {
        int min = INFINITY;
        boost::shared_ptr<Edge> minEdge;
        for(boost::shared_ptr<Edge> edge : edgeList) {
            if(edge->cost < min) {
                min = edge->cost;
                minEdge = edge;
            }
        }
        
        return minEdge;
    }
    
    void Graph::primMST() {
        EdgeList mstEdgeList;
        EdgeList potentialEdgeList;
        //VertexKeyMap keyMap;
        /*for(boost::shared_ptr<Vertex> vertex : _verticesList) {
            keyMap.insert(std::make_pair(vertex, INFINITY));
        }*/
        
        //keyMap[_verticesList.front()] = 0;
        boost::shared_ptr<Vertex> firstVertex = _verticesList.front();
        potentialEdgeList.insert(potentialEdgeList.begin(), firstVertex->edgeList.begin(), firstVertex->edgeList.end());
        
        while(mstEdgeList.size() < _verticesList.size() - 1) {
            boost::shared_ptr<Edge> minEdge = getMinEdge(potentialEdgeList);
            mstEdgeList.push_front(minEdge);
            potentialEdgeList.remove(minEdge);
            (minEdge->srcVertex).lock()->bVisited = true;
            (minEdge->dstVertex).lock()->bVisited = true;
            EdgeList dstVertexEdgeList = (minEdge->dstVertex).lock()->edgeList;
            for(boost::shared_ptr<Edge> edge : dstVertexEdgeList) {
                if(!(edge->dstVertex).lock()->bVisited)
                    potentialEdgeList.push_front(edge);
            }
        }
        
        //TODO: set all bvisited false
        
        // print the contents of result[] to display the built MST
        printf("Following are the edges in the constructed MST\n");
        for (boost::shared_ptr<Edge> edge : mstEdgeList)
            printf("%d -- %d == %d\n", (edge->srcVertex).lock()->data, (edge->dstVertex).lock()->data,
                   edge->cost);
        return;

    }

}