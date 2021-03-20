/**
 * Leetcode 410. 分割数组的最大值
 * 给定一个非负整数数组 nums 和一个整数 m ，你需要将这个数组分成 m 个非空的连续子数组。
 * 设计一个算法使得这 m 个子数组各自和的最大值最小。
 * 
 * 示例 1：
 *  输入：nums = [7,2,5,10,8], m = 2
 *  输出：18
 * 解释：
 *  一共有四种方法将 nums 分割为 2 个子数组。 其中最好的方式是将其分为 [7,2,5] 和 [10,8] 。
 *  因为此时这两个子数组各自的和的最大值为18，在所有情况中最小。
 * 示例 2：
 *  输入：nums = [1,2,3,4,5], m = 2
 *  输出：9
 * 示例 3：
 *  输入：nums = [1,4,4], m = 3
 *  输出：4
 * 
 * 提示：
 *  (1)1 <= nums.length <= 1000
 *  (2)0 <= nums[i] <= 106
 *  (3)1 <= m <= min(50, nums.length)
 */
#include <vector>
#include <cstdint>
using namespace std;

/* 最小化最大值, 明显可以用二分查找 */
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        /* 由题意可知, 答案范围的左边界是数组元素的最大值, 右边界是数组元素求和 */
        uint64_t sum = 0; /* 数组元素求和 */
        uint64_t maxVal = 0; /* 数组元素最大值 */
        for (int x : nums) {
            sum += x;
            maxVal = max(maxVal, (uint64_t)x);
        }
        uint64_t left = maxVal, right = sum;
        uint64_t ans = 0;
        while (left <= right) {
            uint64_t mid = left + ((right - left) >> 1);
            if (judge(mid, m, nums)) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }

private:
    /* 判断能否将数组分成m组, 每组的最大值不超过val */
    bool judge(uint64_t val, int m, vector<int>& nums) {
        /* cnt: 目前分了多少组 */
        int cnt = 1, i = 0;
        uint64_t sum = 0;
        while (i < nums.size()) {
            if (sum + nums[i] <= val) {
                sum += nums[i++];
            } else {
                /* 必须要split了
                 * 重置sum, 组数加一 */
                sum = 0;
                cnt++;
            }
        }
        return cnt <= m;
    }
};