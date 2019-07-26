/* Leetcode 44.通配符匹配
 * 给定一个字符串 (s) 和一个字符模式 (p) ，实现一个支持 '?' 和 '*' 的通配符匹配。
 * '?' 可以匹配任何单个字符。
 * '*' 可以匹配任意字符串（包括空字符串）。
 * 两个字符串完全匹配才算匹配成功。
 */

#include <iostream>
using namespace std;

class DP {
public:
    bool isMatch(string s, string p) {
        int s_len = s.length(), p_len = p.length();
        //dp[i][j]表示s的前i个字符是否与p的前j个字符匹配
        auto dp = new bool*[s_len+1];
        for (int i = 0; i <= s_len; i++) {
            dp[i] = new bool[p_len+1]();
        }
        for (int j = 1; j <= p_len; j++) {
            dp[0][j] = p[j-1] == '*' && dp[0][j-1];
        }
        dp[0][0] = true;
        for (int i = 1; i <= s_len; i++) {
            for (int j = 1; j <= p_len; j++) {
                if (s[i-1] == p[j-1] || p[j-1] == '?')
                    dp[i][j] = dp[i-1][j-1];
                else if (p[j-1] == '*')
                    //dp[i-1][j]表示'*'空匹配
                    //dp[i][j-1]表示'*'匹配了一个字符
                    dp[i][j] = dp[i-1][j] || dp[i][j-1];
            }
        }
        bool res = dp[s_len][p_len];
        for (int i = 0; i <= s_len; i++) {
            delete[](dp[i]); dp[i] = nullptr;
        }
        delete[](dp); dp = nullptr;
        return res;
    }
};