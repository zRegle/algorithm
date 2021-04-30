/**
 * Leetcode 689. 三个无重叠子数组的最大和
 * 给定数组 nums 由正整数组成，找到三个互不重叠的子数组的最大和。
 * 每个子数组的长度为k，我们要使这3*k个项的和最大化。
 * 返回每个区间起始索引的列表（索引从 0 开始）。如果有多个结果，返回字典序最小的一个。
 *
 * 示例:
 *  输入: [1,2,1,2,6,7,5,1], 2
 *  输出: [0, 3, 5]
 *  解释: 子数组 [1, 2], [2, 6], [7, 5] 对应的起始索引为 [0, 3, 5]。
 *  我们也可以取 [2, 1], 但是结果 [1, 3, 5] 在字典序上更大。
 *
 * 注意:
 * (1)nums.length的范围在[1, 20000]之间。
 * (2)nums[i]的范围在[1, 65535]之间。
 * (3)k的范围在[1, floor(nums.length / 3)]之间。
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        /* window[i]: 从下标i开始k个数字之和
         * 即window[i] = nums[i] + nums[i+1] + ... + nums[i+k-1]
         * 例如nums = [1,2,1,2,6,7,5,1], k = 2
         * window = {3,3,3,8,13,12,6} */
        vector<int> window(n-k+1, 0);
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += nums[i];
            if (i >= k)
                /* 滑动窗口右移, 最左元素弹出 */
                sum -= nums[i-k];
            if (i >= k-1)
                /* 填充windows数组 */
                window[i-k+1] = sum;
        }
        /* left[i]: 从左往右扫描, [0, i]区间内windows[x]最大值的下标
         * 例如: window = {3,3,3,8,13,12,6}, left = {0,0,0,3,4,4,4} */
        vector<int> left(n-k+1, 0);
        int best = 0;
        for (int i = 0; i < n-k+1; i++) {
            /* >是为了确保字典序最小 */
            if (window[i] > window[best])
                best = i;
            left[i] = best;
        }
        /* right[i]: 从右往左扫描, [i, n-k]区间内windows[x]最大值的下标
         * 例如: window = {3,3,3,8,13,12,6}, left = {4,4,4,4,4,5,6} */
        vector<int> right(n-k+1, 0);
        best = n-k;
        for (int i = n-k; i >= 0; i--) {
            /* >=是为了确保字典序最小 */
            if (window[i] >= window[best])
                best = i;
            right[i] = best;
        }
        vector<int> ans(3, -1);
        int maxSum = 0;
        /* 结果为left, mid, right三个数组
         * 枚举所有mid数组可能的开始下标 */
        for (int m = k; m <= n-2*k; m++) {
            int l = left[m-k], r = right[m+k];
            int val = window[l] + window[m] + window[r];
            if (val > maxSum) {
                maxSum = val;
                ans[0] = l, ans[1] = m, ans[2] = r;
            }
        }
        return ans;
    }
};