/**
 * Leetcode 494. 目标和
 * 给定一个非负整数数组，a1, a2, ..., an, 和一个目标数，S。
 * 现在你有两个符号 + 和 -。对于数组中的任意一个整数，你都可以从 + 或 -中选择一个符号添加在前面。
 * 返回可以使最终数组和为目标数 S 的所有添加符号的方法数。
 *
 * 示例：
 *  输入：nums: [1, 1, 1, 1, 1], S: 3
 *  输出：5
 *  解释：
 *   -1+1+1+1+1 = 3
 *   +1-1+1+1+1 = 3
 *   +1+1-1+1+1 = 3
 *   +1+1+1-1+1 = 3
 *   +1+1+1+1-1 = 3
 *   一共有5种方法让最终目标和为3。
 *
 * 提示：
 *  (1)数组非空，且长度不会超过 20 。
 *  (2)初始的数组的和不会超过 1000 。
 *  (3)保证返回的最终结果能被 32 位整数存下。
 */
#include <vector>
#include <cmath>
#include <unordered_map>
#include <numeric>
using namespace std;

/* dfs方法参考dfs文件夹 */

/**
 * 优雅的dp, 转化成01背包问题
 * 找到nums一个正子集和一个负子集，使得总和等于target，统计这种可能性的总数。
 * 我们假设P是正子集，N是负子集。让我们看看如何将其转换为子集求和问题：
 *           sum(P) - sum(N) = target（两边同时加上sum(P)+sum(N)）
 * sum(P) + sum(N) + sum(P) - sum(N) = target + sum(P) + sum(N)
 *          2 * sum(P) = target + sum(nums) (因为 sum(P) + sum(N) = sum(nums))
 * 因此，原来的问题已转化为一个求子集的和问题： 找到nums的一个子集 P，使得
 * sum(P) = (target + sum(nums)) / 2
 *
 * 根据公式，若target + sum(nums)不是偶数，就不存在答案，即返回0个可能解。
 *
 * 这样就变成了从nums中挑选数字, 使得它们的和最终为sum(P)
 *
 * dp[i][j] = 从前i个数中挑选数字, 能凑出和为j的方法数
 */
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        /* S超过了数组之和 或者 sum + S不是偶数 */
        if (abs(S) > sum || (sum + S) % 2 == 1) return 0;
        int target = (sum + S) / 2;
        int len = nums.size();
        vector<vector<int>> dp(len + 1, vector<int>(target + 1, 0));
        dp[0][0] = 1; /* 不选取任何数凑成0只有一种方法 */
        for (int i = 1; i <= len; i++) {
            for (int j = 0; j <= target; j++) {
                dp[i][j] = dp[i-1][j]; /* 不选取nums[i-1] */
                if (j-nums[i-1] >= 0)
                    /* 选取nums[i-1] */
                    dp[i][j] += dp[i-1][j-nums[i-1]];
            }
        }
        return dp[len][target];
    }
    /* 空间优化后的dp */
    int optimize(vector<int>& nums, int S) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (abs(S) > sum || (sum + S) % 2 == 1) return 0;
        int target = (sum + S) / 2;
        vector<int> dp(target + 1, 0);
        dp[0] = 1;
        for (int x : nums) {
            for (int j = target; j >= x; j--) {
                dp[j] += dp[j - x];
            }
        }
        return dp[target];
    }
};

/* 相对比较粗暴的dp, dp[i][j] = 前i个数能凑出和为j的方法数, 本质上与dfs相似 */
class Solution1 {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int len = nums.size();
        int sum = accumulate(nums.begin(), nums.end(), 0);
        /* 因为凑出来的和可能是负数, 因此需要用unordered_map */
        vector<unordered_map<int, int>> dp(len + 1, unordered_map<int, int>());
        for (int i = 0; i <= len; i++) {
            for (int j = -sum; j <= sum; j++) {
                dp[i][j] = 0;
            }
        }
        dp[0][0] = 1; /* 0个数, 凑出和为0, 方法只有一种 */
        for (int i = 1; i <= len; i++) {
            for (int j = -sum; j <= sum; j++) {
                if (j - nums[i-1] >= -sum)
                    /* 前面的和加上nums[i-1] */
                    dp[i][j] += dp[i-1][j-nums[i-1]];
                if (j + nums[i-1] <= sum)
                    /* 前面的和减去nums[i-1] */
                    dp[i][j] += dp[i-1][j+nums[i-1]];
            }
        }
        return dp[len][S];
    }
};