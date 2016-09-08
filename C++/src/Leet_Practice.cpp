//
//  Leet_Practice.cpp
//  Practice
//
//  Created by Manik Singhal on 5/9/15.
//  Copyright (c) 2015 Manik Singhal. All rights reserved.
//

#include "Leet.h"
#include "types.h"
#include "algorithms.h"

namespace Solution {
    Vector2D<int> permuteResult;
}

/*Failures: 
 1. Didn't handle for -ve integers
 2. For negative INT_MIN it was failing as INT_MIN doesn't have a corresponding positive rep.

 */
string Solution::fractionToDecimal(int numerator, int denominator)
{
    string result = "";
    if(denominator == 0) return result;
    
    if((numerator < 0 && denominator > 0) || (denominator < 0 && numerator > 0))
        result += "-";
    
    long int num  = numerator < 0 ? -1L * numerator : numerator;
    long int den = denominator < 0 ? -1L * denominator : denominator;
    
    long tmp = num / den;
    if(tmp) {
        result += to_string(tmp);
        num %= den;
    }   else {
        num = abs(num);
        den = abs(den);
        result += "0";
    }
    
    string fractionalPart = "";
    if(num) {
        fractionalPart += ".";
                    num *= 10;
        while(num < den) {
            fractionalPart += "0";
                        num *= 10;
        }
    }
    num /= 10;
    while(num) {
        num *= 10;
        while(num < den) {
            size_t idx = fractionalPart.find('0');
            if(idx != string::npos) {
                for(int i = 0; i < fractionalPart.length(); ++i) {
                    if(i == idx)
                        result += "(";
                    result += fractionalPart[i];
                }
                result += ")";
                break;
            } else {
                fractionalPart += "0";
                num *= 10;
            }
        }
        
        if(num < den) break;
        
        int tmp = num / den;
        char c = '0' + tmp;
        size_t idx = fractionalPart.find(c);
        if(idx != string::npos) {
            for(int i = 0; i < fractionalPart.length(); ++i) {
                if(i == idx)
                    result += "(";
                result += fractionalPart[i];
            }
            result += ")";
            break;
        } else {
            fractionalPart += to_string(tmp);
            num %= den;
        }
    }
    if(!num) {
        for(int i = 0; i < fractionalPart.length(); ++i) {
            result += fractionalPart[i];
        }
    }
    
    return result;
    
    
}


void Solution::reorderList(ListNode* head) {
    if(!head) return;
    
    if(!head->next || !head->next->next) return;
    
    ListNode *mid, *b;
    mid = head;
    b = head;
    while (b->next && b->next->next) {
        mid = mid->next;
        b = b->next->next;
    }
    
    ListNode* a = NULL;
    ListNode* tmpNode = mid->next;
    ListNode* nextNode = NULL;

    mid->next = NULL;
    
    while(tmpNode) {
        nextNode = tmpNode->next;
        tmpNode->next = a;
        a = tmpNode;
        tmpNode = nextNode;
    }
    
    //here 'a' holds last node of original list
    ListNode* tmp = head;
    while(a) {
        ListNode* nextTmp = tmp->next;
        tmp->next = a;
        a = a->next;
        tmp->next->next = nextTmp;
        tmp = nextTmp;
    }
}

void permuteHelper(vector<int>& nums, int fromIdx) {
    if(fromIdx == nums.size() - 1) {
        printf("\n");
        for(int i = 0; i < nums.size() ; ++i)
            printf("%d ", nums[i]);
        Solution::permuteResult.push_back(nums);
        return;
    }
    
    for(size_t i = fromIdx; i < nums.size() ; ++i) {
        if(i == fromIdx || ((nums[fromIdx] != nums[i]) && (nums[i-1] != nums[i]))) {
           /* int tmp = nums[fromIdx];
            nums[fromIdx] = nums[i];
            nums[i] = tmp;*/
            nums.insert(nums.begin() + fromIdx + (fromIdx > i), nums[i]);
            nums.erase(nums.begin() + i + (i > fromIdx));
            permuteHelper(nums, fromIdx + 1);
            nums.insert(nums.begin() + i + (i > fromIdx), nums[fromIdx]);
            nums.erase(nums.begin() + fromIdx + (fromIdx > i));
 /*           tmp = nums[fromIdx];
            nums[fromIdx] = nums[i];
            nums[i] = tmp;*/
        }
    }
}

vector<vector<int>> Solution::permuteUnique(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    permuteHelper(nums, 0);
    return permuteResult;
}

//Test cases, [3,4,-1,1], [1, 1], [2,1]
int Solution::firstMissingPositive(vector<int>& nums) {
    int i = 0;
    if(nums.empty()) return 1;
    while(i < nums.size()) {
        int tmp = nums[i];
        while(tmp > 0 && tmp != i+1 && tmp < nums.size() && nums[tmp - 1] != tmp) {
            swap(nums[i], nums[tmp - 1]);
            tmp = nums[i];
        }
        ++i;
    }
    
    i = 0;
    while(i < nums.size()) {
        if(nums[i] != i + 1) return i + 1;
        ++i;
    }
    
   // if(nums.size() == 1 && nums[0] != 1) return 1;
        
    return nums[nums.size() - 1] + 1;
    
}

//Test cases: [""], ["abc", "def"]
string Solution::longestCommonPrefix(vector<string>& strs) {
    if(strs.empty())
        return "";
    
    string s = strs[0];
    if(s.empty()) return "";
        
    unsigned long level = s.length() - 1;
    for(unsigned long i = 1; i < strs.size(); ++i) {
        string s2 = strs[i];
        if(s2.empty())
            return "";
            
        unsigned long j = 0;
        while(j <= level && s[j] && s2[j] && s[j] == s2[j])
            ++j;
        
        if(j && (j-1) < level)
            level = j - 1;
        else if(!j)
            return "";
    }
    
    string result = "";
    for(unsigned long i = 0; i <= level ; ++i) {
        result += s[i];
    }
    
    return result;
}

namespace  LongestPalindrome{
    unsigned long maxVal = 0;
    unsigned long maxStart = 0;
    int a[1000][1000] = {-1};
    void initArr() {
        memset(a, -1, sizeof(a[0][0]) * 1000 * 1000);
    }
    void longestPalUtil(const string& s, unsigned long start, unsigned long end) {
        if(s.empty()) return;
        
        if(a[start][end] != -1) return;
        
        if(start == end) {
            a[start][end] = 1;
            unsigned long curLen = end - start + 1;
            if(maxVal < curLen) {
                maxVal = curLen;
                maxStart = start;
            }
            return;
        }
        
        longestPalUtil(s, start + 1, end);
        longestPalUtil(s, start, end - 1);
        if(s[start] == s[end])
        {
            if((end == start + 1) || (end - start >= 2 && a[start + 1][end - 1] == 1)) {
                a[start][end] = 1;
                unsigned long curLen = end - start + 1;
                if(maxVal < curLen) {
                    maxVal = curLen;
                    maxStart = start;
                }
            }
        } else
            a[start][end] = 0;
        
    }
}


string Solution::longestPalindrome(string s) {
    if(s.empty()) return "";
    
    string res = "";
    unsigned long len = s.length();
    LongestPalindrome::initArr();
    LongestPalindrome::longestPalUtil(s, 0, len - 1);
    if(LongestPalindrome::maxVal) {
        for(unsigned long i = LongestPalindrome::maxStart; i < LongestPalindrome::maxStart + LongestPalindrome::maxVal; ++i)
            res += s[i];
    }
    return res;
}

bool compareInterval(const Interval& a, const Interval& b) {
    return a.end > b.end; //Mistakes: needed reverse sorting (i did sort increasing order)
}

//Failed for test case : [2,3], [4,6], [7,9], [1, 10]  (needed reverse sorting and accordingly logic change)
vector<Interval> Solution::merge(vector<Interval>& intervals) {
    if(intervals.empty()) return vector<Interval>();
    
    std::sort(intervals.begin(), intervals.end(), compareInterval);
    
    vector<Interval> result;
    Interval lastInterval = intervals[0];
    
    for(int i = 1; i < intervals.size(); ++i) {
        Interval curInterval = intervals[i];
        if((curInterval.end >= lastInterval.start && curInterval.end <= lastInterval.end))
        {
            Interval newInterval(curInterval.start, lastInterval.end);
            if(lastInterval.start <= curInterval.start)
                newInterval.start = lastInterval.start;
            //result.push_back(newInterval);
            lastInterval = newInterval;
        } else {
            result.push_back(lastInterval);
            lastInterval = curInterval;
        }
    }
    result.push_back(lastInterval);
    
    return result;
}



bool Solution::increasingTriplet(vector<int>& nums) {
    if(nums.size() < 3) return false;
    
    int first1 = 0;
    int first2 = 0;
    int second = 0;
    int third = 0;

    int i = 1;
    while((i < nums.size()) && (nums[i] <= nums[first1])) {
        first1 = i;
        ++i;
    }

    while((i < nums.size()) && (second <= first1)) {
        if(nums[i] > nums[first1]) {
            second = i;
            ++i;
            break;
        }
        ++i;
    }

    for (; i < nums.size(); ++i) {
        if(second > 0 && nums[i] > nums[second]) {
            third = i;
            break;
        } else if(nums[i] > nums[first1] && nums[i] < nums[second]) {
            second = i;
            if(nums[first2] < nums[first1]) {
                first1 = first2;
            }
        } else if(nums[i] <= nums[first1]) {
            if(first2 == 0 || nums[i] < nums[first2])
                first2 = i;
            else if(nums[i] > nums[first2]) {
                first1 = first2;
                second = i;
            }
        }
    }
    
    if((first1 < second) && (second < third) && (third < nums.size())) {
        return true;
    }
    
    
    return false;
    
}

std::vector<pair<int, int>> vecPair;

bool exists(int a ,int b) {
    for (auto e : vecPair) {
        if(e.first == a && e.second == b)
            return true;
    }
    
    return false;
}

void threeSumHelper(vector<int>& nums, int a, int b, Vector2D<int>& result) {
    int first = a;
    int last = b;
    if(nums[first] * nums[last] > 0) return;
    
    //there should be at least 3 num
    if (first < last -1) {
        if(exists(nums[first], nums[last])) {
            //means we already have these num in result triplet
            threeSumHelper(nums, a, b - 1, result);
            threeSumHelper(nums, a + 1, b, result);
            return;
        }
        int partialSum = nums[first] + nums[last];
        int need = 0 - partialSum;
        
        int bFoundIdx = Algorithms::binSearch<vector<int>, int>(nums, first + 1, last - 1, need);
        if(bFoundIdx != -1) {
            vecPair.push_back(make_pair(nums[first], need));
            vecPair.push_back(make_pair(need, nums[last]));
            vecPair.push_back(make_pair(nums[first], nums[last]));
            vector<int> triplet;
            triplet.push_back(nums[first]);
            triplet.push_back(need);
            triplet.push_back(nums[last]);
            
            result.push_back(triplet);
            
            threeSumHelper(nums, a, b - 1, result);
            threeSumHelper(nums, a + 1, b, result);
        } else {
            /*if(need < 0) {
                threeSumHelper(nums, a, b - 1, result);
            } else if(need > 0) {
                threeSumHelper(nums, a + 1, b, result);
            } else*/ {
                threeSumHelper(nums, a, b - 1, result);
                threeSumHelper(nums, a + 1, b, result);

            }
        }
    }

}

//bad solution: exceeded time limit
//Correct: http://www.programcreek.com/2012/12/leetcode-3sum/
Vector2D<int> Solution::threeSum(vector<int>& nums) {
    Vector2D<int> result;
    if(nums.size() < 3) return result;
    
    std::sort(nums.begin(), nums.end());
    
    /*if(numHash.empty()) {
        for (int i = 0; i < nums.size(); ++i)
        {
            numHash[nums[i]] = false;
        }
    }*/

    threeSumHelper(nums, 0, (int)nums.size() - 1, result);
    
    return result;
}

void printTree(TreeNode* root, int level, bool bLeft) {
    if(!root) return;
    
    cout<<endl;
    cout<<root->val<<" : "<<level<<" : "<<bLeft;
    printTree(root->left, level + 1, true);
    printTree(root->right, level + 1, false);
}

TreeNode* sortedListToBSTHelper(vector<int>& vec, int startIdx, int lastIdx) {
    if(vec.empty() || (startIdx > lastIdx)) return NULL;
    
    if(startIdx == lastIdx && (startIdx < vec.size())) {
        TreeNode* node = new TreeNode(vec[startIdx]);
        return node;
    }
    
    int midIdx = (startIdx + lastIdx) / 2;
    TreeNode* node = new TreeNode(vec[midIdx]);
    TreeNode* leftSubTree = sortedListToBSTHelper(vec, startIdx, midIdx - 1);
    TreeNode* rightSubTree = sortedListToBSTHelper(vec, midIdx + 1, lastIdx);
    node->left = leftSubTree;
    node->right = rightSubTree;
    
    return node;
}

TreeNode* Solution::sortedListToBST(ListNode* head) {
    vector<int> tmpVec;
    while(head) {
        tmpVec.push_back(head->val);
        head = head->next;
    }
    
    TreeNode* root = sortedListToBSTHelper(tmpVec, 0, (int)tmpVec.size() - 1);
    
    return root;
}

//can also be done by dynamic prog. : similar to breaking rod into different pieces
int Solution::integerBreak(int n) {
    
    vector<int> a(n + 1);
    a.push_back(0);
    a.push_back(1);
    a.push_back(1);
    a.push_back(2);
    
    for(int i = 4; i <= n; ++i) {
        int b = 2 * ((a[i - 2] > i-2) ? a[i-2] : i-2);
        int c = 3 * ((a[i - 3] > i-3) ? a[i-3] : i-3);
        if(b > c) a[i] = b;
        else a[i] = c;
        
    }
    
    return a[n];
}

void surroundingRegionsHelper(int i, int j, vector<vector<char>>& board) {
    board[i][j] = 't'; //temp char
    if(i > 0 && board[i-1][j] == 'O')
        surroundingRegionsHelper(i-1, j, board);
    if((j < board[0].size() - 1) && board[i][j + 1] == 'O')
        surroundingRegionsHelper(i, j + 1, board);
    if((j > 0) && board[i][j - 1] == '0')
        surroundingRegionsHelper(i, j - 1, board);
    if((i < board.size() - 1) && board[i+1][j] == 'O')
        surroundingRegionsHelper(i+1, j, board);

}

void Solution::surroundingRegions(vector<vector<char>>& board) {
    if(board.empty()) return;
    
    //traverse boundry
    vector<char>& topRow = board[0];
    for(int i = 0; i < topRow.size(); ++i) {
        if(topRow[i] == 'O') {
            surroundingRegionsHelper(0, i, board);
        }
    }
    
    vector<char>& bottomRow = board[board.size() - 1];
    for(int i = 0; i < bottomRow.size(); ++i) {
        if(bottomRow[i] == 'O') {
            surroundingRegionsHelper(board.size() - 1, i, board);
        }
    }
    
    for(int i = 1; i < board.size() - 1; ++i) {
        if(board[i][0] == 'O') {
            surroundingRegionsHelper(i, 0, board);
        }
    }
    
    for(int i = 1; i < board.size() - 1; ++i) {
        if(board[i][board[0].size() - 1] == 'O') {
            surroundingRegionsHelper(i, board[0].size() - 1, board);
        }
    }
    
    for(int i = 0; i < board.size(); ++i)  {
        for (int j = 0; j < board[i].size(); ++j) {
            if(board[i][j] == 'O') {
               board[i][j] = 'X';
            } else if (board[i][j] == 't') {
                board[i][j] = 'O';
            }
        }
    }
}

namespace Solution {
    namespace test {
        ListNode* createTestList(const vector<int>& vec) {
            ListNode* head = NULL;
            ListNode* lastNode = NULL;
            for(auto& value : vec) {
                ListNode* node = new ListNode(value);
                if(!head){
                    head = node;
                    lastNode = node;
                } else {
                    lastNode->next = node;
                    lastNode = node;
                }
            }
            
            return head;
        }
        
        void testThreeSum() {
            //vector<int> test1 = {-3, -1, 0, 1, 2};
            //vector<int> test1 = {-2, -1, 0, 1, 2};
            //vector<int> test1 = {-3, -1, 0, 1, 2};
            //vector<int> test1 = {-1,0,1,2,-1,-4};
            //vector<int> test1 = {0, 0, 0};
            //vector<int> test1 = {-4,-1,-4,0,2,-2,-4,-3,2,-3,2,3,3,-4};
            vector<int> test1 = {-8,8,5,-2,-8,-9,-10,6,-3,-5,5,-6,-2,-6,5,-5,7,3,-4,0,-5,-2};
            
            const Vector2D<int>& result = threeSum(test1);
            for_each(result.begin(), result.end(), [](const vector<int>& vec) {
                cout << "Triplet: ";
                for_each(vec.begin(), vec.end(), [](const int& n) {
                    cout << n;
                });
                cout << endl;
            });
        }
        
        void testSortedListToBST() {
            ListNode* head;
            
            //vector<int> test = {1,2,3,4};
            vector<int> test = {1, 2};
            head = createTestList(test);
            TreeNode* node = sortedListToBST(head);
            printTree(node, 0, true);
            cout<<endl;
        }
        
        void testIntegerBreak() {
            int n = integerBreak(20);
            cout << n << endl;
        }
        
        void testSurroundingRegions() {
            /*vector<vector<char>> board = {  {'x','x','x','x'},
                                            {'x','0','0','x'},
                                            {'x','x','0','x'},
                                            {'x','0','x','x'}}; */
            vector<vector<char>> board = {{'X', 'X', 'X'} , {'X', 'O', 'X'}, {'X', 'X', 'X'}};
                
            surroundingRegions(board);
            
            for(auto& row : board) {
                for(auto& item : row) {
                    cout<<item<<"  ";
                }
                cout<<endl;
            }
        }
        
    }
}
