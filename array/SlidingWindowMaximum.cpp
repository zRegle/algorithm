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

/* 另一种解法参考dp文件夹里同名文件 */

/* 双向队列法 */
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> output;
        if (k == 0 || nums.empty()) return output;

        /* 双向队列, 存放下标, 有以下三个特点
         * (1)第一个元素是当前滑动窗口最大值的下标
         * (2)队列中的元素从头到尾是降序的
         * (3)队列中的元素是在滑动窗口范围内的
         */
        deque<int> windows;
        int idx = 0;
        while (idx < nums.size()) {
            if (!windows.empty() && idx - k >= windows.front())
                /* 上次滑动窗口最大值已经超出当前窗口范围
                 * 从队列中移除该元素
                 */
                windows.pop_front();
            while (!windows.empty() && nums[idx] > nums[windows.back()])
                /* 遇到的新元素比当前队列尾元素要大
                 * pop出队列尾, 因为这个队列尾不可能成为最大元素
                 * 如果这个队列尾要成为最大元素, 那么需要滑动窗口不包含当前元素
                 * 此时队列尾早就不包含在滑动窗口内了
                 */
                windows.pop_back();
            /* 插入新元素 */
            windows.push_back(idx);
            idx++;
            if (idx >= k)
                /* 保存当前窗口中最大值 */
                output.push_back(nums[windows.front()]);
        }
        return output;
    }
};
/* 每个元素都被处理了两次, 一次入队, 一次出队, 时间复杂度为O(N) */