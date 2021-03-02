/**
 * Leetcode 416. 分割等和子集
 * 给定一个只包含正整数的非空数组。是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
 * 注意:
 *  每个数组中的元素不会超过 100
 *  数组的大小不会超过 200
 * 示例 1:
 *  输入: [1, 5, 11, 5]
 *  输出: true
 *  解释: 数组可以分割成 [1, 5, 5] 和 [11].
 *
 * 示例 2:
 *  输入: [1, 2, 3, 5]
 *  输出: false
 *  解释: 数组不能分割成两个元素和相等的子集.
 */
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

/**
 * 设nums元素之和为sum, 它的一半为target
 * 问题本质上归结为:
 * 是否可以从nums中挑选若干个元素, 使得元素和为target
 */

/* 暴搜方法查看dfs */

/* 类似于0-1背包问题
 * dp[i][j]: 前i个元素中挑选若干个元素, 能否使得其和为j */
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        /* 数组之和为奇数, 不可能划分两个和相等的子集 */
        if ((sum & 1) == 1) return false;
        int target = sum >> 1;
        int maxNum = *max_element(nums.begin(), nums.end());
        /* 数组最大值大于target, 剩下的元素之和一定小于target, 直接返回false */
        if (maxNum > target) return false;
        int n = nums.size();
        auto dp = vector<vector<bool>>(n, vector<bool>(target + 1, false));
        for (int i = 0; i < n; i++) {
            /* 前i个元素一个不取, 和为0 */
            dp[i][0] = true;
        }
        for (int i = 1; i < n; i++) {
            for (int j = 1; j <= target; j++) {
                if (j >= nums[i])
                    /* 对于元素nums[i], 我们可以选取或者不选取
                     * 选取就是dp[i-1][j-nums[i]]
                     * 不选取就是dp[i-1][j]
                     */
                    dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i]];
                else
                    /* j小于nums[i], 我们不能选取nums[i] */
                    dp[i][j] = dp[i-1][j];
            }
        }
        return dp[n-1][target];
    }

private:
    /* 空间优化做法 */
    bool spaceOptimize(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if ((sum & 1) == 1) return false;
        int target = sum >> 1;
        int maxNum = *max_element(nums.begin(), nums.end());
        if (maxNum > target) return false;
        int n = nums.size();
        auto dp = vector<bool>(target + 1);
        dp[0] = true;
        for (int i = 1; i < n; i++) {
            for (int j = target; j >= nums[i]; j--)
                dp[j] = dp[j] || dp[j-nums[i]];
        }
        return dp[target];
    }
};