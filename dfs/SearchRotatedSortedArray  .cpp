//Leetcode 33.搜索旋转排序数组
//假设按照升序排序的数组在预先未知的某个点上进行了旋转。
//(例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2])。
//搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。
//你可以假设数组中不存在重复的元素。
//你的算法时间复杂度必须是 O(log n) 级别。
//示例 1:
//  输入: nums = [4,5,6,7,0,1,2], target = 0
//  输出: 4
//示例 2:
//  输入: nums = [4,5,6,7,0,1,2], target = 3
//  输出: -1
#include <vector>
using namespace std;

//二分搜索魔改版
//数组看起来就像一个三角形
//  .
// . .
//.   .
//那么在峰值那个点的左右两边都是有序数组, 我们可以对两边分别进行二分搜索
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.empty()) return -1;
        int left = 0, right = nums.size()-1;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (nums[mid] == target) return mid;
            if (nums[mid] >= nums[left]) { //左半边是完全升序的
                if (nums[left] <= target && target < nums[mid]) //target在[left, mid)里
                    right = mid - 1;
                else
                    left = mid + 1; //target在(mid, right]里, 那么对右边进行二分搜索
            } else {
                //右半边是完全升序的
                if (nums[mid] < target && target <= nums[right])    //target在(mid, right]里
                    left = mid + 1;
                else
                    right = mid - 1;    //target在[left, mid)里
            }
        }
        return -1;
    }
};