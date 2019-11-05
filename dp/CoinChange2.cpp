/* Leetcode 518.零钱兑换
 * 给定不同面额的硬币和一个总金额。写出函数来计算可以凑成总金额的硬币组合数。假设每一种面额的硬币有无限个。
 */
#include <vector>
using namespace std;

//space complexity: O(mn)
//dp[i][j]表示只用前i种硬币凑出金额j的方法种数
class Solution {
public:
    int change(vector<int>& coins, int amount) {
        if (coins.empty()) return 0;
        vector<vector<int>> dp(coins.size()+1, vector<int>(amount+1, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= coins.size(); i++) {
            dp[i][0] = 1;
            for (int j = 1; j <= amount; j++)
                dp[i][j] = dp[i-1][j] + (j > coins[i-1] ? dp[i][j-coins[i-1]] : 0);
        }
        return dp[coins.size()][amount];
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