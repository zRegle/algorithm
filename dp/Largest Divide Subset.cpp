/**
 * Leetcode 368. 最大整除子集
 * 给你一个由 无重复 正整数组成的集合 nums ，请你找出并返回其中最大的整除子集 answer ，
 * 子集中每一元素对 (answer[i], answer[j]) 都应当满足：
 *  (1)answer[i] % answer[j] == 0 ，或
 *  (2)answer[j] % answer[i] == 0
 * 如果存在多个有效解子集，返回其中任何一个均可。
 *
 * 示例 1：
 *  输入：nums = [1,2,3]
 *  输出：[1,2]
 *  解释：[1,3] 也会被视为正确答案。
 * 示例 2：
 *  输入：nums = [1,2,4,8]
 *  输出：[1,2,4,8]
 *
 * 提示：
 *  (1)1 <= nums.length <= 1000
 *  (2)1 <= nums[i] <= 2 * 10^9
 *  (3)nums 中的所有整数 互不相同
 */
#include <vector>
#include <algorithm>
using namespace std;

/**
 * 可以转化为"最长上升子序列"问题
 * 设dp[i]: 以i为最大值的最大整除子集的长度
 *
 * 首先对原数组排序, 然后根据转移方程:
 * dp[i] = max{dp[j] + 1, j < i}, if nums[i] % nums[j] == 0
 *       = dp[i], if nums[i] % nums[j] ≠ 0
 *
 * 由于我们将 nums[i] 往某个数字后面接时（假设为 nums[j]），只检查了其与 nums[j] 的关系，
 * 并没有去检查 nums[i] 与 nums[j] 之前的数值是否具有「倍数/约数关系」。
 * 换句话说，我们只确保了最终答案 [a1, a2, a3, ..., an] 相邻两数值之间具有「倍数/约数关系」，
 * 并不明确任意两值之间具有「倍数/约数关系」。
 * 因此需要证明传递性: a|b, b|c => a|c
 * 由a|b可得b = x * a
 * 由b|c可得c = y * b
 * 那么有c = y * x * a, 可得a|c
 *
 */
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1);
        vector<int> path(n); /* 转移路径 */
        sort(nums.begin(), nums.end()); /* 排序 */
        int maxVal = 0, idx = -1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] % nums[j] == 0) {
                    if (dp[i] < dp[j] + 1) {
                        dp[i] = dp[j] + 1;
                        path[i] = j; /* 转移路径记录 */
                    }
                }
            }
            if (maxVal < dp[i]) {
                maxVal = dp[i];
                idx = i;
            }
        }
        vector<int> ans(maxVal);
        /* 回溯路径 */
        for (int i = maxVal-1; i >= 0; i--) {
            ans[i] = nums[idx];
            idx = path[idx];
        }
        return ans;
    }
};