/**
 * Leetcode 300. 最长递增子序列
 * 给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
 * 子序列是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。
 * 例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。
 *
 * 示例 1：
 *  输入：nums = [10,9,2,5,3,7,101,18]
 *  输出：4
 *  解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。
 * 示例 2：
 *  输入：nums = [0,1,0,3,2,3]
 *  输出：4
 *
 * 提示：
 *  (1)1 <= nums.length <= 2500
 *  (2)-10^4 <= nums[i] <= 10^4
 *
 * 进阶：
 *  你可以设计时间复杂度为 O(n²) 的解决方案吗？
 *  你能将算法的时间复杂度降低到O(n log(n)) 吗?
 */
#include <vector>
using namespace std;

/* O(nlogn的方法查看二分查找文件夹) */

/**
 * dp[i]: 以i结尾的最长递增子序列
 * 遍历[0,i)的任意dp[j], 如果nums[j] < nums[i]
 * 则dp[i] = dp[j] + 1, 取所有j中的最大值dp[j]
 * 时间复杂度: O(n²)
 */
class Solution0 {
public:
    int lengthOfLIS(vector<int>& nums) {
        int len = nums.size();
        vector<int> dp(len, 1);
        int ans = 0;
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i])
                    dp[i] = max(dp[j] + 1, dp[i]);
            }
            ans = max(dp[i], ans);
        }
        return ans;
    }
};