/**
 * Leetcode 719. 找出第 k 小的距离对
 * 给定一个整数数组，返回所有数对之间的第 k 个最小距离。一对 (A, B) 的距离被定义为 A 和 B 之间的绝对差值。
 *
 * 示例 1:
 *  输入：
 *  nums = [1,3,1]
 *  k = 1
 *  输出：0
 *  解释：
 *  所有数对如下：
 *  (1,3) -> 2
 *  (1,1) -> 0
 *  (3,1) -> 2
 *  因此第 1 个最小距离的数对是 (1,1)，它们之间的距离为 0。
 *
 * 提示:
 * (1)2 <= len(nums) <= 10000.
 * (2)0 <= nums[i] < 1000000.
 * (3)1 <= k <= len(nums) * (len(nums) - 1) / 2.
 */
#include <vector>
#include <algorithm>
using namespace std;

/**
 * 数组A中, 两两数字之间的距离有一个范围[0, max{A} - min{A}]
 * 我们要找到第k个最小距离, 可以对这个范围内的数字进行二分查找
 * 
 * 每次选中一个mid之后, 我们判断数组中距离小于等于mid的数字对有多少组
 * 如果超过k组, 代表第k个最小距离比mid还要小, 继续二分; 反之亦然
 */

class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int low = 0, high = nums.back() - nums[0];
        /* 二分查找第k个最小距离 */
        while (low < high) {
            int mid = (low + high) / 2;
            int left = 0, right = 0, count = 0;
            /* 统计有多少对数字的距离小于等于mid */
            while (right < nums.size()) {
                while (nums[right] - nums[left] > mid) left++;
                /* 以nums[right]为右端点, 
                 * 距离小于等于mid的数字对的个数为: right - left */
                count += right - left;
                right++;
            }
            if (count >= k)
                /* 小于mid的数字对超过了k对
                 * 说明第k个最小距离的范围是[low, mid]*/
                high = mid;
            else
                /* 小于mid的数字对不足k对
                 * 说明第k个最小距离的范围是(mid, high] */
                low = mid + 1;
        }
        return low;
    }
};