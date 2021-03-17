/**
 * 剑指offer - 字符的所有组合
 * 输入n个字符, 求这n个字符的所有组合方案数
 * 
 * 示例:
 *  输入: a, b, c
 *  输出: 7
 *  解释: a, b, c, ab, ac, bc, abc
 *  注意: 字符相同但顺序不同, 例如"ab"和"ba", 也视作同一个组合,
 */
#include <string>
#include <vector>
using namespace std;

/* dfs方法查看dfs文件夹 */

/* dp[i][j]: 从前i个字符中选取j个字符的方案数 */
class Solution {
public:
    int combination(vector<char>& chs) {
        int n = chs.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for (int i = 0; i <= n; i++) {
            /* 从前i个字符中选取0个字符的方案只有一种 */
            dp[i][0] = 1;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                /* dp[i-1][j]: 不选取当前字符
                 * dp[i-1][j-1]: 选取当前字符 */
                dp[i][j] = dp[i-1][j] + dp[i-1][j-1];
            }
        }
        int sum = 0;
        /* 求和: 从n个字符中选取i个字符 */
        for (int i = 1; i <= n; i++) {
            sum += dp[n][i];
        }
        return sum;
    }
};
