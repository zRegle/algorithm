/**
 * Leetcode 665.非递减数列
 * 给你一个长度为 n 的整数数组，请你判断在 最多 改变 1 个元素的情况下，该数组能否变成一个非递减数列。
 * 我们是这样定义一个非递减数列的： 对于数组中任意的 i (0 <= i <= n-2)，总满足 nums[i] <= nums[i + 1]。
 *
 * 示例 1:
 *  输入: nums = [4,2,3]
 *  输出: true
 *  解释: 你可以通过把第一个4变成1来使得它成为一个非递减数列。
 *
 * 示例 2:
 *  输入: nums = [4,2,1]
 *  输出: false
 *  解释: 你不能在只改变一个元素的情况下将其变为非递减数列。
 *
 * 提示：
 *  (1)1 <= n <= 10^4
 *  (1)-10^5 <= nums[i] <= 10^5
 */
#include <vector>
using std::vector;

/**
 * 不能简单地判断有多少个相邻的nums[i-1] > nums[i]
 * 反例: [3,4,2,3], 只有一个nums[1] > nums[2]
 * 但还是不满足题目条件
 *
 * 必须真正地去模拟改变数组
 */
class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        int len = nums.size();
        if (len < 2) return true;
        int cnt = 0;
        for (int i = 1; i < len; i++) {
            if (nums[i] < nums[i-1]) {
                cnt++;
                if (cnt > 1) return false;
                /* 此时我们可以该nums[i-1]或者nums[i]
                 * 根据贪心, 应尽量使nums[i]保持一个较小的值
                 * 因此先尝试该nums[i-1], 不行再改nums[i] */
                if (i < 2 || nums[i-2] <= nums[i])
                    /* nums[i-1]是第一个元素
                     * nums[i-2] <= nums[i]
                     * 把nums[i-1]改成nums[i]仍满足不递减 */
                    nums[i-1] = nums[i];
                else
                    /* 改变nums[i-1]后不满足不递减性质
                     * 此时必须改变nums[i] */
                    nums[i] = nums[i-1];
            }
        }
        return true;
    }
};