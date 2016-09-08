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
#include "Microsoft.h"
#include "Leet.h"
#include "trie.h"
#include "algorithms.h"

void testStringFunctions();
void testAtoi();
void testGraph();
void testGraphMST();
int findDigits();
void testTrie();
void testIncreasingTriplet();

int main(int argc, char* argv[]) {

    
    //testStringFunctions();
    //testAtoi();
    
   // double result = Practice::evalPostfix("623+-382/+*2$3+");   //result = 52
    //printf("Postfix result: %lf", result);
    
   // std::string postfix = Practice::getPostfixFromInfix("((A-(B+C))*D)$(E+F)");
    //printf("%s", postfix.c_str());
    //testGraph();
    
    //testGraphMST();
    
    //findDigits();
    
   // std::string str= "Hello World";
    //removeDup(str);
    
   /* int a[11] = { 1, 1, 1, 1, 1, 1, 0, 1, 1,1,1}; //{8,12,18,22,25,30,37,40,49,75,5};
    int foundIdx = findEleRotatedSortedArr(a, 11, 0);
    printf("Found element at %d", foundIdx);*/
    
  //  string result = Solution::fractionToDecimal(-2147483648, -1);
     //   string result = Solution::fractionToDecimal(1,99);
  //  printf("\nResult: %s\n", result.c_str());
    
   /* vector<int> input;
    input.push_back(1);
    input.push_back(2);
    input.push_back(1);
    input.push_back(2);
    input.push_back(1);
    Solution::permuteUnique(input); */
    
    
   /* vector<int> input;
    input.push_back(-3);
    input.push_back(4);
    input.push_back(-1);
    input.push_back(-1);
    int res = Solution::firstMissingPositive(input);
    printf("\nResult: %d\n", res); */
    
  /*  vector<string> strs;
    strs.push_back("abcdefghij");
    strs.push_back("");
    strs.push_back("abcdefgdsfds");
    strs.push_back("fbcdfvfsij");

    string result = Solution::longestCommonPrefix(strs);
    printf("\nResult: %s\n", result.c_str()); */
    
   /* string inputStr = "aaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffgggggggggghhhhhhhhhhiiiiiiiiiijjjjjjjjjjkkkkkkkkkkllllllllllmmmmmmmmmmnnnnnnnnnnooooooooooppppppppppqqqqqqqqqqrrrrrrrrrrssssssssssttttttttttuuuuuuuuuuvvvvvvvvvvwwwwwwwwwwxxxxxxxxxxyyyyyyyyyyzzzzzzzzzzyyyyyyyyyyxxxxxxxxxxwwwwwwwwwwvvvvvvvvvvuuuuuuuuuuttttttttttssssssssssrrrrrrrrrrqqqqqqqqqqppppppppppoooooooooonnnnnnnnnnmmmmmmmmmmllllllllllkkkkkkkkkkjjjjjjjjjjiiiiiiiiiihhhhhhhhhhggggggggggffffffffffeeeeeeeeeeddddddddddccccccccccbbbbbbbbbbaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffgggggggggghhhhhhhhhhiiiiiiiiiijjjjjjjjjjkkkkkkkkkkllllllllllmmmmmmmmmmnnnnnnnnnnooooooooooppppppppppqqqqqqqqqqrrrrrrrrrrssssssssssttttttttttuuuuuuuuuuvvvvvvvvvvwwwwwwwwwwxxxxxxxxxxyyyyyyyyyyzzzzzzzzzzyyyyyyyyyyxxxxxxxxxxwwwwwwwwwwvvvvvvvvvvuuuuuuuuuuttttttttttssssssssssrrrrrrrrrrqqqqqqqqqqppppppppppoooooooooonnnnnnnnnnmmmmmmmmmmllllllllllkkkkkkkkkkjjjjjjjjjjiiiiiiiiiihhhhhhhhhhggggggggggffffffffffeeeeeeeeeeddddddddddccccccccccbbbbbbbbbbaaaa";
    string result = Solution::longestPalindrome(inputStr);
    printf("\nResult: %s\n", result.c_str());*/
    
    /*vector<Interval> input;
    input.push_back(*(new Interval(4,5)));
    input.push_back(*(new Interval(2,10)));
    input.push_back(*(new Interval(5,6)));
    input.push_back(*(new Interval(15,18)));
    vector<Interval> result = Solution::merge(input); */
    
    //testTrie();
    
    
    //testIncreasingTriplet();
    
   // Algorithms::test::testLCS();
    
   // Solution::test::testThreeSum();
    
    //Solution::test::testSortedListToBST();
    
    //Solution::test::testIntegerBreak();
    
    Solution::test::testSurroundingRegions();
    
   // return 0;
}

void testTrie() {
    Trie* trie = new Trie();
    trie->insertWord("hello");
    trie->insertWord("hell");
    trie->insertWord("world");
    trie->insertWord("worth");
    trie->insertWord("heading");
    trie->insertWord("he");
    trie->insertWord("won");
    
    trie->printAllWords();
}

void testStringFunctions() {

    const char *a = "Hello World";
    
    size_t len = Practice::strlen(a);
  //  size_t lenNull = Practice::strlen(NULL);
    
    char* b = (char*) calloc(len * sizeof(char), 0);
    Practice::strcpy(b, a);
    
    char* c = NULL;

    Practice::strcpy(c, a);
    
    
    const char *d = "Hello World";
    const char* e = "Good Bye";
    
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
    graph->addEdge(0, 1, 2);
    graph->addEdge(1, 2, 3);
    graph->addEdge(0, 3, 6);
    graph->addEdge(1, 3, 8);
    graph->addEdge(1, 4, 5);
    graph->addEdge(3, 4, 9);
    graph->addEdge(2, 4, 7);
    
    graph->addEdge(1, 0, 2);
    graph->addEdge(2, 1, 3);
    graph->addEdge(3, 0, 6);
    graph->addEdge(3, 1, 8);
    graph->addEdge(4, 1, 5);
    graph->addEdge(4, 3, 9);
    graph->addEdge(4, 2, 7);
    
    graph->kruskalMST();
    graph->primMST();
}

int findDigits() {
    using namespace std;
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int noTest;
    cin>>noTest;
    
    std::vector<long long int> testCaseVector;
    for(int i = 0; i < noTest; ++i) {
        long long int x;
        cin>>x;
        testCaseVector.push_back(x);
    }
    cout<<50;
    for(int i = 0; i < noTest; ++i) {
        int arr[10] = {0};
        int count = 0;
        long long int no = testCaseVector[i];
        long long int tmpNo = no;
        while(tmpNo > 0) {
            int rem = tmpNo % 10;
            if(!rem) {
                tmpNo /= 10;
                continue;
            }
            if(!arr[rem]) {
                if((no / rem) == 0 ) {
                    arr[rem] = 1;
                    count++;
                }
            } else
                count++;
        }
        cout<<count<<endl;
    }
    return 0;
}

void testIncreasingTriplet() {
   // int arr[] = {1,2};
   // int arr[] = {1,2, 3,4,5};
   // int arr[] = {5,4,3,2,1};
   // int arr[] = {6,5,2,9,7,8};
   // int arr[] = {1,5,4,3,2};
   // int arr[] = {7,5,2,8,4,3};
    
    //Failed test case
    int arr[] = {1, 2, -10, -8, -7};
    
    vector<int> nums(arr, arr + sizeof(arr) / sizeof(int));

    bool result = Solution::increasingTriplet(nums);
    if(result)
        cout<<"True"<<endl;
    else
        cout<<"False"<<endl;
}