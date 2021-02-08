/**
 * Leetcode 628. 三个数的最大乘积
 * 给你一个整型数组 nums ，在数组中找出由三个数组成的最大乘积，并输出这个乘积。
 * 
 * 示例 1：
 *  输入：nums = [1,4,2,3]
 *  输出：24
 * 示例 2：
 *  输入：nums = [-1,-4,-2,-3]
 *  输出：-6
 * 示例 3：
 *  输入：nums = [-100,-1,4,2,3]
 *  输出：400
 * 示例 4：
 *  输入：nums = [-100,1,4,2,3]
 *  输出：24
 *  
 * 提示：
 *  3 <= nums.length <= 104
 *  -1000 <= nums[i] <= 1000
 */
#include <vector>
#include <climits>
using namespace std;

/**
 * 数组可以分为三种情况:
 *  1.全是正数
 *  2.全是负数
 *  3.有正数也有负数
 * 前两种情况我们可以直接找最大的三个元素即可
 * 第三种情况有可能最小的两个负数相乘大于最大的两个正数相乘
 * 因此在遍历过程中, 我们可以同时找数组中:
 *  第一、二、三大的数 和 第一、二小的数
 * 最后比较第一、二、三大的数的乘积 和 第一、二小的数与第一大的数的乘积即可
 */

class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        /* 第一、二小的数 */
        int min1 = INT_MAX, min2 = INT_MAX;
        /* 第一、二、三大的数 */
        int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;
        for (int val : nums) {
            if (val <= min1) {
                /* 比当前最小值还小, 更新最小值
                 * 原来的最小值变成次最小值 */
                swap(min1, min2);
                min1 = val;
            } else if (val <= min2)
                min2 = val;
            if (val >= max1) {
                /* 比当前最大值还大, 更新最大值
                 * 原来的最大值变成次大值
                 * 原来的次大值变成第三大值 */
                swap(max2, max3);
                swap(max1, max2);
                max1 = val;
            } else if (val >= max2) {
                swap(max2, max3);
                max2 = val;
            } else if (val >= max3)
                max3 = val;
        }
        return max(max1 * max2 * max3, max1 * min1 * min2);
    }
};