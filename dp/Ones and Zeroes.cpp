/**
 * Leetcode 474. 一和零
 * 给你一个二进制字符串数组 strs 和两个整数 m 和 n 。
 * 请你找出并返回 strs 的最大子集的大小，该子集中所有元素加起来 最多 有 m 个 0 和 n 个 1 。
 * 如果 x 的所有元素也是 y 的元素，集合 x 是集合 y 的 子集 。
 * 
 * 示例 1：
 *  输入：strs = ["10", "0001", "111001", "1", "0"], m = 5, n = 3
 *  输出：4
 *  解释：最多有 5 个 0 和 3 个 1 的最大子集是 {"10","0001","1","0"} ，因此答案是 4 。
 *       其他满足题意但较小的子集包括 {"0001","1"} 和 {"10","1","0"} 。{"111001"} 不满足题意，因为它含 4 个 1 ，大于 n 的值 3 。
 * 示例 2：
 *  输入：strs = ["10", "0", "1"], m = 1, n = 1
 *  输出：2
 *  解释：最大的子集是 {"0", "1"} ，所以答案是 2 。
 * 
 * 提示：
 *  (1)1 <= strs.length <= 600
 *  (2)1 <= strs[i].length <= 100
 *  (3)strs[i] 仅由 '0' 和 '1' 组成
 *  (4)1 <= m, n <= 100
 */
#include <string>
#include <vector>
using namespace std;

/* 可以看做是01背包, m n组合起来就是背包容量
 * dp[i][j][k]: 表示可以背包容量为j个0, k个1时, 前i个元素最多容纳的元素个数
 * 直接上空间优化版本 */

/* 另外一个角度: dp[i][j]表示i个1和j个0最多能拼出的字符串数目 */
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int size = strs.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for (int i = 1; i <= size; i++) {
            auto pair = count(strs[i-1]);
            int zero = pair.first, one = pair.second;
            for (int j = m; j >= zero; j--) {
                for (int k = n; k >= one; k--) {
                    dp[j][k] = max(dp[j][k], dp[j-zero][k-one]+1);
                }
            }
        }
        return dp[m][n];
    }

private:
    inline pair<int, int> count(string& s) {
        int zero = 0, one = 0;
        for (char c : s) {
            zero += c == '0';
            one += c == '1';
        }
        return make_pair(zero, one);
    }
};