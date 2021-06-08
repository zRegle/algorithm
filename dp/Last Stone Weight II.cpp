/**
 * Leetcode 1049. 最后一块石头的重量 II
 * 有一堆石头，用整数数组 stones 表示。其中 stones[i] 表示第 i 块石头的重量。
 * 每一回合，从中选出任意两块石头，然后将它们一起粉碎。假设石头的重量分别为 x 和 y，且 x <= y。
 * 那么粉碎的可能结果如下：
 *  (1)如果 x == y，那么两块石头都会被完全粉碎；
 *  (2)如果 x != y，那么重量为 x 的石头将会完全粉碎，而重量为 y 的石头新重量为 y-x。
 * 最后，最多只会剩下一块 石头。返回此石头 最小的可能重量 。如果没有石头剩下，就返回 0。
 *
 * 示例 1：
 *  输入：stones = [2,7,4,1,8,1]
 *  输出：1
 *  解释：
 *   组合 2 和 4，得到 2，所以数组转化为 [2,7,1,8,1]，
 *   组合 7 和 8，得到 1，所以数组转化为 [2,1,1,1]，
 *   组合 2 和 1，得到 1，所以数组转化为 [1,1,1]，
 *   组合 1 和 1，得到 0，所以数组转化为 [1]，这就是最优值。
 *
 * 示例 2：
 *  输入：stones = [31,26,33,21,40]
 *  输出：5
 *  解释：
 *   组合 40 和 21，得到19，所以数组转化为 [31,26,33,19]
 *   组合 33 和 31，得到2，所以数组转化为 [26,2,19]
 *   组合 26 和 19，得到7，所以数组转化为 [7,2]
 *   组合 7 和 2，得到5，所以数组转为为[5]，这就是最优值
 */
#include <vector>
#include <numeric>
using namespace std;

/**
 * 与leetcode 494类似, 可以转化为01背包问题
 *
 * 粉碎石头的过程就类似于在各个数字上加上 +/- 符号, 
 * 分成两个集合Positive和Negative, 最后求表达式的和就是结果
 * 我们的目标是:
 *  (1)求和结果大于等于0
 *  (2)求和结果尽可能得小
 *
 * 设石头总重量为sum, 那么我们要找到一个Negative集合, 使得:
 *  (1)元素之和小于sum/2 ---> Positive - Negative 结果大于等于0
 *  (2)元素之和最大 ---> Positive - Negative 结果尽可能小
 *  
 * 那么就变成典型的01背包: 背包容量为sum/2, 求容纳物品的最大价值
 */

class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int n = stones.size();
        int sum = accumulate(stones.begin(), stones.end(), 0);
        int target = sum >> 1;
        vector<vector<int>> dp(n+1, vector<int>(target+1));
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= target; j++) {
                /* 不捡物品i */
                dp[i][j] = dp[i-1][j];
                if (j >= stones[i-1])
                    /* 背包容量够大, 判断捡不捡物品i */
                    dp[i][j] = max(dp[i][j], dp[i-1][j-stones[i-1]] + stones[i-1]);
            }
        }
        /* 选取的石头就是Negative集合
         * 结果 = sum{stones} - sum{Negative} * 2 */
        return sum - (dp[n][target] << 1);
    }

private:
    /* 空间优化后的dp */
    int optimize(vector<int>& stones) {
        int n = stones.size();
        int sum = accumulate(stones.begin(), stones.end(), 0);
        int target = sum >> 1;
        vector<int> dp(vector<int>(target+1));
        for (int x : stones) {
            for (int j = target; j >= x; j--) {
                dp[j] = max(dp[j], dp[j-x] + x);
            }
        }
        return sum - (dp[target] << 1);
    }
};