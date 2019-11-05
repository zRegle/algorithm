/* Leetcode 1143.最长公共子序列
 * 给定两个字符串s1和s2,返回这两个字符串的最长公共子序列.
 * 一个字符串的子序列是指这样一个新的字符串:它是由原字符串在不改变字符的相对顺序的情况下删除某些字符(也可以不删除任何字符)后组成的新字符串.
 * 例如,"ace"是"abcde"的子序列,但"aec"不是"abcde"的子序列.两个字符串的"公共子序列"是这两个字符串所共同拥有的子序列。
 * 若这两个字符串没有公共子序列,则返回0.
 * 示例1:
 *  输入：s1 = "abcde", s2 = "ace"
 *  输出：3
 *  解释：最长公共子序列是 "ace"，它的长度为 3。
 */
#include <iostream>
#include <vector>
using namespace std;

/* dp[i][j]:表示s1的前i个字符跟s2的前j个字符的最长公共子序列的长度
 * 那么dp[i][j]有三种情况:
 * i = j = 0 -> dp[i][j] = 0
 * s1[i] == s2[j] -> dp[i-1][j-1] + 1
 * s1[i] != s2[j] -> max{dp[i-1][j], dp[i][j-1]}
 * 这里只用了两个一维数组
 */
class Solution {
public:
    int longestCommonSubsequence(string& s1, string& s2) {
        int l1 = s1.size(), l2 = s2.size();
        //prev存着dp[i-1][j]的结果
        //cur存当前行的结果
        vector<int> prev(l2+1, 0), cur(l2+1, 0);
        int max_len = -1;
        for (int i = 1; i <= l1; i++) {
            for (int j = 1; j <= l2; j++) {
                cur[j] = s1[i-1] == s2[j-1] ? prev[j-1]+1 : max(cur[j-1], prev[j]);
                max_len = max(max_len, cur[j]);
            }
            //更新
            prev.assign(cur.begin(), cur.end());
        }
        return max_len;
    }
};