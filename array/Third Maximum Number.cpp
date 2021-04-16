/**
 * Leetcode 414. 第三大的数
 * 给你一个非空数组，返回此数组中 第三大的数 。如果不存在，则返回数组中最大的数。
 *
 * 示例 1：
 *  输入：[3, 2, 1]
 *  输出：1
 *  解释：第三大的数是 1 。
 *
 * 示例 2：
 *  输入：[1, 2]
 *  输出：2
 *  解释：第三大的数不存在, 所以返回最大的数 2 。
 *
 * 示例 3：
 *  输入：[2, 2, 3, 1]
 *  输出：1
 *  解释：注意，要求返回第三大的数，是指在所有不同数字中排第三大的数。
 *  此例中存在两个值为 2 的数，它们都排第二。在所有不同数字中排第三大的数为 1 。
 *
 * 提示：
 *  (1)1 <= nums.length <= 10^4
 *  (2)-2^31 <= nums[i] <= 2^31 - 1
 *
 * 进阶：你能设计一个时间复杂度 O(n) 的解决方案吗？
 */
#include <vector>
#include <climits>
using std::vector;

/* 三个变量分别代表最大值, 次大值, 第三大值即可 */
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        long first = LONG_MIN, second = LONG_MIN, third = LONG_MIN;
        for (int x : nums) {
            /**
             * 为什么要判断条件是大于等于?
             * 如果只是大于, 那么最大值出现两次时
             * 就会错误地更新次大值或者第三大值, 
             * 因此需要用大于等于将这种情况包含起来,
             * 然后在分支里再判断是否等于即可
             */
            if (x >= first) {
                if (x == first) continue;
                third = second;
                second = first;
                first = x;
            } else if (x >= second) {
                if (x == second) continue;
                third = second;
                second = x;
            } else if (x > third) {
                third = x;
            }
        }
        return third == LONG_MIN ? first : third;
    }
};