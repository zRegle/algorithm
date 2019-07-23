/* Leetcode 32 Longest Valid Parentheses
 * 给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号的子串的长度。
 * 示例 1:
 * 输入: "(()
 * 输出:
 * 解释: 最长有效括号子串为 "()
 *
 * 示例 2
 * 输入: ")()())
 * 输出:
 * 解释: 最长有效括号子串为 "()()"
 */

#include <iostream>
#include <vector>
using namespace std;

//动态规划, dp[i]表示以i结尾的字符串Sub的最长有效括号子串的长度
class Solution {
public:
    int longestValidParentheses(string s) {
        int length = s.length();
        if (length < 2) return 0;
        vector<int> dp(length, 0);
        int res = 0;
        for (int i = 1; i < length; i++) {
            //以'('结尾的肯定不是合法的字符串, 所以只处理')'结尾的
            if (s[i] == ')') {
                if (s[i-1] == '(')
                    //s[i-1] = '(', s[i-1]和s[i]组成一个合法的括号
                    //长度为s[i-1]之前的合法字符串长度+2
                    dp[i] = i >= 2 ? dp[i-2] + 2 : 2;
                else if (i-dp[i-1]-1 >= 0 && s[i-dp[i-1]-1] == '(')
                    //s[i-1] = ')', s[i-1]之前的某个位置可能有对应的'('与s[i]组成有效的括号
                    //我们要跳过中间的字符串去看, 所以看i-dp[i-1]-1是不是'('
                    //如果是, 那么dp[i] = i-dp[i-1]-1之前的有效长度 + i-dp[i-1]-1到i-1的有效长度, 即dp[i-1] + 2
                    dp[i] = (i-dp[i-1]-2 >= 0 ? dp[i-dp[i-1]-2] : 0) + dp[i-1] + 2;
            }
            res = max(res, dp[i]);
        }
        return res;
    }
};