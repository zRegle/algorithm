/* 188. 买卖股票的最佳时机 IV
 * 给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。
 * 设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。
 * 注意: 你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
 * 示例 1:
 *  输入: [2,4,1], k = 2
 *  输出: 2
 *  解释: 在第 1 天 (股票价格 = 2) 的时候买入，在第 2 天 (股票价格 = 4) 的时候卖出，这笔交易所能获得利润 = 4-2 = 2 。
 * 示例 2:
 *  输入: [3,2,6,5,0,3], k = 2
 *  输出: 7
 *  解释: 在第 2 天 (股票价格 = 2) 的时候买入，在第 3 天 (股票价格 = 6) 的时候卖出, 这笔交易所能获得利润 = 6-2 = 4 。
 *       随后，在第 5 天 (股票价格 = 0) 的时候买入，在第 6 天 (股票价格 = 3) 的时候卖出, 这笔交易所能获得利润 = 3-0 = 3 。
 */
#include <vector>
using namespace std;

/* 经典动态规划题目
 * dp[i][j][0]表示第i天, 已经购买了j次股票, 并且当天没有持有股票的收益
 * dp[i][j][0]表示第i天, 已经购买了j次股票, 并且当天持有股票的收益
 */
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (k > n >> 1) {
            /* 一次交易由买入和卖出构成, 至少需要两天。
             * 因此有效的限制k应该不超过n/2，如果超过，就没有约束作用了
             * 即相当于随便买卖多少次都行, 用贪心解决即可 */
            int profit = 0;
            for (int i = 1; i < n; i++) {
                if (prices[i] > prices[i-1])
                    profit += prices[i] - prices[i-1];
            }
            return profit;
        }
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(k+1, vector<int>(2, 0)));
        for (int j = 0; j <= k; j++) {
            /* 第1天, 不管购买了多少次股票, 最终只要是没有持有股票收益就为0 */
            dp[0][j][0] = 0;
            /* 第1天, 不管购买了多少次股票, 最终只要是持有股票收益就为-prices[0] */
            dp[0][j][1] = -prices[0];
        }
        for (int i = 1; i < n; i++) {
            for (int j = 1; j <= k; j++) {
                /* 第j天没有持有股票时的收益:
                 * (1)第j天没有任何操作 -> dp[i-1][j][0]
                 * (2)第j天卖出股票-> 前i-1天已经购买了j次股票的收益 + 当天卖出股票的收益
                 */
                dp[i][j][0] = max(dp[i-1][j][0], dp[i-1][j][1] + prices[i]);
                /* 第j天持有股票时的收益:
                 * (1)第j天没有任何操作 -> dp[i-1][j][1]
                 * (2)第j天买入股票-> 前i-1天已经购买了j-1次股票的收益 - 当天买入股票的花费
                 */
                dp[i][j][1] = max(dp[i-1][j][1], dp[i-1][j-1][0] - prices[i]);
            }
        }
        return dp[n-1][k][0];
    }

    /* 优化空间复杂度为O(k) */
    int maxProfitSpaceCompress(int k, vector<int>& prices) {
        int n = prices.size();
        if (k > n >> 1) {
            int profit = 0;
            for (int i = 1; i < n; i++) {
                if (prices[i] > prices[i-1])
                    profit += prices[i] - prices[i-1];
            }
            return profit;
        }
        vector<vector<int>> dp(k+1, vector<int>(2, 0));
        for (int j = 0; j <= k; j++) {
            dp[j][0] = 0;
            dp[j][1] = -prices[0];
        }
        for (int i = 1; i < n; i++) {
            for (int j = 1; j <= k; j++) {
                dp[j][0] = max(dp[j][0], dp[j][1] + prices[i]);
                dp[j][1] = max(dp[j][1], dp[j-1][0] - prices[i]);
            }
        }
        return dp[k][0];
    }
};