/**
 * Leetcode 643. 子数组最大平均数 I
 * 给定 n 个整数，找出平均数最大且长度为 k 的连续子数组，并输出该最大平均数。
 *  
 * 示例：
 *  输入：[1,12,-5,-6,50,3], k = 4
 *  输出：12.75
 *  解释：最大平均数 (12-5-6+50)/4 = 51/4 = 12.75
 *  
 * 提示：
 *  (1)1 <= k <= n <= 30,000。
 *  (2)所给数据范围 [-10,000，10,000]。
 */
#include <vector>
using std::vector;
using std::max;

/* 简简单单滑动窗口求窗口最大值 */
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int curSum = 0;
        for (int i = 0; i < k; i++)
            curSum += nums[i];
        int maxSum = curSum;
        for (int i = k; i < nums.size(); i++) {
            curSum -= nums[i - k];
            curSum += nums[i];
            maxSum = max(maxSum, curSum);
        }
        return 1.0 * maxSum / k;
    }
};