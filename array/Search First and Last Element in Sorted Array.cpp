/* Leetcode 34.在排序数组中查找元素的第一个和最后一个位置
 * 给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。
 * 你的算法时间复杂度必须是O(logn)级别。
 * 如果数组中不存在目标值，返回 [-1, -1]。
 * 示例 1:
 *  输入: nums = [5,7,7,8,8,10], target = 8
 *  输出: [3,4]
 * 示例 2:
 *  输入: nums = [5,7,7,8,8,10], target = 6
 *  输出: [-1,-1]
 */
#include <vector>
using namespace std;

//思路: 利用二分搜索不断逼近左右边界
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> ans(2, -1);
        if (nums.empty()) return ans;
        int left = 0, right = nums.size()-1;
        //搜索左边界
        while (left < right) {  //不能是<=, 这样当left = right时就死循环了
            int mid = (left + right) >> 1;
            if (nums[mid] < target) //说明target左边界在mid的右边
                left = mid + 1;
            else
                right = mid;    //说明target的左边界在mid的左边, 因为可能mid就是左边界, 所以不能是mid-1
        }
        //最终left = right, 判断是否等于target
        ans[0] = nums[left] == target ? left : -1;
        //下面搜索右边界
        left = 0, right = nums.size()-1;
        while (left < right) {
            int mid = ((left + right) >> 1) + 1;
            if (nums[mid] > target)
                right = mid-1;
            else
                left = mid;
        }
        ans[1] = nums[right] == target ? right : -1;
        return ans;
    }
};