/**
 * 剑指 Offer. n个骰子的点数
 * 把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。
 * 输入n，打印出s的所有可能的值出现的概率。
 *
 * 你需要用一个浮点数数组返回答案，
 * 其中第 i 个元素代表这 n 个骰子所能掷出的点数集合中第 i 小的那个的概率。
 *
 * 示例 1:
 *  输入: 1
 *  输出: [0.16667,0.16667,0.16667,0.16667,0.16667,0.16667]
 *
 * 示例 2:
 *  输入: 2
 *  输出: [0.02778,0.05556,0.08333,0.11111,0.13889,0.16667,0.13889,0.11111,0.08333,0.05556,0.02778]
 *
 * 限制：1 <= n <= 11
 */
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<double> dicesProbability(int n) {
        vector<double> prev(6, 1.0 / 6.0);
        for (int i = 2; i <= n; i++) {
            /* i个骰子的和范围是[i, 6i]
             * 一共6i - i + 1 = 5i + 1情况 */
            vector<double> cur(5 * i + 1, 0);
            for (int j = 0; j < prev.size(); j++) {
                /* 第i个骰子的点数 */
                for (int k = 0; k < 6; k++) {
                    cur[j + k] += prev[j] / 6.0;
                }
            }
            prev = cur;
        }
        return prev;
    }
};

/* dp[i][j]: i个骰子的和为j的方案数 */
class Solution0 {
public:
    vector<double> dicesProbability(int n) {
        int maxSum = n * 6;
        vector<vector<int>> dp(n+1, vector<int>(maxSum+1, 0));
        for (int i = 1; i <= 6; i++)
            /* 1个骰子情况 */
            dp[1][i] = 1;
        for (int i = 2; i <= n; i++) {
            /* i个骰子的和, 最小是为i, 最大值为i * 6 */
            for (int j = i; j <= 6 * i; j++) {
                /* 第i个骰子的6个点数 */
                for (int k = 1; k <= 6; k++) {
                    if (j - k >= 0) {
                        dp[i][j] += dp[i-1][j-k];
                    }
                }
            }
        }
        vector<double> ans;
        int all = accumulate(dp[n].begin(), dp[n].end(), 0);
        for (int i = n; i <= 6 * n; i++) {
            if (dp[n][i] != 0)
                ans.push_back((double)dp[n][i] / all);
        }
        return ans;
    }
};