/**
 * Leetcode 877.石子游戏
 * 亚历克斯和李用几堆石子在做游戏。偶数堆石子排成一行，每堆都有正整数颗石子 piles[i] 。
 * 游戏以谁手中的石子最多来决出胜负。石子的总数是奇数，所以没有平局。
 * 亚历克斯和李轮流进行，亚历克斯先开始。 每回合，玩家从行的开始或结束处取走整堆石头。
 * 这种情况一直持续到没有更多的石子堆为止，此时手中石子最多的玩家获胜。
 * 假设亚历克斯和李都发挥出最佳水平，当亚历克斯赢得比赛时返回 true ，当李赢得比赛时返回 false 。
 *
 * 示例：
 *  输入：[5,3,4,5]
 *  输出：true
 *  解释：
 *   亚历克斯先开始，只能拿前 5 颗或后 5 颗石子 。
 *   假设他取了前 5 颗，这一行就变成了 [3,4,5] 。
 *   如果李拿走前 3 颗，那么剩下的是 [4,5]，亚历克斯拿走后 5 颗赢得 10 分。
 *   如果李拿走后 5 颗，那么剩下的是 [3,4]，亚历克斯拿走后 4 颗赢得 9 分。
 *   这表明，取前 5 颗石子对亚历克斯来说是一个胜利的举动，所以我们返回 true 。
 *
 * 提示：
 *  (1)2 <= piles.length <= 500
 *  (2)piles.length 是偶数。
 *  (3)1 <= piles[i] <= 500
 *  (4)sum(piles) 是奇数。
 */
#include <vector>
using std::vector;
using std::max;

/* dfs方法参考dfs文件夹
 * 数学方法参考math文件夹 */

/**
 * dp[i][j]: [i, j]区间先手选, 最多能赢对手多少个石子
 * 例如: [5, 4], dp[0][1] = 5 - 4 = 1
 */
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>> dp(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            dp[i][i] = piles[i];
        for (int i = n-2; i >= 0; i--) {
            for (int j = i+1; j < n; j++) {
                /**
                 * 首先Alex在[i+1, j]区间先手选最多能赢Lee的石子数为dp[i+1][j]
                 * 
                 * 接着倒退回来, 假设Alex在[i, j]区间先手选了piles[i]
                 * 那么Alex在区间[i+1, j]的最优策略就变成了Lee的最优策略
                 * 因此Alex在区间[i, j]先手选了piles[i], 最多能赢Lee的石子数为
                 *  piles[i] - dp[i+1][j]
                 *  
                 * Alex先手选piles[j]也同理
                 */
                dp[i][j] = max(piles[i] - dp[i+1][j], piles[j] - dp[i][j-1]);
            }
        }
        return dp[0][n-1] > 0;
    }
};