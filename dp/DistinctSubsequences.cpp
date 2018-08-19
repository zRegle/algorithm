#include <iostream>
#include <string>
using namespace std;

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


class Solution {
public:
    int numDistinct(string& s, string& t) {
        int len1 = s.length(), len2 = t.length();
        if (len1 <= len2) return s == t;
        int** dp = new int*[len1+1];
        for (int i = 0; i <= len1; ++i) {
            dp[i] = new int[len2+1]();
            dp[i][0] = 1;   //s前i个字符能够构成空串的方案只有一种
        }
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
        int cnt = dp[len1][len2];
        for (int i = 0; i <= len1; ++i) delete[](dp[i]);
        delete[](dp);
        return cnt;
    }
};

int main() {
   string str = "babgbag";
   string tar = "bag";
   auto s = new Solution();
   cout<<s->numDistinct(str, tar)<<endl;
   return 0;
}