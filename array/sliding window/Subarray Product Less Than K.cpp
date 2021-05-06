/**
 * Leetcode 713. 乘积小于K的子数组
 * 给定一个正整数数组 nums。
 * 找出该数组内乘积小于 k 的连续的子数组的个数。
 *
 * 示例 1:
 *  输入: nums = [10,5,2,6], k = 100
 *  输出: 8
 *  解释: 8个乘积小于100的子数组分别为: [10], [5], [2], [6], [10,5], [5,2], [2,6], [5,2,6]。
 *  需要注意的是 [10,5,2] 并不是乘积小于100的子数组。
 *
 * 说明:
 * (1)0 < nums.length <= 50000
 * (2)0 < nums[i] < 1000
 * (3)0 <= k < 10^6
 */
#include <vector>
using namespace std;

/* 滑动窗口 */
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int ans = 0;
        int left = 0, right = 0;
        int curSum = 1;
        int n = nums.size();
        for (; right < n; right++) {
            curSum *= nums[right];
            /* 当前窗口乘积大于k, 左指针不断左移, 直到小于k */
            while (left <= right && curSum >= k) {
                curSum /= nums[left];
                left++;
            }
            /* 循环结束后有两种情况:
             *  (1)一般情况是, left < right
             *  (2)left == right, 表明nums[right] >= k */
            
            /* 此时滑动窗口内的乘积已经小于k了, 新增子数组个数为:
             * [left, right]以内, 以nums[right]结尾的子数组
             * 
             * 例如: [1000,4,3,2,999], k = 50
             *      假设left = 1, right = 3
             *      以right为结尾的子数组有: [4,3,2], [3,2], [2] */
            ans += right - left + 1;
        }
        return ans;
    }
};