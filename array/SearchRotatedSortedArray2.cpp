/* Leetcode 81.搜索旋转排序数组2
 * 假设按照升序排序的数组在预先未知的某个点上进行了旋转。
 * (例如，数组 [0,0,1,2,2,5,6] 可能变为 [2,5,6,0,0,1,2])。
 * 编写一个函数来判断给定的目标值是否存在于数组中。若存在返回true，否则返回 false。
 * 
 * 跟不存在重复的数那道题的区别在于:
 * 可能存在left != right-1 && nums[left] == nums[mid] == nums[right]
 * 如: [1,1,3,1] 或者 [1,3,1,1,1]
 * 要另外处理这种情况
 */
#include <vector>
using namespace std;

//比较笨的方法
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        if (nums.empty()) return false;
        return binary_search(nums, target, 0, nums.size()-1);
    }
private:
    bool binary_search(vector<int>& nums, int target, int left, int right) {
        if (left <= right) {
            int mid = (left + right) >> 1;
            if (nums[mid] == target) return true;
            if (nums[left] == nums[mid] && nums[mid] == nums[right]) {
                //我们不知道target到底在左半部分还是右半部分, 分别递归搜索
                bool l = binary_search(nums, target, left, mid-1);
                bool r = binary_search(nums, target, mid+1, right);
                return l || r;
            }
            if (nums[mid] >= nums[left]) {
                if (nums[left] <= target && target < nums[mid])
                    return binary_search(nums, target, left, mid-1);
                else
                    return binary_search(nums, target, mid+1, right);
            } else {
                if (nums[mid] < target && target <= nums[right])
                    return binary_search(nums, target, mid+1, right);
                else
                    return binary_search(nums, target, left, mid-1);
            }
        }
        return false;
    }
};

//比较好的做法
class Solution2 {
public:
    bool search(vector<int>& nums, int target) {
        if (nums.empty()) return false;
        int left = 0, right = nums.size()-1;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (nums[mid] == target) return true;
            //当遇到特殊情况时,我们只需要缩窄一下搜索区间即可
            if (nums[left] == nums[mid] && nums[mid] == nums[right]) {
                left++;
                right--;
                continue;
            }
            if (nums[left] <= nums[mid]) {
                if (nums[left] <= target && target < nums[mid])
                    right = mid-1;
                else
                    left = mid+1;
            } else {
                if (nums[mid] < target && target <= nums[right])
                    left = mid+1;
                else
                    right = mid-1;
            }
        }
        return false;
    }
};