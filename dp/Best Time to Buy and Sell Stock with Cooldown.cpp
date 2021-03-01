/**
 * Leetcode 309. 最佳买卖股票时机含冷冻期
 * 给定一个整数数组，其中第 i 个元素代表了第 i 天的股票价格 。
 * 设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:
 * 你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
 * 卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。
 * 示例:
 *  输入: [1,2,3,0,2]
 *  输出: 3 
 *  解释: 对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出]
 */
#include <vector>
using namespace std;

/**
 * 动态规划:
 *  dp[i][0]: 表示第i天持有股票的累计收益
 *  dp[i][1]: 表示第i天不持有股票并且今天刚卖出股票的累计收益
 *  dp[i][2]: 表示第i天不持有股票并且今天没卖股票的累计收益
 */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int days = prices.size();
        if (days == 0) return 0;
        auto dp = vector<vector<int>>(days, vector<int>(3));
        dp[0][0] = -prices[0];
        for (int i = 1; i < days; i++) {
            /**
             * 第i天持有股票:
             *  (1)今天没有任何操作, 故从dp[i-1][0]转移过来
             *  (2)今天买入了股票, 那么第i-1天不能卖出股票, 故从dp[i-1][2]转移过来
             */
            dp[i][0] = max(dp[i-1][0], dp[i-1][2] - prices[i]);
            /**
             * 第i天不持有股票并且今天刚卖出股票
             * 那么第i-1天就必须持有股票, 故从dp[i-1][0]转移过来
             */
            dp[i][1] = dp[i-1][0] + prices[i];
            /**
             * 第i天不持有股票并且今天没卖股票, 即什么都没有操作
             * 故第i-1天必须为没持有股票, 但是第i-1天卖不卖股票都可以
             * 从dp[i-1][1], dp[i-1][2]转移
             */
            dp[i][2] = max(dp[i-1][1], dp[i-1][2]);
        }
        /* 取最后一天不持有股票的最大值 */
        return max(dp[days-1][1], dp[days-1][2]);
    }
};