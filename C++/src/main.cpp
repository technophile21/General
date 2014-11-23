//
//  main.cpp
//  Practice
//
//  Created by Manik Singhal on 6/7/14.
//  Copyright (c) 2014 Manik Singhal. All rights reserved.
//

#include <iostream>

#include "Practice.h"
#include <vector>
#include "Graphs.h"

void testStringFunctions();
void testAtoi();
void testGraph();
void testGraphMST();

int main(int argc, char* argv[]) {

    //testStringFunctions();
    //testAtoi();
    
   // double result = Practice::evalPostfix("623+-382/+*2$3+");   //result = 52
    //printf("Postfix result: %lf", result);
    
   // std::string postfix = Practice::getPostfixFromInfix("((A-(B+C))*D)$(E+F)");
    //printf("%s", postfix.c_str());
    //testGraph();
    
    testGraphMST();
    
    return 0;
}

void testStringFunctions() {

    char *a = "Hello World";
    
    size_t len = Practice::strlen(a);
  //  size_t lenNull = Practice::strlen(NULL);
    
    char* b = (char*) calloc(len * sizeof(char), 0);
    Practice::strcpy(b, a);
    
    char* c = NULL;

    Practice::strcpy(c, a);
    
    
    char *d = "Hello World";
    char* e = "Good Bye";
    
    printf("Comparison results: %d - %d - %d - %d \n", Practice::strcmp(a, d), Practice::strcmp(e, d), Practice::strcmp(NULL, NULL), Practice::strcmp(e,c));
    
   // printf("Comparison results with std func. : %d - %d - %d - %d \n", strcmp(a, d), strcmp(e, d), strcmp(0, 0), strcmp(e,0));

    
    printf("Final strings: b: %s \n c: %s", b, c);
    
    free(b);
    
}

void testAtoi() {
    printf("\nTest 1: %d", Practice::atoi("123"));
    printf("\nTest 2: %d", Practice::atoi("-456"));
    printf("\nTest 3: %d", Practice::atoi("+789"));
    try {
        printf("\nTest 4: %d", Practice::atoi("12a3"));
    } catch(Practice::InvalidArgumentException) {
        printf("\nException occured for input: %s", "12a3");
    }
    
    try {
        printf("\nTest 4: %d", Practice::atoi(""));
    } catch(Practice::InvalidArgumentException) {
        printf("\nException occured for input: %s", "");
    }

}

void testGraph() {
    DS::Graph *graph = new DS::Graph();
    graph->addEdge(1, 2, 12);
    graph->addEdge(1, 3, 4);
    //graph->addEdge(1, 4, 3);
   // graph->addEdge(2, 5, 6);
   // graph->addEdge(2, 4, 3);
    graph->addEdge(3, 2, 5);
   // graph->addEdge(3, 5, 2);
   // graph->addEdge(4, 6, 4);
   // graph->addEdge(5, 6, 3);
    
    //graph->dfsTraversal();
    //graph->bfsTraversal();
    graph->findShortestPath(1, 2);
}

void testGraphMST() {
    DS::Graph *graph = new DS::Graph();
    graph->addEdge(0, 1, 10);
    graph->addEdge(0, 2, 6);
    graph->addEdge(0, 3, 5);
    graph->addEdge(1, 3, 15);
    graph->addEdge(2, 3, 4);
    
    graph->kruskalMST();
}