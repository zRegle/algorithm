/* Leetcode 239.滑动窗口最大值
 * 给定一个数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。
 * 你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
 * 返回滑动窗口中的最大值。
 * 进阶: 你能在线性时间复杂度内解决此题吗？
 * 示例:
 *  输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
 *  输出: [3,3,5,5,6,7] 
 */
#include <vector>
#include <deque>
using namespace std;

/* 另一种解法参考array文件夹里同名文件 */

/* 动态规划法
 * 将数组分成数个大小为k的块(最后一个可能不够k个元素)
 * 滑动窗口可能位于一个块内, 或者横跨两个块(不可能横跨2个或以上的块)
 * 设left[i] = 下标i所在的块开头到下标i的最大值(左->右)
 *  例如: k = 3
 *  nums = 1,3,-1 | -3,5,3 | 6,7;
 *  nums[5]位于第二个块, 从这个块的开头到下标5的最大值是5, 所以left[3] = 5
 * 设right[i] = 下标i所在的块结尾到下标i的最大值(右->左)
 *  例如: k = 3
 *  nums = 1,3,-1 | -3,5,3 | 6,7;
 *  nums[3]位于第二个块, 从这个块的结尾到下标3的最大值是5, 所以right[3] = 5
 * 那么对于从i到j的滑动窗口, 它的最大值就是
 *  max(right[i], left[j])
 */
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0 || k == 0) return vector<int>();
        if (k == 1) return nums;

        vector<int> left(n, 0);
        left[0] = nums[0];
        vector<int> right(n, 0);
        right[n-1] = nums[n-1];
        for (int i = 1; i < n; i++) {
            if (i % k == 0)
                /* i刚好是一个块的开始 */
                left[i] = nums[i];
            else
                left[i] = max(left[i-1], nums[i]);

            int j = n - i - 1;
            if ((j + 1) % k == 0)
                /* j刚好是一个块的结束 */
                right[j] = nums[j];
            else
                right[j] = max(right[j+1], nums[j]);
        }

        vector<int> output(n-k+1, 0);
        for (int i = 0; i < n-k+1; i++)
            /* i到i+k-1的滑动窗口 */
            output[i] = max(right[i], left[i+k-1]);
        return output;
    }
};