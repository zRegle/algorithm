/**
 * Leetcode 645. 错误的集合
 * 集合 s 包含从 1 到 n 的整数。
 * 不幸的是，因为数据错误，导致集合里面某一个数字复制了成了集合里面的另外一个数字的值，
 * 导致集合 丢失了一个数字 并且 有一个数字重复 。
 * 给定一个数组 nums 代表了集合 S 发生错误后的结果。
 * 请你找出重复出现的整数，再找到丢失的整数，将它们以数组的形式返回。
 * 
 * 示例 1：
 *  输入：nums = [1,2,2,4]
 *  输出：[2,3]
 * 
 * 示例 2：
 *  输入：nums = [1,1]
 *  输出：[1,2]
 * 
 * 提示：
 *  (1)2 <= nums.length <= 10^4
 *  (2)1 <= nums[i] <= 10^4
 */

#include <vector>
using std::vector;

/* 排序、哈希表做法就不介绍了 */

/* 思路与leetcode 260有点类似 */
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int n = nums.size();
        /**
         * 设重复的数字为x, 丢失的数字为y
         * 在数组后再添加[1, n] n个数字
         * 那么x出现了3次, y出现了一次, 其他数字都出现了2次
         * 这2n个数字异或的结果就是x ^ y
         */
        int xorSum = 0;
        for (int i = 1; i <= n; i++) {
            xorSum ^= i;
        }
        for (int val : nums)
            xorSum ^= val;
        /* 获取最后一个为1的bit, 这个bit要么来自x要么来自y
         * x & (-x)的解释参考leetcode 260 */
        int lowbit = xorSum & (-xorSum);
        int x = 0, y = 0;
        /**
         * 将这2n个数字划分为两组,
         * A组跟lowbit与不为0, B组跟lowbit与为0
         * 因为一个数字不可能同时出现在A组和B组
         * 因此除了x, y之外, 其他数字必然在其中一个组出现了两次
         * 因此A组所有数字异或结果, B组所有数字异或结果就是x和y
         */
        for (int val : nums) {
            if (lowbit & val)
                x ^= val;
            else
                y ^= val;
        }
        for (int i = 1; i <= n; i++) {
            if (lowbit & i)
                x ^= i;
            else
                y ^= i;
        }
        /**
         * 此时已经得到x和y, 但不知道哪个是重复的
         * 哪个是丢失的, 重新遍历一遍数组即可
         */
        vector<int> ans(2);
        for (int val : nums) {
            if (val == x) {
                ans[0] = x;
                ans[1] = y;
                break;
            } else if (val == y) {
                ans[0] = y;
                ans[1] = x;
                break;
            }
        }
        return ans;
    }
};