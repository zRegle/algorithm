/**
 * Leetcode 354. 俄罗斯套娃信封问题
 * 给你一个二维整数数组 envelopes ，其中 envelopes[i] = [wi, hi] ，表示第 i 个信封的宽度和高度。
 * 当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，如同俄罗斯套娃一样。
 * 请计算 最多能有多少个 信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放到另一个信封里面）。
 * 注意：不允许旋转信封。
 * 
 * 示例 1：
 *  输入：envelopes = [[5,4],[6,4],[6,7],[2,3]]
 *  输出：3
 *  解释：最多信封的个数为 3, 组合为: [2,3] => [5,4] => [6,7]。
 * 示例 2：
 *  输入：envelopes = [[1,1],[1,1],[1,1]]
 *  输出：1
 * 
 * 提示：
 *  (1)1 <= envelopes.length <= 5000
 *  (2)envelopes[i].length == 2
 *  (3)1 <= wi, hi <= 10^4
 */
#include <vector>
#include <algorithm>
using namespace std;

/**
 * 先固定宽度, 对其进行排序, 然后就可以转化为
 * Leetcode 300. 最长递增子序列
 * 同样有两种方法: dp 和 基于二分查找的dp
 */
 
/* dp[i]: 以信封i结尾的最长递增子序列 */
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        if (n < 2) return n;
        /**
         * 固定宽度, 从小到大排序
         * 为了避免像[[1,1],[1,2],[1,3],[1,4]]这样的case错误地输出4
         * 高度作为第二优先级排序, 相同宽度下, 高度高的排前面
         * 这样相同高度的信封, 后者就不会错误地将前者装进去
         */
        auto cmp = [](const vector<int>& e1, const vector<int>& e2) -> bool {
            return e1[0] < e2[0] || (e1[0] == e2[0] && e1[1] > e2[1]);
        };
        sort(envelopes.begin(), envelopes.end(), cmp);
        int ans = 0;
        vector<int> dp(n, 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (envelopes[i][1] > envelopes[j][1]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};