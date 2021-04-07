/**
 * 剑指Offer - 和为s的连续正数序列
 * 输入一个正整数 target ，输出所有和为 target 的连续正整数序列（至少含有两个数）。
 * 序列内的数字由小到大排列，不同序列按照首个数字从小到大排列。
 *
 * 示例 1：
 *  输入：target = 9
 *  输出：[[2,3,4],[4,5]]
 * 示例 2：
 *  输入：target = 15
 *  输出：[[1,2,3,4,5],[4,5,6],[7,8]]
 *
 * 限制：1 <= target <= 10^5
 */
#include <vector>
using std::vector;

/* 滑动窗口, left和right初始指向1和2(至少两个数)
 * 然后不断调整left和right即可 */
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        int left = 1, right = 2, sum = 3;
        vector<vector<int>> ans;
        vector<int> v;
        int mid = (target + 1) / 2; /* left的最大值, 因为至少两个数字 */
        while (left < mid) {
            if (sum == target) {
                int size = right - left + 1;
                v.resize(size, 0);
                for (int i = 0; i < size; i++) {
                }
                ans.push_back(v);
            } else if (sum > target) {
                /* sum超过target, 缩小滑动窗口 */
                sum -= left;
                left++;
                /* continue避免重复加right */
                continue;
            }
            /**
             * 两种情况:
             * 1.sum == target, sum += right必定超过target, 下次循环调整left
             * 2.sum < target, sum += right显而易见
             */
            right++;
            sum += right;
        }
        return ans;
    }
};