/*
 * leetcode 115. Distinct Subsequences
 * 给定两个字符串s, t, 求按顺序从s中挑选字符, 能够构成t的方案一共有几种
 * Input: S = "rabbbit", T = "rabbit"
 * Output: 3
 * Explanation:
 *
 * As shown below, there are 3 ways you can generate "rabbit" from S.
 * (The caret symbol ^ means the chosen letters)
 * rabbbit
   ^^^^ ^^
 * rabbbit
   ^^ ^^^^
 * rabbbit
   ^^^ ^^^
 * 思路
 * dp[i][j]表示s前i个字符能够构成t前j个字符的方案种数
 */
#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    int numDistinct(string& s, string& t) {
        int len1 = s.length(), len2 = t.length();
        if (len1 <= len2) return s == t;
        vector<vector<long>> dp(len1+1, vector<long>(len2+1, 0));
        for (int i = 1; i <= len1; ++i) {
            for (int j = 1; j <= len2; ++j) {
                if (s[i-1] != t[j-1]) {
                    //如果s的第i个字符不等于t的第j个字符
                    //那么s的第i个字符就不用于构建t的前j个字符, 就相当于dp[i-1][j]
                    dp[i][j] = dp[i-1][j];
                } else {
                    //如果相等, 那么有两种情况
                    //第一种, s的前i-1个字符构成t的前j-1个字符, 然后s的第i个字符构成t的第j个字符
                    //第二种, s的前i-1个字符构成t的前j个字符, 然后s的第i个字符就不用来构建
                    dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
                }
            }
        }
        return dp[len1][len2];
    }
};

//优化空间复杂度的方法
//在递推关系中, dp[i][j]只依赖于dp[i-1][j-1]和dp[i-1][j]
//那么我们可以只用一维数组来存储上一行的结果
class Solution2 {
public:
    int numDistinct(string& s, string& t) {
        int l1 = s.size(), l2 = t.size();
        if (l1 <= l2) return s == t;
        vector<long> dp(l2+1, 0);
        dp[0] = 1;
        for (int i = 1; i <= l1; i++) {
            //从后往前遍历, 因为如果从前往后遍历时, dp[j-1]在更新dp[j]已经被更新为dp[i][j-1]了
            //到dp[j]要用到dp[i-1][j-1]时, 就无法用到上一行的结果了
            //跟01背包问题里优化的思路一样
            for (int j = l2; j >= 1; j--) {
                if (s[i-1] == t[j-1]) {
                    dp[j] = dp[j-1] + dp[j];
                }
            }
        }
        return dp[l2];
    }
};

int main() {
   string str = "babgbag";
   string tar = "bag";
   Solution s;
   cout<<s.numDistinct(str, tar)<<endl;
   return 0;
}