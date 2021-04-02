/**
 * Leetcode 730. 统计不同回文子序列
 * 给定一个字符串 S，找出 S 中不同的非空回文子序列个数，并返回该数字与 10^9 + 7 的模。
 * 通过从 S 中删除 0 个或多个字符来获得子序列。
 * 如果一个字符序列与它反转后的字符序列一致，那么它是回文字符序列。
 * 如果对于某个i，Ai != Bi，那么 A1, A2, ... 和 B1, B2, ... 这两个字符序列是不同的。
 *
 * 示例 1：
 * 输入：
 * S = 'bccb'
 *  输出：6
 *  解释：6 个不同的非空回文子字符序列分别为：'b', 'c', 'bb', 'cc', 'bcb', 'bccb'。
 *       注意：'bcb' 虽然出现两次但仅计数一次。
 *
 * 示例 2：
 *  输入：
 *  S = 'abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba'
 *  输出：104860361
 *  解释：共有 3104860382 个不同的非空回文子序列，对 10^9 + 7 取模为 104860361。
 *
 * 提示：
 *  (1)字符串 S 的长度将在[1, 1000]范围内。
 *  (2)每个字符 S[i] 将会是集合 {'a', 'b', 'c', 'd'} 中的某一个。
 */
#include <string>
#include <vector>
using namespace std;

/**
 * dp[i][j]: [i, j]区间不同回文串的个数
 *
 * 转移方程比较复杂, 分以下几种情况:
 *
 * (1)s[i] == s[j]:
 *     直觉出发, 此时应该dp[i][j] = 2 * dp[i+1][j-1] + 2
 *     首先, [i+1, j-1]有x种不同的回文串, 则[i+1, j-1]有x种不同的回文串
 *     其次, s[i]和s[j]作为两端, 与[i+1, j-1]组合起来又有x种不同的回文串
 *     因此, 第一项就是2 * dp[i+1][j-1]
 *     加二是因为s[i]和s[j]可以组合成一种回文串, s[i]也可以单独成回文串
 *
 *     举个例子:
 *     s = "aba", i = 0, j = 2:  dp[1][1] = 1 记录了文串"b",
 *     dp[i+1][j-1] * 2是因为先算dp[i+1][j-1]为第一次, 即"b"; 然后第二次是"aba“
 *     加二是因为回文串{"a", "aa"}
 *     最后dp[i][j]的结果为{"a", "b", "aa", "aba"}
 *
 *     但是我们需要考虑[i+1, j-1]中是否出现了跟s[i]和s[j]相同的字符
 *     因此需要遍历[i+1, j-1]中s[i]出现了多少次:
 *         (a)出现了一次, 比较简单, 去掉s[i]单独成回文串这一情况即可, 即:
 *              dp[i][j] = 2 * dp[i+1][j-1] + 1
 *
 *         (b)出现了两次或以上, 记[i+1, j-1]中s[i]第一次出现和最后一次出现的位置是low, high
 *            那么此时s[low] + s[low+1, high-1] + s[high]组合成的回文串跟
 *            s[i] + s[low+1, high-1] + s[j]组合成的回文串就重复计算了, 因此要减去重复的部分
 *            dp[i][j] = 2 * dp[i+1][j-1] - dp[low+1][high-1]
 *
 *            举个例子:
 *            "aacaa", i = 0, j = 4, dp[i+1][j-1]记录了回文串{"a",  "c", "aa", "aca"}
 *            2 * dp[i+1][j-1]记录了回文串{"a",  "c", "aa", "aca"}, 另外还有回文串{"aaa",  "aca", "aaaa", "aacaa"}
 *            其中{"aca"}重复了, 因此要减去这个重复的部分, 即dp[low+1][high-1]
 *            最后dp[i][j]记录了回文串{"a",  "c", "aa", "aca", "aaa", "aaaa", "aacaa"}
 *
 * (2)s[i] != s[j]
 *      此时dp[i][j] = dp[i+1][j] ∪ dp[i][j-1]
 *                  = dp[i+1][j] + dp[i][j-1] - dp[i+1][j] ∩ dp[i][j-1]
 *      即dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1]
 */
class Solution {
public:
    int countPalindromicSubsequences(string& s) {
        int n = s.size();
        vector<vector<int>> dp(n,vector<int>(n,0));
        for (int i = 0; i < n; i++)
            dp[i][i] = 1;
        const int mod = 1e9 + 7;
        for (int i = n-2; i >= 0; i--) {
            for (int j = i+1; j < n; j++) {
                if (s[i] == s[j]) {
                    dp[i][j] = 2 * dp[i+1][j-1];
                    /* 统计[i+1, j-1]中有多少个s[i] */
                    int low = i+1, high = j-1;
                    while (low <= high && s[low] != s[i]) low++;
                    while (low <= high && s[high] != s[i]) high--;
                    if (low < high) {
                        /* 至少两个s[i] */
                        dp[i][j] -= dp[low+1][high-1];
                    } else if (low > high) {
                        /* 一个也没有 */
                        dp[i][j] += 2;
                    } else {
                        /* 只有一个 */
                        dp[i][j]++;
                    }
                } else {
                    dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1];
                }
                if (dp[i][j] >= 0)
                    dp[i][j] %= mod;
                else
                    /* 整数溢出变成负值, 加回Mod */
                    dp[i][j] += mod;
            }
        }
        return dp[0][n-1];
    }
};