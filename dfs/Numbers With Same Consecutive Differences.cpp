/**
 * Leetcode 967. 连续差相同的数字
 * 返回所有长度为 N 且满足其每两个连续位上的数字之间的差的绝对值为 K 的非负整数。
 * 请注意，除了数字 0 本身之外，答案中的每个数字都不能有前导零。
 * 例如，01 因为有一个前导零，所以是无效的；但 0 是有效的。
 * 你可以按任何顺序返回答案。
 *  
 * 示例 1：
 * 输入：N = 3, K = 7
 * 输出：[181,292,707,818,929]
 * 解释：注意，070 不是一个有效的数字，因为它有前导零。
 */
#include <vector>
#include <queue>
using namespace std;

/* bfs方法请查看bfs文件夹 */

class Solution {
public:
    vector<int> numsSameConsecDiff(int n, int k) {
        vector<int> ans;
        for (int i = 1; i <= 9; i++) {
            dfs(i, 1, n, k, ans);
        }
        return ans;
    }

    void dfs(int prefix, int cnt, int n, int k, vector<int>& ans) {
        if (cnt == n) {
            ans.push_back(prefix);
            return;
        }
        int lastDigit = prefix % 10;
        if (lastDigit - k >= 0) {
            prefix *= 10;
            prefix += lastDigit - k;
            dfs(prefix, cnt + 1, n, k, ans);
            /* 回溯还原 */
            prefix /= 10;
        }
        /* 判断k是否为0, 防止duplicate */
        if (k != 0 && lastDigit + k <= 9) {
            prefix *= 10;
            prefix += lastDigit + k;
            dfs(prefix, cnt + 1, n, k, ans);
        }
    }
};