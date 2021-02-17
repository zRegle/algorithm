/**
 * Leetcode 312.戳气球
 * 有 n 个气球，编号为0 到 n - 1，每个气球上都标有一个数字，这些数字存在数组 nums 中。
 * 现在要求你戳破所有的气球。戳破第 i 个气球，你可以获得 nums[i - 1] * nums[i] * nums[i + 1] 枚硬币。
 * 这里的 i - 1 和 i + 1 代表和 i 相邻的两个气球的序号。
 * 如果 i - 1或 i + 1 超出了数组的边界，那么就当它是一个数字为 1 的气球。
 * 求所能获得硬币的最大数量。
 *
 * 示例 1：
 *  输入：nums = [3,1,5,8]
 *  输出：167
 *  解释：
 *   nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
 *   coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
 * 示例 2：
 *  输入：nums = [1,5]
 *  输出：10
 *
 * 提示：
 *  1.n == nums.length
 *  2.1 <= n <= 500
 *  3.0 <= nums[i] <= 100
 */
#include <vector>
using namespace std;

/* 详细的解题思路参考分治文件夹, dp是基于分治的基础上的 */

/**
 * 设coins(i, j)为不戳破i和j气球下, 区间(i, j)最多获得的硬币数
 * 我可以枚举(i, j)区间的所有k, 然后取最大值即可, 转移方程如下:
 *   coins(i, j) = max{val[i] * val[k] * val[j] + coins(i, k) + coins(k, j) | i < k < j}
 *   其中val[k]为k代表的气球的数字
 *   公式中第一个元素代表, (i, j)区间内所有的气球都被戳破, 只剩下i, k, j三个气球时, 戳破k气球获得的硬币数
 *   第二三个元素代表两个子问题
 */

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n+2, vector<int>(n+2, 0));
        /* 为数组添上两个虚拟气球作为边界, 即nums[-1]和nums[n], 方便后续处理
         * 其余元素为val[i] = nums[i-1] */
        vector<int> val(n+2, 0);
        val[0] = val[n+1] = 1;
        for (int i = 1; i <= n; i++) {
            val[i] = nums[i-1];
        }
        /**
         * 两点需要注意:
         * 1. (i, j)之间至少存在一个元素, 不然没有意义, 因此i的范围是[0, n-1], j的范围是[i+2, n+1]
         * 2. i必须从n-1 -> 0来迭代, 因为i<k<j, dp[i][j]依赖于dp[i][k]和dp[k][j]
         *    如果从0 -> n-1迭代, 因为k>i大, 所以在算dp[i][j]时, dp[k][j]还没准备好, 是错误的
         *    如果从n-1 -> 0迭代, 因为j>k, 所以dp[i][k]位于dp[i][j]的左侧, 计算过, 可以使用
         *                           k>i, 所以dp[k][j]位于dp[i][j]的下一行, 也计算过, 可以使用
         */
        for (int i = n-1; i >= 0; i--) {
            for (int j = i+2; j <= n+1; j++) {
                for (int k = i+1; k < j; k++) {
                    dp[i][j] = max(dp[i][j],
                                   val[i] * val[k] * val[j] + dp[i][k] + dp[k][j]);
                }
            }
        }
        return dp[0][n+1];
    }
};