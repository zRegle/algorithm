/* Leetcode 97.交错字符串
 * 给定三个字符串 s1, s2, s3, 验证 s3 是否是由 s1 和 s2 交错组成的。
 * 示例 1:
 *  输入: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
 *  输出: true
 * 示例 2:
 *  输入: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
 *  输出: false
 */
#include <string>
#include <vector>
using namespace std;

//dp[i][j]: s1前i个字符和s2前j个字符能否组成s3前i+j个字符
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int len1 = s1.size(), len2 = s2.size(), len3 = s3.size();
        if (len1 + len2 != len3) return false;
        vector<vector<bool>> dp(len1+1, vector<bool>(len2+1, false));
        dp[0][0] = true;
        int i, j;
        for (i = 1; i <= len1; i++)
            //只从s1中抽取字符串到s3中
            dp[i][0] = s1[i-1] == s3[i-1] && dp[i-1][0];
        for (j = 1; j <= len2; j++)
            //只从s2中抽取字符串到s3中
            dp[0][j] = s2[j-1] == s3[j-1] && dp[0][j-1];
        for (i = 1; i <= len1; i++) {
            for (j = 1; j <= len2; j++) {
                //s1[i-1] == s3[i+j-1] -> 取决于s1的前i-1个字符和s2的前j个字符能否组成s3的前i+j-2个字符
                //s2[j-1] == s3[i+j-1] -> 取决于s1的前i个字符和s2的前j-1个字符能否组成s3的前i+j-2个字符
                dp[i][j] = (s1[i-1] == s3[i+j-1] && dp[i-1][j]) ||
                        (s2[j-1] == s3[i+j-1] && dp[i][j-1]);
            }
        }
        return dp[len1][len2];
    }
};