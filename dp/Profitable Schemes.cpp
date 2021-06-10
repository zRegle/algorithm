#include <vector>
using std::vector;

#define MOD ((int)1e9 + 7)

/**
 * 将任务看成"物品", 将人力成本看成"重量", 利润看成"价值", 就转化为背包问题
 * 但是比较特殊的是, 这里要求的是"不少于", 而不是一般背包的"不超过"
 * 设dp[i][j][k] = 考虑前i件物品, 使用j人, 所得利润至少为k的方案数
 */
class Solution {
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        int m = group.size();
        vector<vector<vector<int>>> dp(m+1, vector<vector<int>>(n+1, vector<int>(minProfit+1)));
        dp[0][0][0] = 1;
        for (int i = 1; i <= m; i++) {
            int need = group[i-1], gain = profit[i-1];
            for (int j = 0; j <= n; j++) {
                for (int k = 0; k <= minProfit; k++) {
                    /**
                     * 对于第i个任务, 我们选择不做, 显然此时
                     * dp[i][j][k] = dp[i-1][j][k]
                     */
                    dp[i][j][k] = dp[i-1][j][k];
                    if (j >= need) {
                        /**
                         * 对于第i个任务, 我们选择完成, 那么方案数就增加了
                         * dp[i][j][k] += dp[i-1][j-need][k-gain]
                         * 注意k-gain可能为负数, 等价于
                         *  前i-1个任务, 用了j-need个人, 利润为0
                         */
                        if (k >= gain)
                            dp[i][j][k] += dp[i-1][j-need][k-gain];
                        else
                            dp[i][j][k] += dp[i-1][j-need][0];
                    }
                    dp[i][j][k] %= MOD;
                }
            }
        }
        int ans = 0;
        for (int j = 0; j <= n; j++) {
            ans = (ans + dp[m][j][minProfit]) % MOD;
        }
        return ans;
    }

private:
    /* 空间优化方案 */
    int optimize(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        int m = group.size();
        vector<vector<int>> dp(n+1, vector<int>(minProfit+1));
        dp[0][0] = 1;
        for (int i = 1; i <= m; i++) {
            int need = group[i-1], gain = profit[i-1];
            for (int j = n; j >= 0; j--) {
                for (int k = minProfit; k >= 0; k--) {
                    if (j >= need) {
                        if (k >= gain)
                            dp[j][k] += dp[j-need][k-gain];
                        else
                            dp[j][k] += dp[j-need][0];
                    }
                    dp[j][k] %= MOD;
                }
            }
        }
        int ans = 0;
        for (int j = 0; j <= n; j++)
            ans = (ans + dp[j][minProfit]) % MOD;
        return ans;
    }
};