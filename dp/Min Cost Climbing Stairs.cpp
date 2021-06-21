/**
 * Leetcode 746. 使用最小花费爬楼梯
 * 数组的每个下标作为一个阶梯，第 i 个阶梯对应着一个非负数的体力花费值 cost[i]（下标从 0 开始）。
 * 每当你爬上一个阶梯你都要花费对应的体力值，一旦支付了相应的体力值，你就可以选择向上爬一个阶梯或者爬两个阶梯。
 * 请你找出达到楼层顶部的最低花费。在开始时，你可以选择从下标为 0 或 1 的元素作为初始阶梯。
 *  
 * 示例 1：
 *  输入：cost = [10, 15, 20]
 *  输出：15
 *  解释：最低花费是从 cost[1] 开始，然后走两步即可到阶梯顶，一共花费 15 。
 * 示例 2：
 *  输入：cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
 *  输出：6
 *  解释：最低花费方式是从 cost[0] 开始，逐个经过那些 1 ，跳过 cost[3] ，一共花费 6 。
 */
#include <vector>
#include <climits>
using std::vector;
using std::min;

/* dp[i]: 爬到阶梯i的最小花费
 * dp[i] = min(dp[i-1], dp[i-2]) + cost[i] */
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n, INT_MAX);
        dp[0] = cost[0]; dp[1] = cost[1];
        for (int i = 2; i < n; i++) {
            dp[i] = min(dp[i-1], dp[i-2]) + cost[i];
        }
        return min(dp[n-2], dp[n-1]);
    }

private:
    int optimize(vector<int>& cost) {
        int n = cost.size();
        int pprev = cost[0], prev = cost[1], tmp;
        for (int i = 2; i < n; i++) {
            tmp = prev;
            prev = min(prev, pprev) + cost[i];
            pprev = tmp;
        }
        return min(prev, pprev);
    }
};