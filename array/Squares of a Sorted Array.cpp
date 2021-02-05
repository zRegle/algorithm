/**
 * Leetcode 977. 有序数组的平方
 * 给你一个按 非递减顺序 排序的整数数组 nums，返回 每个数字的平方 组成的新数组，要求也按 非递减顺序 排序。
 * 
 * 示例 1：
 *  输入：nums = [-4,-1,0,3,10]
 *  输出：[0,1,9,16,100]
 *  解释：平方后，数组变为 [16,1,0,9,100]
 *       排序后，数组变为 [0,1,9,16,100]
 * 示例 2：
 *  输入：nums = [-7,-3,2,3,11]
 *  输出：[4,9,9,49,121]
 * 
 * 提示：
 *  (1)1 <= nums.length <= 104
 *  (2)-104 <= nums[i] <= 104
 *  (3)nums 已按 非递减顺序 排序
 * 
 * 进阶：请你设计时间复杂度为 O(n) 的算法解决本问题
 */
#include <vector>
#include <cmath>
using std::vector;

/* 双指针, 一头一尾, 
 * 比较它们绝对值的大小, 将较大的逆序放置到结果数组中
 */
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int len = nums.size();
        auto ans = vector<int>(len, 0);
        int l = 0, r = len-1;
        int cur = len-1;
        while (l <= r) {
            if (abs(nums[l]) > abs(nums[r])) {
                ans[cur] = nums[l] * nums[l];
                l++;
            } else {
                ans[cur] = nums[r] * nums[r];
                r--;
            }
            cur--;
        }
        return ans;
    }
};