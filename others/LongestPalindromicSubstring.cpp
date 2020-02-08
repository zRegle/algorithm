/* Leetcode 5.最长回文子串
 * 给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。
 * 示例 1：
 *  输入: "babad"
 *  输出: "bab"
 *  注意: "aba" 也是一个有效答案。
 * 示例 2：
 *  输入: "cbbd"
 *  输出: "bb"
 */
#include <iostream>
#include <vector>
using namespace std;

//还有个马拉车算法

//中心扩展法, 选定一个或一对字符, 向左右两边拓展
class Solution1 {
public:
    string longestPalindrome(string s) {
        int len = s.length();
        if (!len) return "";
        int start = 0, maxLen = 0;
        for (int i = 0; i < len; i++) {
            auto p1 = expand(i, i, s); //回文串长度是奇数的情况
            int l1 = p1.second - p1.first + 1;
            if (l1 > maxLen) {
                maxLen = l1;
                start = p1.first;
            }
            if (s[i] == s[i+1]) {
                auto p2 = expand(i, i+1, s); //回文串长度是偶数的情况
                int l2 = p2.second - p2.first + 1;
                if (l2 > maxLen) {
                    maxLen = l2;
                    start = p2.first;
                }
            }
        }
        return s.substr(start, maxLen);
    }
private:
    //传进来的时候, left到right必定是回文串
    pair<int, int> expand(int left, int right, string& s) {
        int len = s.length();
        while (left >= 0 && right < len && s[left] == s[right])
            left--, right++;
        //退出循环后, left和right要回退一步
        pair<int, int> coordinate(++left, --right);
        return coordinate;
    }
};

//动态规划
//dp[i][j]表示s的第i个字符到第j个字符是否为回文串
//dp[i][j] = s[i] == s[j] && dp[i+1][j-1] (i + 1 < j)
//         = s[i] == s[j] (i + 1 = j)
//         = true (i = j)
class Solution2 {
public:
    string longestPalindrome(string s) {
        int len = s.length();
        if (!len) return "";
        vector<vector<bool>> dp(len+1, vector<bool>(len+1, false));
        int start = 0, cnt = 1;
        //因为dp[i][j]要用到dp[i+1][j-1]所以i要反向遍历, j要正向遍历
        for (int i = len; i >= 1; i--) {
            for (int j = i; j <= len; j++) {
                if (i == j)
                    dp[i][j] = true;
                else if (j == i + 1)
                    dp[i][j] = s[i-1] == s[j-1];
                else
                    dp[i][j] = s[i-1] == s[j-1] && dp[i+1][j-1];
                if (dp[i][j]) {
                    int curLen = j - i + 1;
                    if (curLen > cnt) {
                        cnt = curLen;
                        start = i - 1;
                    }
                }
            }
        }
        return s.substr(start, cnt);
    }
private:
    //优化空间从O(n²)到O(n)
    string optimize(string s) {
        int len = s.length();
        if (!len) return "";
        vector<bool> dp(len+1, false); //存着第i+1行的结果
        int start = 0, cnt = 1;
        for (int i = len; i >= 1; i--) {
            for (int j = len; j >= i; j--) { //因为要用前一列的结果, 所以j也要反向遍历
                if (j == i)
                    dp[j] = true;
                else if (j == i + 1)
                    dp[j] = s[i-1] == s[j-1];
                else
                    dp[j] = s[i-1] == s[j-1] && dp[j-1];
                if (dp[j]) {
                    int curLen = j - i + 1;
                    if (curLen > cnt) {
                        cnt = curLen;
                        start = i - 1;
                    }
                }
            }
        }
        return s.substr(start, cnt);
    }
};