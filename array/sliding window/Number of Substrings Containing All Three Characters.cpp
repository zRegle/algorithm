/**
 * Leetcode 930. 和相同的二元子数组
 * 给你一个二元数组 nums ，和一个整数 goal ，请你统计并返回有多少个和为 goal 的 非空 子数组。
 * 子数组 是数组的一段连续部分。
 * 
 * 示例 1：
 *  输入：nums = [1,0,1,0,1], goal = 2
 *  输出：4
 *  解释：
 *   如下面所示，有 4 个满足题目要求的子数组：
 *   [(1,0,1),0,1]
 *   [(1,0,1,0),1]
 *   [1,(0,1,0,1)]
 *   [1,0,(1,0,1)]
 * 
 * 示例 2：
 *  输入：nums = [0,0,0,0,0], goal = 0
 *  输出：15
 * 
 * 提示：
 *  (1)1 <= nums.length <= 3 * 10^4
 *  (2)nums[i] 不是 0 就是 1
 *  (3)0 <= goal <= nums.length
 */
#include <vector>
#include <unordered_map>
using namespace std;

/* 类似leetcode 560的解法 */
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        unordered_map<int, int> map;
        map[0] = 1;
        int sum = 0, ans = 0;
        for (int x : nums) {
            sum += x;
            if (map.find(sum-goal) != map.end())
                ans += map[sum-goal];
            map[sum]++;
        }
        return ans;
    }
};

/**
 * 固定终点j, 满足sum[j] - sum[i] = goal的i落在一段连续的区间
 * i取区间中每一个数都满足条件
 * 我们可以令滑动窗口右边界为r, 使用两个左边界表示左区间[l1, l2)
 * 此时区间中的任何i都满足sum[j] - sum[i], 即一共有l2 - l1个
 */
class Solution1 {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int l1 = 0, l2 = 0, r = 0;
        int s1 = 0, s2 = 0;
        int ans = 0;
        while (r < nums.size()) {
            s1 += nums[r];
            /* 维护左区间的最左边界 */
            while (l1 <= r && s1 > goal) {
                s1 -= nums[l1];
                l1++;
            }
            s2 += nums[r];
            /* 维护左区间的最右边界
             * 注意s2 == goal也需要右移
             * 这样才能得到最右边界 */
            while (l2 <= r && s2 >= goal) {
                s2 -= nums[l2];
                l2++;
            }
            ans += l2 - l1;
            r++;
        }
        return ans;
    }
};

class Solution2 {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        /* sum不大于goal - sum不大于goal-1 = sum刚好等于goal */
        return atMost(nums, goal) - atMost(nums, goal-1);
    }

private:
    /* 统计sum不大于goal的子数组数目 */
    int atMost(vector<int>& nums, int goal) {
        if (goal < 0) return 0;
        int sum = 0, l = 0, r = 0;
        int ans = 0;
        while (r < nums.size()) {
            sum += nums[r];
            while (sum > goal) {
                sum -= nums[l];
                l++;
            }
            ans += r - l + 1;
            r++;
        }
        return ans;
    }
};