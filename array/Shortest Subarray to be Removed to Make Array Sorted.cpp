/**
 * Leetcode 1574. 删除最短的子数组使剩余数组有序
 * 给你一个整数数组 arr ，请你删除一个子数组（可以为空），使得 arr 中剩下的元素是 非递减 的。
 * 一个子数组指的是原数组中连续的一个子序列。
 * 请你返回满足题目要求的最短子数组的长度。
 *
 * 示例 1：
 *  输入：arr = [1,2,3,10,4,2,3,5]
 *  输出：3
 *  解释：我们需要删除的最短子数组是 [10,4,2] ，长度为 3 。剩余元素形成非递减数组 [1,2,3,3,5] 。
 *       另一个正确的解为删除子数组 [3,10,4] 。
 * 示例 2：
 *  输入：arr = [5,4,3,2,1]
 *  输出：4
 *  解释：由于数组是严格递减的，我们只能保留一个元素。所以我们需要删除长度为 4 的子数组，
 *       要么删除 [5,4,3,2]，要么删除 [4,3,2,1]。
 * 示例 3：
 *  输入：arr = [1,2,3]
 *  输出：0
 *  解释：数组已经是非递减的了，我们不需要删除任何元素。
 * 示例 4：
 *  输入：arr = [1]
 *  输出：0
 */
#include <vector>
#include <climits>
using namespace std;

/**
 * 删除一个子数组后有序, 有三种情况:
 *  1.删除开头的子数组
 *  2.删除结尾的子数组
 *  3.删除中间的子数组
 * 求这三者之间的最小值即可
 */

class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int len = arr.size();
        int left = 0, right = len - 1;
        int prev = INT_MIN;
        /* 循环结束后[0, left-1]有序 */
        while (left < len && arr[left] >= prev) {
            prev = arr[left];
            left++;
        }
        if (left == len)
            return 0;
        prev = INT_MAX;
        /* 循环结束后[right+1, len-1]有序 */
        while (right > 0 && arr[right] <= prev) {
            prev = arr[right];
            right--;
        }
        /* 除了左边有序的子数组外全部删除 和 除了右边有序的子数组外全部删除
         * 两者比较, 取最小值 */
        int ans = min(len - left, right + 1);

        /* 删除中间的子数组, 使得左边有序的最大值小于等于右边有序的最小值 */
        int i = 0, j = right + 1;
        while (i < left && j < len) {
            if (arr[i] <= arr[j]) {
                ans = min(ans, j - i - 1);
                i++;
            } else {
                j++;
            }
        }
        return ans;
    }
};