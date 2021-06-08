/**
 * Leetcode 724. 寻找数组的中心下标
 * 给你一个整数数组 nums，请编写一个能够返回数组 “中心下标” 的方法。
 * 数组 中心下标 是数组的一个下标，其左侧所有元素相加的和等于右侧所有元素相加的和。
 * 如果数组不存在中心下标，返回 -1 。如果数组有多个中心下标，应该返回最靠近左边的那一个。
 * 注意：中心下标可能出现在数组的两端。
 *  
 * 示例 1：
 *  输入：nums = [1, 7, 3, 6, 5, 6]
 *  输出：3
 *  解释：
 *   中心下标是 3 。
 *   左侧数之和 (1 + 7 + 3 = 11)，
 *   右侧数之和 (5 + 6 = 11) ，二者相等。
 */
#include <vector>
#include <numeric>
using namespace std;

/* 简单题, 一看就懂 */
class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return -1;
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int cur = 0;
        for (int i = 0; i < n; i++) {
            /* 注意这里不能用
             * cur == (sum - nums[i]) / 2
             * 因为除以二小数点后的会被抹掉, 导致错误
             * 例如: [1,1,1,1,1,1], 就会错误返回index 2 */
            if (cur == sum - nums[i] - cur)
                return i;
            cur += nums[i];
        }
        return -1;
    }
};