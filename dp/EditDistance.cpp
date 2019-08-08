/* Leetcode 72 编辑距离
 * 给定两个单词 word1 和 word2，计算出将 word1 转换成 word2 所使用的最少操作数 。
 * 你可以对一个单词进行如下三种操作
 * 1.插入一个字
 * 2.删除一个字
 * 3.替换一个字
 * 示例 1
 * 输入: word1 = "horse", word2 = "ros
 * 输出: 3
 * 解释:
 * horse -> rorse (将 'h' 替换为 'r'
 * rorse -> rose (删除 'r'
 * rose -> ros (删除 'e')
 */

#include <vector>
#include <climits>
using namespace std;

//dp, dp[i][j]表示word1的前i个字符变到word2前j个字符的最小步数
class Solution {
public:
    int minDistance(string& word1, string& word2) {
        int len1 = word1.size(), len2 = word2.size();
        vector<vector<int>> dp(len1+1, vector<int>(len2+1, INT_MAX));
        for (int i = 0; i <= len1; i++) dp[i][0] = i;
        for (int i = 0; i <= len2; i++) dp[0][i] = i;
        for (int i = 1; i <= len1; i++) {
            for (int j = 1; j <= len2; j++) {
                if (word1[i-1] == word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    //word1:abcde, word2: ghijk
                    //1.abcde 变到 ghij
                    //2.插入'k'
                    int insert = dp[i][j-1];
                    //1.abcde 变到 ghijke
                    //2.删除'e'
                    int _delete = dp[i-1][j];
                    //1.等同于abcd 变到 ghij
                    //2.用'k'替换word1接下来的那个字符
                    int replace = dp[i-1][j-1];
                    dp[i][j] = min(insert, min(_delete, replace));
                }
            }
        }
        return dp[len1][len2];
    }
};