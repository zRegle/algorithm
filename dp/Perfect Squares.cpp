/* Leetcode 279. Perfect Squares
 * 给定一个数, 求出一系列平方数之和等于这个数的最少个数
 *
 * Input: n = 12
 * Output: 3
 * Explanation: 12 = 4 + 4 + 4.
 *
 * Input: n = 13
 * Output: 2
 * Explanation: 13 = 4 + 9.
 */
#include <vector>
#include <climits>
using namespace std;

/* BFS方法参考BFS文件夹 */

 /* 动态规划, dp[i]表示给定数字i, 平方数的最少个数 */
class Solution {
    int numSquares(int n) {
        vector<int> dp(n+1, INT_MAX);
        dp[0] = 0; dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j * j <= i; ++j) {
                //i-j*j用的平方数 + (dp[j*j] = 1)
                dp[i] = min(dp[i], dp[i-j*j] + 1);
            }
        }
        return dp[n];
    }
};
