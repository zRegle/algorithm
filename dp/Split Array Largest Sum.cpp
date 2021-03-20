/**
 * Leetcode 410. 分割数组的最大值
 * 给定一个非负整数数组 nums 和一个整数 m ，你需要将这个数组分成 m 个非空的连续子数组。
 * 设计一个算法使得这 m 个子数组各自和的最大值最小。
 *
 * 示例 1：
 *  输入：nums = [7,2,5,10,8], m = 2
 *  输出：18
 * 解释：
 *  一共有四种方法将 nums 分割为 2 个子数组。 其中最好的方式是将其分为 [7,2,5] 和 [10,8] 。
 *  因为此时这两个子数组各自的和的最大值为18，在所有情况中最小。
 * 示例 2：
 *  输入：nums = [1,2,3,4,5], m = 2
 *  输出：9
 * 示例 3：
 *  输入：nums = [1,4,4], m = 3
 *  输出：4
 *
 * 提示：
 *  (1)1 <= nums.length <= 1000
 *  (2)0 <= nums[i] <= 106
 *  (3)1 <= m <= min(50, nums.length)
 */
#include <vector>
#include <cstdint>
#include <climits>
using namespace std;

/**
 * dp[i][j]: 将数组的前i个数分割为j段所能得到的最大连续子数组和的最小值
 * 在考虑状态转移时, 我们在i的范围内枚举k, 其中i的前k个数被划分成j-1段, 剩余的[k+1, i]为一段, 加起来一共j段
 * 那么此时所有区间的和的最大值就是: val = max(dp[k][j-1], k+1到i]的求和)
 * 对于每一个k, 我们都算出其对应的val, 然后在它们中选取最小值, 就是dp[i][j]
 */
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        int n = nums.size();
        auto dp = vector<vector<uint64_t>>(n+1, vector<uint64_t>(m+1, LLONG_MAX));
        vector<uint64_t> preSum(n+1, 0); /* 前缀和, 方便计算 */
        for (int i = 1; i <= n; i++) {
            preSum[i] = preSum[i-1] + nums[i-1];
        }
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            /* 划分必须有效: 因此j要同时满足j <= i && j <= m */
            for (int j = 1; j <= min(i, m); j++) {
                for (int k = 0; k < i; k++) {
                    /**
                     * k = 0时, [0, i]划分成一段
                     * k != i, 因为我们不能说前i个数就已经划分成j-1段, 将0个元素划分成1段
                     * dp[k][j-1]: k必须大于等于j-1, 对于无效的dp[k][j-1], 因为初始化成了MAX, 所以不会对min产生影响
                     */
                    dp[i][j] = min(dp[i][j], max(dp[k][j-1], preSum[i] - preSum[k]));
                }
            }
        }
        return (int)dp[n][m];
    }
};