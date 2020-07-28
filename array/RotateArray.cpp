/* Leetcode 189.旋转数组
 * 给定一个数组，将数组中的元素向右移动k个位置，其中k是非负数。
 * 要求使用空间复杂度为O(1)的原地算法。
 */
#include <vector>
using namespace std;

class Solution {
public:
    /* 暴力解法, 将数字一步一步移到对应的位置上,O(NK)复杂度 */
    void rotate(vector<int>& nums, int k) {
        int l = nums.size();
        k = k % l;
        for (int i = 0; i < k; i++) {
            for (int j = 1; j < l; j++) {
                swap(nums[0], nums[j]);
            }
        }
    }
};

class Solution1 {
public:
    /* 直接将数字移到合适的位置上 */
    void rotate(vector<int>& nums, int k) {
        int l = nums.size();
        k = k % l;
        /* start: 外层循环开始的下标
         * cnt: 循环计数器
         * cur: 用于内层循环的下标
         * prev: 被交换出去的数字
         */
        int start = 0, cnt = 0, cur, prev;
        while (cnt < l) {
            cur = start, prev = nums[start];
            do {
                cur = (cur + k) % l;
                swap(prev, nums[cur]);
                cnt++;
            } while (cur != start); /* 当重新回到start时退出, 防止死循环 */
            /* 更新开始下标 */
            start++;
        }
    }
};

class Solution2 {
public:
    void rotate(vector<int>& nums, int k) {
        int l = nums.size();
        k = k % l;
        if (k == 0) return;
        /* 翻转整个数组 */
        for (int i = 0; i < l >> 1; i++)
            swap(nums[i], nums[l-i-1]);
        /* 翻转前k个数 */
        for (int i = 0; i < k >> 1; i++)
            swap(nums[i], nums[k-i-1]);
        /* 翻转后l-k个数 */
        for (int i = 0; i < (l-k) >> 1; i++)
            swap(nums[i+k], nums[l-i-1]);
    }
};