/* Leetcode 35.搜索插入位置
 * 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
 * 你可以假设数组中无重复元素。
 * 示例 1:
 *  输入: [1,3,5,6], 5
 *  输出: 2
 * 示例 2:
 *  输入: [1,3,5,6], 2
 *  输出: 1
 * 示例 3:
 *  输入: [1,3,5,6], 7
 *  输出: 4
 * 示例 4:
 *  输入: [1,3,5,6], 0
 *  输出: 0
 */
#include <vector>
using std::vector;

//明显要用二分搜索, 注意一下头尾两种特殊情况即可
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        if (nums.empty()) return 0;
        int left = 0, right = nums.size()-1;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (nums[mid] == target) return mid;
            if (nums[mid] > target)
                right = mid-1;
            else
                left = mid+1;
        }
        if (right < 0) return 0;    //特殊情况处理
        return nums[right] > target ? right-1 : right + 1;
    }
};