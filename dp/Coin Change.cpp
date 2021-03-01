/**
 * Leetcode 322. 零钱兑换
 * 给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。
 * 如果没有任何一种硬币组合能组成总金额，返回 -1。
 * 你可以认为每种硬币的数量是无限的。
 *
 * 示例 1：
 *  输入：coins = [1, 2, 5], amount = 11
 *  输出：3
 *  解释：11 = 5 + 5 + 1
 */
#include <vector>
using namespace std;

/**
 * 比较简单的动态规划
 * dp[i]: 表示凑齐金额i所需的最小硬币数
 */
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int MAX = amount + 1; /* MAX值不要用0x7fffffff, 否则会溢出 */
        auto dp = vector<int>(amount + 1, MAX);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) {
            for (int c : coins) {
                if (i - c >= 0) {
                    dp[i] = min(dp[i], dp[i - c] + 1);
                }
            }
        }
        return dp[amount] == MAX ? -1 : dp[amount];
    }
};