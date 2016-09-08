//
//  trie.cpp
//  Practice
//
//  Created by Manik Singhal on 6/19/16.
//  Copyright (c) 2016 Manik Singhal. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <vector>
#include "algorithms.h"

using namespace std;

namespace Algorithms {
    
    typedef vector<vector<int>> Array2D;

    namespace Helpers {
        int getLCSHelper(Array2D& l, const std::string& a, const std::string& b, int i, int j) {
            if (i < 0 || j < 0) {
                return 0;
            }
            
            //we have computed this
            if(l[i][j] != -1) {
                return l[i][j];
            }
            
            if(a[i] == b[j]) {
                l[i][j] = 1 + getLCSHelper(l, a, b, i - 1, j - 1);
            } else {
                int lcs1 = getLCSHelper(l, a, b, i - 1, j);
                int lcs2 = getLCSHelper(l, a, b, i, j - 1);
                if(lcs1 > lcs2)
                    l[i][j] = lcs1;
                else
                    l[i][j] = lcs2;
            }
            
            return l[i][j];
        }

    }
    
    //get longest common subsequence
    int getLCS(const std::string& a, const std::string& b, std::string& result) {
        if(a.empty() || b.empty()) return 0;
        
        Array2D l;
        for(int i = 0; i < a.size(); ++i) {
            vector<int> t;
            for(int j =0; j < b.size(); ++j) {
                t.push_back(-1);
            }
            l.push_back(t);
        }
        
        int length = Helpers::getLCSHelper(l, a, b, (int)a.size() - 1, (int)b.size() - 1);
        return length;
    }
    
    namespace test {
        void testLCS() {
            std::string result = "";
            int len = getLCS("ABCDGH", "AEDFHR", result);
            
            std::cout<<len<<endl;
        }
    }
}