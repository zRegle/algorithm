/**
 * Leetcode 523. 连续的子数组和
 * 给你一个整数数组 nums 和一个整数 k ，编写一个函数来判断该数组是否含有同时满足下述条件的连续子数组：
 * 子数组大小 至少为 2 ，且子数组元素总和为 k 的倍数。
 * 如果存在，返回 true ；否则，返回 false 。
 * 如果存在一个整数 n ，令整数 x 符合 x = n * k ，则称 x 是 k 的一个倍数。
 *  
 * 示例 1：
 *  输入：nums = [23,2,4,6,7], k = 6
 *  输出：true
 *  解释：[2,4] 是一个大小为 2 的子数组，并且和为 6 。
 * 
 * 示例 2：
 *  输入：nums = [23,2,6,4,7], k = 6
 *  输出：true
 *  解释：[23, 2, 6, 4, 7] 是大小为 5 的子数组，并且和为 42 。 
 *        42 是 6 的倍数，因为 42 = 7 * 6 且 7 是一个整数。
 * 示例 3：
 *  输入：nums = [23,2,6,4,7], k = 13
 *  输出：false
 *  
 * 提示：
 * (1)1 <= nums.length <= 105
 * (2)0 <= nums[i] <= 109
 * (3)0 <= sum(nums[i]) <= 2^31 - 1
 * (4)1 <= k <= 2^31 - 1
 */
#include <unordered_map>
#include <vector>
using namespace std;

/**
 * 与leetcode 560类似
 * 
 * 同余定理: 如果(a - b) % k = 0, 则a % k = b % k
 * 反过来也是成立的: 如果a % k = b % k, 则(a - b) % k = 0
 * 
 * 证明:
 * 因为a % k = b % k, 不妨设a = xk + r, b = yk + r
 * a - b = (x - y)k, 明显整除k
 */
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        /**
         * 设sum[i] = Σnums[i]
         * 
         * key -> sum[i] % k
         * index -> key第一次出现的index
         */
        unordered_map<int, int> map;
        int mod, prev;
        /* 处理sum[i] % k = 0的情况 */
        map[0] = -1; 
        for (int i = 0; i < n; i++) {
            /* 因为1 <= k <= 2^31-1
             * 所以这里要防止溢出 */
            mod = (mod + nums[i]) % k;
            if (map.find(mod) != map.end()) {
                prev = map[mod];
                if (i - prev >= 2)
                    return true;
            } else {
                /* mod第一次出现, 插入index */
                map[mod] = i;
            }
        }
        return false;
    }
};