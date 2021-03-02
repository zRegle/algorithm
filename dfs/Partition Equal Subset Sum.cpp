/**
 * Leetcode 416. 分割等和子集
 * 给定一个只包含正整数的非空数组。是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
 * 注意:
 *  每个数组中的元素不会超过 100
 *  数组的大小不会超过 200
 * 示例 1:
 *  输入: [1, 5, 11, 5]
 *  输出: true
 *  解释: 数组可以分割成 [1, 5, 5] 和 [11].
 *
 * 示例 2:
 *  输入: [1, 2, 3, 5]
 *  输出: false
 *  解释: 数组不能分割成两个元素和相等的子集.
 */
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_map>
using namespace std;

/**
 * 设nums元素之和为sum, 它的一半为target
 * 问题本质上归结为:
 * 是否可以从nums中挑选若干个元素, 使得元素和为target
 */

/* dp方法查看dp文件夹 */

/**
 * dfs暴搜 + 记忆化: 每个元素有选取和不选取两种可能
 */
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        /* 数组之和为奇数, 不可能划分两个和相等的子集 */
        if ((sum & 1) == 1) return false;
        int target = sum >> 1;
        int maxNum = *max_element(nums.begin(), nums.end());
        /* 数组最大值大于target, 剩下的元素之和一定小于target, 直接返回false */
        if (maxNum > target) return false;
        return dfs(0, 0, nums, sum >> 1);
    }

private:
    /* 记忆化数组 */
    unordered_map<string, bool> mem;
    /**
     * 判断到达下标idx, 当前累计和是cur, 是否满足要求
     * @param idx 当前数组下标, 即dfs深度
     * @param cur 当前累计和
     * @param nums 数组
     * @param target 目标
     * @return true or false
     */
    bool dfs(int idx, int cur, vector<int>& nums, int target) {
        if (cur > target || idx == nums.size())
            return false;
        if (cur == target)
            return true;
        /* key是到达idx时, 当前和是cur这个状态 */
        string key = to_string(idx) + ',' + to_string(cur);
        if (mem.find(key) != mem.end())
            return mem[key];
        /* 挑选数字nums[idx] */
        if (dfs(idx + 1, cur + nums[idx], nums, target)) {
            mem[key] = true;
            return true;
        }
        /* 不挑选数字nums[idx] */
        mem[key] = dfs(idx + 1, cur, nums, target);
        return mem[key];
    }
};