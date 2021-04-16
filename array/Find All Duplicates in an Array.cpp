/**
 * Leetcode 442.数组中重复的数据
 * 给定一个整数数组 a，其中1 ≤ a[i] ≤ n （n为数组长度）, 其中有些元素出现两次而其他元素出现一次。
 * 找到所有出现两次的元素。
 * 
 * 你可以不用到任何额外空间并在O(n)时间复杂度内解决这个问题吗？
 * 示例：
 *  输入: [4,3,2,7,8,2,3,1]
 *  输出: [2,3]
 */
#include <vector>
#include <cmath>
using std::vector;

/**
 * 注意题目条件:
 *  (1)1 ≤ a[i] ≤ n （n为数组长度）
 *  (2)有些元素出现两次而其他元素出现一次
 * 
 * 思路:
 * 找到数字i时，将位置i处的数字翻转为负数。
 * 如果位置i上的数字已经为负，则i是出现两次的数字。
 * 
 * 类似于Leetcode 448
 */
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> ans;
        for (int i = 0; i < nums.size(); i++) {
            /* nums[i]有可能是负值, 先取绝对值 */
            int idx = abs(nums[i])-1;
            if (nums[idx] < 0)
                ans.push_back(idx+1);
            else
                nums[idx] = -nums[idx];
        }
        return ans;
    }
};