/* Leetcode 518.零钱兑换
 * 给定不同面额的硬币和一个总金额。写出函数来计算可以凑成总金额的硬币组合数。假设每一种面额的硬币有无限个。
 */
#include <vector>
using namespace std;

//space complexity: O(mn)
/**
 * 我们很容易想到, 设dp[i]表示凑出金额i的组合数
 *  dp[i] = sum{dp[i-c], c ∈ coins}
 * 这样做是错误的, 例如amount = 3, coins = {1, 2}, 有
 *  3 = 1 + 1 + 1
 *  3 = 1 + 2
 * dp[1] = 1
 * dp[2] = 2 (用两个1或者用一个2)
 * dp[3] = dp[1] + dp[2] = 3 
 * (错误, 先凑1再凑2和先凑2再凑1没本质区别, 1 + 2这种情况算了两次)
 * 
 * 应该重新定义子问题:
 * dp[i][j]表示只用前i种硬币凑出金额j的方法种数,
 * 我们只关心第i个硬币用没用, 不关心它的使用顺序
 */
class Solution {
public:
    int change(vector<int>& coins, int amount) {
        int n = coins.size();
        if (n == 0) return 0;
        vector<vector<int>> dp(n+1, vector<int>(amount+1));
        dp[0][0] = 1;
        /* 外层循环是遍历硬币, 体现了:
         * 只关心用不用这种硬币, 不关心它用的顺序和次数 */
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= amount; j++) {
                /* 第i种硬币不用, 显然
                 * dp[i][j] = dp[i-1][j] */
                dp[i][j] = dp[i-1][j];
                if (j >= coins[i-1])
                    /* 用第i种硬币
                     * 方案数增加dp[i][j-coins[i-1]] */
                    dp[i][j] += dp[i][j-coins[i-1]];
            }
        }
        return dp[n][amount];
    }
};

//space complexity: O(n)
//在上一个方法中, dp[i][j]只依赖于dp[i-1][j]和dp[i][j-coins[i-1]]
//那么我们只用一个一维数组存取上一行的结果
int change(vector<int>& coins, int amount) {
    vector<int> dp(amount+1, 0);
    dp[0] = 1;
    for (int i = 1; i <= coins.size(); i++) {
        for (int j = coins[i-1]; j <= amount; j++)
            dp[j] += dp[j-coins[i-1]];
    }
    return dp[amount];
}