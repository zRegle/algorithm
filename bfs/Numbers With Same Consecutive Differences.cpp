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

/* dfs方法请查看dfs文件夹 */

class Solution {
public:
    vector<int> numsSameConsecDiff(int n, int k) {
        queue<int> q;
        for (int i = 1; i <= 9; i++) q.push(i);
        int cnt = 1;
        while (cnt < n) {
            int size = q.size();
            while (size--) {
                int prefix = q.front(); q.pop();
                int lastDigit = prefix % 10;
                if (lastDigit >= k) {
                    int next = prefix * 10 + lastDigit - k;
                    q.push(next);
                }
                /* 判断k是否为0, 防止duplicate */
                if (k != 0 && lastDigit + k <= 9) {
                    int next = prefix * 10 + lastDigit + k;
                    q.push(next);
                }
            }
            cnt++;
        }
        vector<int> ans(q.size(), 0);
        for (int i = 0; !q.empty(); i++) {
            ans[i] = q.front();
            q.pop();
        }
        return ans;
    }
};