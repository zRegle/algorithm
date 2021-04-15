/**
 * Leectcode 162. 寻找峰值
 * 峰值元素是指其值大于左右相邻值的元素。
 * 给你一个输入数组 nums，找到峰值元素并返回其索引。数组可能包含多个峰值，在这种情况下，返回 任何一个峰值 所在位置即可。
 * 你可以假设 nums[-1] = nums[n] = -∞ 。
 *
 * 示例 1：
 *  输入：nums = [1,2,3,1]
 *  输出：2
 *  解释：3 是峰值元素，你的函数应该返回其索引 2。
 * 示例 2：
 *  输入：nums = [1,2,1,3,5,6,4]
 *  输出：1 或 5
 *  解释：你的函数可以返回索引 1，其峰值元素为 2；或者返回索引 5， 其峰值元素为 6。
 *
 * 提示：
 *  (1)1 <= nums.length <= 1000
 *  (2)-231 <= nums[i] <= 231 - 1
 *  (3)对于所有有效的 i 都有 nums[i] != nums[i + 1]
 *
 * 进阶：你可以实现时间复杂度为 O(logN) 的解决方案吗？
 */
#include <vector>
using namespace std;

/**
 * 因为:
 * (1)对于所有有效的 i 都有 nums[i] != nums[i + 1]
 * (2)nums[-1] = nums[n] = -∞
 * 因此数组必定存在峰值
 *
 * 又因为我们只需要返回其中一个峰值即可, 所以可以用二分查找
 * 只向大于当前元素的方向查找即可
 */
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int len = nums.size();
        if (len == 1) return 0;
        int left = 0, right = len-1;
        while (left < right) {
            int mid = (left + right) >> 1;
            if (nums[mid] < nums[mid+1])
                /* nums[mid]处于上升阶段 */
                left = mid + 1;
            else
                /**
                 * nums[mid]处于下降阶段
                 * nums[mid]可能就是峰值
                 */
                right = mid;
        }
        return left;
    }
};