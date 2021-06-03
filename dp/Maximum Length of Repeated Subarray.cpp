/**
 * Leetcode 718.最长重复子数组
 * 给两个整数数组 A 和 B ，返回两个数组中公共的、长度最长的子数组的长度。
 *
 * 示例：
 *  输入：
 *  A: [1,2,3,2,1]
 *  B: [3,2,1,4,7]
 *  输出：3
 *  解释：长度最长的公共子数组是 [3, 2, 1] 。
 *
 * 提示：
 * (1)1 <= len(A), len(B) <= 1000
 * (2)0 <= A[i], B[i] < 100
 */
#include <vector>
using std::vector;
using std::max;

/* dp[i][j]表示数组A以A[i]结尾和数组B以B[j]结尾的最长公共子数组
 * 递推公式:
 *  (1)如果A[i] == B[j]
 *    a.i > 0 && j > 0, dp[i][j] = dp[i-1][j-1] + 1
 *    b.i == 0 || j == 0, dp[i][j] = 1
 *  
 *  (2)A[i] != B[j], dp[i][j] = 0
 */
class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int ans = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (nums1[i] == nums2[j]) {
                    if (i > 0 && j > 0)
                        dp[i][j] = dp[i-1][j-1] + 1;
                    else
                        dp[i][j] = 1;
                    ans = max(ans, dp[i][j]);
                }
            }
        }
        return ans;
    }
    /* 空间复杂度优化, 递推关系只依赖左上角的格子 */
    int optimize(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        int ans = 0;
        vector<int> dp(n, 0);
        for (int i = 0; i < m; i++) {
            for (int j = n-1; j >= 0; j--) {
                if (nums1[i] == nums2[j]) {
                    if (i > 0 && j > 0)
                        dp[j] = dp[j-1] + 1;
                    else
                        dp[j] = 1;
                    ans = max(ans, dp[j]);
                } else {
                    /* 注意这里要更新当前行结果为0
                     * 不然就错误地保存了上一行的结果到当前行 */
                    dp[j] = 0;
                }
            }
        }
        return ans;
    }
};