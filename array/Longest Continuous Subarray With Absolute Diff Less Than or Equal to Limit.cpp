/**
 * Leetcode 1438. 绝对差不超过限制的最长连续子数组
 * 给你一个整数数组 nums ，和一个表示限制的整数 limit，请你返回最长连续子数组的长度，
 * 该子数组中的任意两个元素之间的绝对差必须小于或者等于 limit 。
 * 如果不存在满足条件的子数组，则返回 0 。
 * 
 * 示例 1：
 *  输入：nums = [8,2,4,7], limit = 4
 *  输出：2 
 *  解释：所有子数组如下：
 *      [8] 最大绝对差 |8-8| = 0 <= 4.
 *      [8,2] 最大绝对差 |8-2| = 6 > 4. 
 *      [8,2,4] 最大绝对差 |8-2| = 6 > 4.
 *      [8,2,4,7] 最大绝对差 |8-2| = 6 > 4.
 *      [2] 最大绝对差 |2-2| = 0 <= 4.
 *      [2,4] 最大绝对差 |2-4| = 2 <= 4.
 *      [2,4,7] 最大绝对差 |2-7| = 5 > 4.
 *      [4] 最大绝对差 |4-4| = 0 <= 4.
 *      [4,7] 最大绝对差 |4-7| = 3 <= 4.
 *      [7] 最大绝对差 |7-7| = 0 <= 4. 
 *      因此，满足题意的最长子数组的长度为 2 。
 * 示例 2：
 *  输入：nums = [10,1,2,4,7,2], limit = 5
 *  输出：4 
 *  解释：满足题意的最长子数组是 [2,4,7,2]，其最大绝对差 |2-7| = 5 <= 5 。
 * 示例 3：
 *  输入：nums = [4,2,2,2,4,4,2,2], limit = 0
 *  输出：3
 * 
 * 提示：
 *  (1)1 <= nums.length <= 10^5
 *  (2)1 <= nums[i] <= 10^9
 *  (3)0 <= limit <= 10^9
 */
#include <vector>
#include <map>
using namespace std;

/**
 * 滑动窗口, 记录滑动窗口内的最小值和最大值
 * 如果不满足要求, 就尝试移动左指针
 */

class MySolution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int left = 0, right = 1;
        int minVal = nums[0], maxVal = nums[0];
        int ans = 1, len = nums.size();
        /**
         * 当前滑动窗口中:
         * key -> 数组元素, value -> 该元素最后出现的下标
         */
        map<int, int> map;
        map[nums[left]] = left;
        while (right < len && left <= right) {
            maxVal = max(maxVal, nums[right]);
            minVal = min(minVal, nums[right]);
            map[nums[right]] = right;
            if (maxVal - minVal <= limit) {
                ans = max(ans, right - left + 1);
            } else {
                /* 当前元素是最大值, 导致不满足条件
                 * 此时应该移动左指针来改变最小值, 直到满足条件 */
                if (maxVal == nums[right]) {
                    /* 不断改变最小值, 直到最大值 - 最小值 <= limit */
                    int idx = INT_MIN;
                    while (maxVal - minVal > limit) {
                        idx = max(idx, map[minVal]);
                        map.erase(minVal);
                        minVal = map.begin()->first;
                    }
                    /* 循环结束后, 我们知道新的左边界的范围为(idx, map[minVal]]
                     * 因为[0, idx]含有元素x使得 最大值 - x > limit
                     * 故[0, idx]应该全部舍弃掉 */
                    /* 下面来确定新的左边界 */
                    int nextLeft = INT_MAX;
                    auto it = map.begin();
                    while (it != map.end()) {
                        if (it->second <= idx)
                            /* 该元素在[0, idx], 从当前滑动窗口中删除 */
                            map.erase(it++);
                        else {
                            /* 在(idx, map[minVal]]中挑选下标最小的元素作为新的左边界 */
                            nextLeft = min(nextLeft, it->second);
                            it++;
                        }
                    }
                    left = nextLeft;
                } else {
                    /* 过程与上面类似, 此时应该不断改变最大值来满足要求 */
                    int idx = INT_MIN;
                    while (maxVal - minVal > limit) {
                        idx = max(idx, map[maxVal]);
                        map.erase(maxVal);
                        maxVal = map.rbegin()->first;
                    }
                    int nextLeft = INT_MAX;
                    auto it = map.begin();
                    while (it != map.end()) {
                        if (it->second <= idx)
                            map.erase(it++);
                        else {
                            nextLeft = min(nextLeft, it->second);
                            it++;
                        }
                    }
                    left = nextLeft;
                }
            }
            right++;
        }
        return ans;
    }
};

/* 更加优雅的做法 */
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        /* 在当前滑动窗口中:
         * key->数组元素, value->元素出现的次数 */
        map<int, int> map;
        int ans = 0;
        int left = 0, right = 0;
        while (right < nums.size()) {
            map[nums[right]]++;
            while (map.rbegin()->first - map.begin()->first > limit) {
                /* 当前滑动窗口不满足要求时, 移动左指针 */
                map[nums[left]]--;
                if (map[nums[left]] == 0)
                    map.erase(nums[left]);
                left++;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};