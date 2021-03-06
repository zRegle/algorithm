/**
 * Leetcode 581. 最短无序连续子数组
 * 给你一个整数数组 nums ，你需要找出一个 连续子数组 ，
 * 如果对这个子数组进行升序排序，那么整个数组都会变为升序排序。
 * 请你找出符合题意的 最短 子数组，并输出它的长度。
 * 
 * 示例：
 *  输入：nums = [1,2,6,4,8,10,9,15,17]
 *  输出：5
 *  解释：你只需要对 [6, 4, 8, 10, 9] 进行升序排序，那么整个表都会变为升序排序。
 */
#include <vector>
#include <algorithm>
using namespace std;

/* 时间O(nlogn), 空间O(n) */
class Solution0 {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        auto copy = nums;   /* 拷贝一份原数组 */
        sort(copy.begin(), copy.end()); /* 排序 */
        int len = nums.size();
        /**
         * 要求的最短子数组的头尾指针
         * end设置成-1是为了处理原数组本来就是升序的情况
         */
        int start = 0, end = -1;
        /* 比较排序后的数组和原数组 */
        /* 从头往后找, 找到第一个不相等的元素 */
        for (int i = 0; i < len; i++) {
            if (copy[i] != nums[i]) {
                start = i;
                break;
            }
        }
        /* 从尾部往前找, 找到第一个不相等的元素 */
        for (int i = len-1; i >= 0; i--) {
            if (copy[i] != nums[i]) {
                end = i;
                break;
            }
        }
        return end - start + 1;
    }
};


/**
 * 将原数组看成三部分:
 *  (1)左半部分是递增子序列
 *  (2)中间是我们要排序的最短子序列
 *  (3)右半部分还是递增序列
 * 不难看出, 左半部分的最大值 < 中间部分的任意值
 *          右半部分的最小值 > 中间部分的任意值
 * 记中间部分的左右边界为start和end
 * 参考链接:
 * https://leetcode-cn.com/problems/shortest-unsorted-continuous-subarray/solution/si-lu-qing-xi-ming-liao-kan-bu-dong-bu-cun-zai-de-/
 *
 * 记中间部分的最大值max对应的下标为i, 我们不难发现i ∈ [start, end)
 * 因为如果i = end, 那么i就可以归并到右半部分, end - start就不是最短数组
 * 同理, 中间部分的最小值min对应的下标为j, 有j ∈ (start, end]
 *
 * 我们从左往右遍历, 维护一个最大值maxVal,
 * 那么我们在进入右半部分前, 任意nums[i] < maxVal, 我们找到最后一个小于maxVal的值
 * 就是我们要找的右边界end
 *
 * 同理, 从右往左遍历, 维护一个最小值minVal,
 * 那么我们在进入左半部分前, 任意nums[i] > minVal, 我们找到最后一个大于minVal的值
 * 就是我们要找的左边界start
 */
class Solution1 {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int len = nums.size();
        int maxVal = nums[0], minVal = nums.back();
        int start = 0, end = -1;
        for (int i = 0; i < len; i++) {
            /* 从左往右遍历, 寻找右边界 */
            if (maxVal > nums[i]) {
                end = i;
            } else {
                maxVal = nums[i];
            }
            /* 从右往左遍历, 寻找左边界 */
            if (minVal < nums[len-i-1]) {
                start = len - i - 1;
            } else {
                minVal = nums[len-i-1];
            }
        }
        return end - start + 1;
    }
};