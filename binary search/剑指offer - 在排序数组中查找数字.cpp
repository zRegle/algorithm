/**
 * 剑指 Offer 53 - I. 在排序数组中查找数字 I
 * 统计一个数字在排序数组中出现的次数。
 * 
 * 示例 1:
 *  输入: nums = [5,7,7,8,8,10], target = 8
 *  输出: 2
 * 示例 2:
 *  输入: nums = [5,7,7,8,8,10], target = 6
 *  输出: 0
 * 
 * 限制：0 <= 数组长度 <= 50000
 */
#include <vector>
using namespace std;

/**
 * 二分: left, right恰好指向左右边界
 * [left, right]内都是目标数字, 长度为right - left + 1
 * 收缩的方式查看template.txt
 */
class Solution0 {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        if (!n) return 0;
        int start, end;
        int left = 0, right = n-1;
        /* 寻找左边界, 那么应使得mid偏向left, 采用m=(l+r)/2 */
        while (left < right) {
            int mid = (left + right) / 2;
            if (nums[mid] < target)
                left = mid+1;
            else
                right = mid;
        }
        /* 判断target是否存在 */
        if (nums[left] != target) return 0;
        /* mid偏向left, 退出后left就是左边界 */
        start = left;
        left = 0, right = n-1;
        /* 寻找右边界, 那么应使得mid偏向right, 采用m=(l+r+1)/2 */
        while (left < right) {
            int mid = (left + right + 1) / 2;
            if (nums[mid] > target)
                right = mid-1;
            else
                left = mid;
        }
        /* mid偏向right, 退出后right就是右边界 */
        end = right;
        return end - start + 1;
    }
};

/**
 * 二分: left, right包裹住左右边界
 * (left, right)包裹住目标数字, 长度为right - left - 1
 */
class Solution1 {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        if (!n) return 0;
        int start, end;
        int left = 0, right = n-1;
        while (left <= right) {
            int mid = (left+right)/2;
            if (nums[mid] <= target)
                /* mid偏向left, 即使相等我们也要右移left指针
                 * 最终只剩一个数时, left右移 */
                left = mid+1;
            else
                right = mid-1;
        }
        if (nums[left] != target) return 0;
        end = left;
        left = 0, right = n-1;
        while (left <= right) {
            int mid = (left+right)/2;
            if (nums[mid] >= target)
                /* mid偏向left, 即使相等我们也要左移right指针
                 * 最终只剩一个数时, right左移 */
                right = mid-1;
            else
                left = mid+1;
        }
        start = right;
        return end - start - 1;
    }
};