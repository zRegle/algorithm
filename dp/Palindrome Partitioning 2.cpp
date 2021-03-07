#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <unordered_set>
using namespace std;

/**
 * leetcode 132. Palindrome Partitioning II
 * 给定一个字符串, 求最少分割多少下, 能够使得字符串各部分都是回文串
 *
 * 例如:
 * 输入: aab
 * 输出: 1
 * 分割: aa|b
 */


/*
 * 我的思路(brute force):
 * 暴力bfs, 用'*'插入原字符串代表分割
 * 结果: MLE, 21/29 Test Case Passed
 */
class Solution {
public:
    int minCut(string& s) {
        if (s.empty()) return 0;
        unordered_set<string> visit; visit.insert(s);
        queue<pair<string, int>> q; q.push(make_pair(s, 0));
        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            auto str = cur.first;
            auto cnt = cur.second;    //表示插入了多少个*
            if (isValid(str)) return cnt;
            for (int i = 0; i < str.size()-1; i++) {
                string new_s;
                if (str[i+1] != '*' && str[i] != '*') {
                    new_s += str.substr(0, (unsigned int)i+1) + '*' + str.substr((unsigned int)i+1);
                    if (visit.find(new_s) == visit.end()) {
                        visit.insert(new_s);
                        q.push(make_pair(new_s, cnt+1));
                    }
                }
            }
        }
        return 0;
    }
private:
    bool isValid(string& s) {
        string partition;
        for (auto c : s) {
            if (c != '*')
                partition += c;
            else {
                if (!isPalindrome(partition))
                    return false;
                partition.clear();
            }
        }
        return isPalindrome(partition);
    }

    bool isPalindrome(string& s) {
        int size = s.size();
        if (!size) return true;
        int i = 0, j = size-1;
        while (i < j) {
            if (s[i++] != s[j--])
                return false;
        }
        return true;
    }
};

/*
 * 动态规划求解
 * isPail[i][j] -> s[i]到s[j]是否为回文串(闭区间)
 * cut[i] -> s的前i个字符最少需要分割多少下
 */
class Solution2 {
public:
    int minCut(string& s) {
        int len = s.length();
        if (!len) return 0;
        vector<int> dp(len+1);
        for (int i = 0; i <= len; i++)
            dp[i] = i-1;
        //让dp[0] = -1是因为:
        //例如s = "aa", 那么当i=1, j = 2时
        //dp[2] = min(dp[2], dp[1-1] + 1), 如果dp[0]≠-1, 那么dp[2]结果就错了
        vector<vector<bool>> isPalindromic(len+1, vector<bool>(len+1, false));
        for (int j = 1; j <= len; j++) {
            for (int i = j; i >= 1; i--) {
                if (i == j)
                    isPalindromic[i][j] = true;
                else if (j == i + 1)
                    isPalindromic[i][j] = s[i-1] == s[j-1];
                else
                    isPalindromic[i][j] = s[i-1] == s[j-1] && isPalindromic[i+1][j-1];
                if (isPalindromic[i][j])
                    dp[j] = min(dp[j], dp[i-1]+1);
                    /* 例如:
                     * abklmlklmlk
                     *       ^   ^
                     *       i   j
                     * 那么我们可以尝试在前i个字符的基础上, 在i的前面再分割一下就合法了                     
                     * 至于为什么要用min而不是每次都是cut[i]+1, 是因为:
                     * ab|klmlklmlk
                     *        ^   ^ ===> cut[i] = 1
                     *        i   j
                     * a|b|klmlklmlk
                     *     ^       ^ ===> cut[i] = 2, 如果直接赋值成cut[i]+1, 就变成了要分割3次了
                     *     i       j
                     */
            }
        }
        return dp[len];
    }
};

/*
 * Manacher-algorithm-like Method
 */
class Solution3 {
public:
    int minCut(string& s) {
        const int size = s.size();
        if (size <= 1) return 0;
        int cut[size+1]; for (int i = 0; i <= size; i++) cut[i] = i-1;
        for (int i = 1; i < size; i++) {
            //以i为中心, 向两边扩散
            for (int j = 0; i-j >= 0 && i+j < size && s[i-j] == s[i+j]; j++) //奇数长度的回文串
                cut[i+j+1] = min(cut[i+j+1], cut[i-j]+1);
            //偶数长度的回文串:
            //baab
            //  ^(i)
            for (int j = 0; i-j-1 >= 0 && i+j < size && s[i-j-1] == s[i+j]; j++)    
                cut[i+j+1] = min(cut[i+j+1], cut[i-j-1]+1);
        }
        return cut[size];
    }
};