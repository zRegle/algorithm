/* Leetcode 53 最大子序和
给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

示例:
输入: [-2,1,-3,4,-1,2,1,-5,4],
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
*/

//dp, dp[i]表示以i结尾的最大子序和
#include <vector>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int size = nums.size();
        vector<int> dp(size);
        dp[0] = nums[0];
        int max_sum = nums[0];
        for (int i = 1; i < size; i++) {
            dp[i] = dp[i-1] >= 0 ? (dp[i-1] + nums[i]) : nums[i];
            max_sum = max(dp[i], max_sum);
        }
        return max_sum;
    }
};