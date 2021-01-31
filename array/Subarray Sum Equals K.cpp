/**
 * Leetcode 560. 和为K的子数组
 * 给定一个整数数组和一个整数 k，你需要找到该数组中和为 k 的连续的子数组的个数。
 * 示例 1 :
 *  输入:nums = [1,1,1], k = 2
 *  输出: 2 , [1,1] 与 [1,1] 为两种不同的情况。
 * 说明 :
 *  数组的长度为 [1, 20,000]。
 *  数组中元素的范围是 [-1000, 1000] ，且整数 k 的范围是 [-1e7, 1e7]。
 */
#include <vector>
#include <unordered_map>
using std::vector;
using std::unordered_map;

/* O(N²)的方法直接略过, 来看O(N)的方法 */

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int sum = 0, cnt = 0;
        /* key -> 前缀和
         * value -> 个数 */
        unordered_map<int, int> preSum;
        preSum[0] = 1; /* 前缀和为0的个数为一, 即选择0个元素 */
        for (int n : nums) {
            sum += n;
            /* 先获得前缀和为 preSum - k 的个数，加到计数变量里 */
            if (preSum.find(sum - k) != preSum.end())
                /* 设当前下标为i, 
                 * 前缀和为preSum - k的下标集合为{j0, j1, ..., jx}
                 * 那么[j0, i], [j1, i], ... , [jx, i]都是符合要求的子区间
                 * 因此此时cnt += preSum[sum - k]
                 */
                cnt += preSum[sum - k];
            /* 然后维护 preSum 的定义 */
            preSum[sum]++;
        }
        return cnt;
    }
};