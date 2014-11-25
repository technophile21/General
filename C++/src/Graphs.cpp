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
        VertexSharedPtr srcVertex;
        VertexSharedPtr dstVertex;
    };

    typedef boost::shared_ptr<Edge> EdgeSharedPtr;
    typedef std::list<EdgeSharedPtr> EdgeList;
    
    class Vertex {
    public:
        int data = 0;
        EdgeList edgeList;
        bool bVisited = false;   //In C++11 we can initialize member directly
    };
        
    Graph::Graph() {
        
    }

    Graph::~Graph() {
    }

    // Const Correctness: http://www.cprogramming.com/tutorial/const_correctness.html
    bool Graph::isEmpty() const {
        return _verticesList.empty();
    }

    /* Exception safety:
     Here, you are allocating memory for a Vertex, then you try to add it at the end of _verticesList. When inserting an element in an std::list, a new node should be allocated. Unless otherwise specified, std::list uses std::allocator to allocate new memory, which is based on new and delete. In other words, if there is no more free memory to allocate for the new node, new will throw an std::bad_alloc exception and insert will rethrow the exception. In addVertex, if insert throws, then the newly allocated Vertex (node) will not be freed. This is a memory leak, and so your method fails to provide the basic exception safety (also known as no-leak guarantee).
     
     */
    void Graph::addVertex(int data) {
        VertexSharedPtr node(new Vertex());
        node->data = data;
        node->edgeList.clear();
        
        VerticesList::const_iterator iter = _verticesList.insert(_verticesList.end(), node);
        _dataVertexMap.insert(std::make_pair(data, iter));
    }

    VertexSharedPtr Graph::addAndGetVertex(int data) {
        VertexSharedPtr node(new Vertex());
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
        
        VertexSharedPtr srcVertex(nullptr);
        VertexSharedPtr dstVertex(nullptr);
        if(srcIter == _dataVertexMap.end())
            srcVertex = addAndGetVertex(srcData);
        else
            srcVertex = *(srcIter->second);
        
        if(dstIter == _dataVertexMap.end())
            dstVertex = addAndGetVertex(dstData);
        else
            dstVertex = *(dstIter->second);
        
        EdgeSharedPtr newEdge(new Edge());
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
        for (auto& edge : edgeList) {
            //Notice the comparison syntax
            if((edge->dstVertex).get()  == (*(dstIter->second)).get())
                return edge->cost;
        }
        
        return INFINITY;
    }
        
    void Graph::displayGraph() {
        
    }

    void Graph::dfsTraversal() {
        std::stack<VertexSharedPtr> vertexStack;
        vertexStack.push(_verticesList.front());
        
        while(!vertexStack.empty())
        {
            VertexSharedPtr& vertex = vertexStack.top();
            vertexStack.pop();
            
            assert(vertex.get() != nullptr);
            
            vertex->bVisited = true;
            printf("%d\n", vertex->data);
            const EdgeList& edgeList = vertex->edgeList;
            for (auto& edge : edgeList) {
                VertexSharedPtr& dstVertex = edge->dstVertex;
                assert(dstVertex.get() != nullptr);
                if(!dstVertex->bVisited)
                    vertexStack.push(dstVertex);
            }
        }
        
        //TODO: mark visited back to false for each node.
        
    }
    
    void Graph::bfsTraversal() {
        std::queue<VertexSharedPtr> verticesQueue;
        verticesQueue.push(_verticesList.front());
        
        while(!verticesQueue.empty())
        {
            VertexSharedPtr& vertex = verticesQueue.front();
            verticesQueue.pop();
            
            assert(vertex.get() != nullptr);
            
            if(vertex->bVisited) continue;
            
            vertex->bVisited = true;
            printf("%d\n", vertex->data);
            const EdgeList& edgeList = vertex->edgeList;
            for (auto& edge : edgeList) {
                VertexSharedPtr& dstVertex = edge->dstVertex;
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
    
        VertexSharedPtr srcVertex(*(srcIter->second));
        VertexSharedPtr dstVertex(*(dstIter->second));
        
        struct VertexInfo {
            bool bGotMinDistance = false;
            VertexSharedPtr precedingVertex;
            int distanceFromSource = INFINITY;
        };
        
        VertexSharedPtr currentVertex = srcVertex;
        
        typedef std::map<VertexSharedPtr, VertexInfo> VertexInfoMap;
        VertexInfoMap vertexInfoMap;
        for(auto& vertex : _verticesList) {
            VertexInfo info;
            if(vertex.get() == srcVertex.get()) {
                info.bGotMinDistance = true;
                info.distanceFromSource = 0;
                info.precedingVertex = VertexSharedPtr ();
            }
            vertexInfoMap.insert(std::make_pair(vertex, info));
        }
        
        
        while(currentVertex.get() != dstVertex.get()) {
            VertexInfo& curVertexInfo = vertexInfoMap[currentVertex];
            curVertexInfo.bGotMinDistance = true;
            VertexSharedPtr minDistVertex = currentVertex;
            int curMinDist  = INFINITY;
            for(auto iter = vertexInfoMap.begin(); iter != vertexInfoMap.end(); ++iter) {
                VertexSharedPtr vertex = iter->first;
                VertexInfo vertexInfo = iter->second;
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
        
        for(VertexSharedPtr& vertex = dstVertex; vertex.get() != srcVertex.get(); ) {
            printf("%d\n", vertex->data);
            VertexInfo info = vertexInfoMap[vertex];
            vertex = info.precedingVertex;
        }
        printf("%d\n", srcVertex->data);
        
    }
    
    class CompareEdge {
    public:
        bool operator() (const EdgeSharedPtr & e1, const EdgeSharedPtr & e2) const{
            if(e1->cost == e2->cost)
                return e1.get() < e2.get();  //similar to default comparator less<T>
            
            return e1->cost < e2->cost;
        }
    };
    
    typedef std::map<VertexSharedPtr, VertexSharedPtr> ParentMap;
    // A utility function to find the subset of an element i
    VertexSharedPtr find(const ParentMap& parentMap, const VertexSharedPtr& vertex)
    {
        ParentMap::const_iterator iter = parentMap.find(vertex);
        if (!(iter->second).get())
            return vertex;
        return find(parentMap, iter->second);
    }
    
    // A utility function to do union of two subsets
    void Union(ParentMap& parentMap, const VertexSharedPtr& x, const VertexSharedPtr& y)
    {
        const VertexSharedPtr xset = find(parentMap, x);
        const VertexSharedPtr yset = find(parentMap, y);
        parentMap[x] = y;
    }
    
    
    // The main function to check whether a given graph contains cycle or not
    bool isCycle(const VerticesList& verticesList, const EdgeList& allEdgeList)
    {
        // Allocate memory for creating V subsets
        ParentMap parent;
        
        for(auto& vertex : verticesList) {
            parent.insert(std::make_pair(vertex, nullptr));
        }
        
        // Iterate through all edges of graph, find subset of both
        // vertices of every edge, if both subsets are same, then there is
        // cycle in graph.
        for(auto& edge : allEdgeList)
        {
            VertexSharedPtr x = find(parent, (edge->srcVertex));
            VertexSharedPtr y = find(parent, (edge->dstVertex));
            
            if (x.get() == y.get())
                return true;
            
            Union(parent, x, y);
        }
        return false;
    }
    
    void Graph::kruskalMST() {
        std::set<EdgeSharedPtr, CompareEdge> allEdgeList;
        for(auto& vertex : _verticesList) {
            EdgeList& vertexEdgeList = vertex->edgeList;
            allEdgeList.insert(vertexEdgeList.begin(), vertexEdgeList.end());
        }
        
        EdgeList mstEdgeList;
        for(auto edge : allEdgeList) {
            if(mstEdgeList.size() == _verticesList.size() - 1) break;
            mstEdgeList.push_front(edge);
            if(isCycle(_verticesList, mstEdgeList)) {
                mstEdgeList.pop_front();
            }
        }
        
        // print the contents of result[] to display the built MST
        printf("Following are the edges in the constructed MST\n");
        for (auto& edge : mstEdgeList)
            printf("%d -- %d == %d\n", (edge->srcVertex)->data, (edge->dstVertex)->data,
                   edge->cost);
        return;
    }
    
    /*EdgeSharedPtr getMinEdge(const EdgeList& edgeList) {
        int min = INFINITY;
        EdgeSharedPtr minEdge;
        for(auto& edge : edgeList) {
            if(edge->cost < min) {
                min = edge->cost;
                minEdge = edge;
            }
        }
        
        return minEdge;
    }*/
    
    boost::shared_ptr<Edge> getMinEdge(const EdgeList& edgeList)
    {
        return *std::min_element(edgeList.begin(),edgeList.end()
                                 , [](boost::shared_ptr<Edge> const& a
                                      , boost::shared_ptr<Edge> const& b)
                                 { return a->cost < b->cost; });
    }
    
    void Graph::primMST() {
        EdgeList mstEdgeList;
        EdgeList potentialEdgeList;
        
        const VertexSharedPtr& firstVertex = _verticesList.front();
        potentialEdgeList.insert(potentialEdgeList.begin(), firstVertex->edgeList.begin(), firstVertex->edgeList.end());
        
        while(mstEdgeList.size() < _verticesList.size() - 1) {
            EdgeSharedPtr minEdge = getMinEdge(potentialEdgeList);
            mstEdgeList.push_front(minEdge);
            potentialEdgeList.remove(minEdge);
            //Mark the vertices visited so that edge having them as destination are not again included again
            (minEdge->srcVertex)->bVisited = true;
            (minEdge->dstVertex)->bVisited = true;
            EdgeList& dstVertexEdgeList = (minEdge->dstVertex)->edgeList;
            for(EdgeSharedPtr edge : dstVertexEdgeList) {
                if(!(edge->dstVertex)->bVisited)
                    potentialEdgeList.push_front(edge);
            }
        }
        
        //TODO: set all bvisited false
        
        // print the contents of result[] to display the built MST
        printf("Following are the edges in the constructed MST\n");
        for (auto& edge : mstEdgeList)
            printf("%d -- %d == %d\n", (edge->srcVertex)->data, (edge->dstVertex)->data,
                   edge->cost);
        return;

    }

}