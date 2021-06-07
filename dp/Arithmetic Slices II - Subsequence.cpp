/**
 * Leetcode 446. 等差数列划分 II - 子序列
 * 如果一个数列至少有三个元素，并且任意两个相邻元素之差相同，则称该数列为等差数列。
 * 例如，以下数列为等差数列:
 * 1, 3, 5, 7, 9
 * 7, 7, 7, 7
 * 3, -1, -5, -9
 * 以下数列不是等差数列。
 * 1, 1, 2, 5, 7
 *  
 * 数组 A 包含 N 个数，且索引从 0 开始。
 * 该数组子序列将划分为整数序列 (P0, P1, ..., Pk)，满足 0 ≤ P0 < P1 < ... < Pk < N。
 *  
 * 如果序列 A[P0]，A[P1]，...，A[Pk-1]，A[Pk] 是等差的，
 * 那么数组 A 的子序列 (P0，P1，…，PK) 称为等差序列。值得注意的是，这意味着 k ≥ 2。
 * 
 * 函数要返回数组 A 中所有等差子序列的个数。
 * 输入包含 N 个整数。每个整数都在 -231 和 231-1 之间，另外 0 ≤ N ≤ 1000。保证输出小于 231-1。
 *  
 * 示例：
 *  输入：[2, 4, 6, 8, 10]
 *  输出：7
 *  解释：
 *  所有的等差子序列为：
 *   [2,4,6]
 *   [4,6,8]
 *   [6,8,10]
 *   [2,4,6,8]
 *   [4,6,8,10]
 *   [2,4,6,8,10]
 *   [2,6,10]
 
 */
#include <vector>
#include <unordered_map>
using std::vector;
using std::unordered_map;

#define ULL unsigned long long

/**
 * dp[i][delta]: 以nums[i]结尾, 公差为delta的等差数列个数
 * 递推公式:
 *  设nums[i] - nums[j] = delta
 *  dp[i][delta] = dp[i][delta] + dp[j][delta] + 1
 *                 dp[i][delta] + 1
 */
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return 0;
        vector<unordered_map<ULL, int>> dp(n);
        int ans = 0;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                ULL delta = (ULL)nums[i] - (ULL)nums[j];
                int cnt = 0;
                if (dp[j].count(delta) != 0) {
                    /* 以nums[j]结尾, 公差为delta的等差数列有cnt个
                     * 那么以nums[i]结尾, 公差为delta的等差数列就多了cnt个 */
                    cnt = dp[j][delta];
                    /* 这里加一是为了处理"弱等差数列"
                     * 例如可能存在nums[k](j < i < k)
                     * 使得nums[j], nums[i], nums[k]形成等差数列 */
                    dp[i][delta] += cnt + 1;
                } else {
                    /* 处理长度为2的"弱等差数列"
                     * 做初始化工作 */
                    dp[i][delta]++;
                }
                /* 只有长度大于2的等差数列才能被算进答案 */
                ans += cnt;
            }
        }
        return ans;
    }
};