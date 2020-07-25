/* Leetcode 174.地下城游戏
 * 一些恶魔抓住了公主（P）并将她关在了地下城的右下角。地下城是由 M x N 个房间组成的二维网格。
 * 我们英勇的骑士（K）最初被安置在左上角的房间里，他必须穿过地下城并通过对抗恶魔来拯救公主。
 * 骑士的初始健康点数为一个正整数。如果他的健康点数在某一时刻降至 0 或以下，他会立即死亡。
 * 有些房间由恶魔守卫，因此骑士在进入这些房间时会失去健康点数（若房间里的值为负整数，则表示骑士将损失健康点数）；
 * 其他房间要么是空的（房间里的值为 0 ），要么包含增加骑士健康点数的魔法球（若房间里的值为正整数，则表示骑士将增加健康点数）。
 * 为了尽快到达公主，骑士决定每次只向右或向下移动一步。
 *
 * 编写一个函数来计算确保骑士能够拯救到公主所需的最低初始健康点数。
 *
 * 例如，考虑到如下布局的地下城，如果骑士遵循最佳路径 右->右->下->下，则骑士的初始健康点数至少为 7。
 * -2(K) -3  3
 * -5    -10 1
 * 10    30  -5(P)
 */
#include <iostream>
#include <vector>
using  namespace  std;

/* 明显要用动态规划, 但是如果我们是从左上角到右下角遍历
 * 我们要记录(1)能够到达某个格子时最小需要多少初始HP 以及 (2)这个最小初始生命值到达该格子时所剩余的HP
 * 我们想要(1)尽可能地小, 同时另(2)尽可能地大
 * 但是, 我们无法选择(1)还是(2)作为状态转移方程的值,
 * 如果选择(1)作为状态转移方程的值, 考虑下列情况:
 * |     | 7/6 |
 * | 6/3 | -4 |
 * 6/3表示到达这个格子需要的最小初始生命值为6, 到达该格子后剩余生命值为3, 7/6同理
 * -4表示进入这个房间要消耗4生命值
 * 那么我们从左边走到这个房间, 需要的最小初始HP就变成6+(4-3)+1=8了, 更新后该房间的值为8/1
 * 如果选择从上面走下来, 那么我们走到这个房间需要的最小初始HP还是7, 更新后该房间的值为7/2, 我们应该选择这条路径
 * 可以看到如果选择(1)作为状态转移方程的值, 在这种状况下就得到了错误的路径
 *
 * 如果选择(2)呢? 考虑下面这种情况
 * |     | 7/6 |
 * | 2/3 | -4 |
 * 显然, 走到该房间时的所需要的最小初始HP是2+(4-3)+1=4
 * 如果选择(2)作为状态转移方程的值, 在这种状况下就得到了错误的答案为7/2
 *
 * 两个选择都有道理, 所以我们无法确定
 * 归根结底, 如果我们是从左上角到右下角遍历
 * 我们无法确定我当前的选择的最小HP和剩余的HP能否支持我进入下一个房间
 * 因此, 我们不妨假设总是能够进入下一个房间, 这就需要我们从右下角向左上角遍历, 就能确保我们总是能够进入下一个房间
 * 不防设dp[i][j]为进入第(i, j)个房间前, 所需要的最小HP
 * 状态转移方程就比较简单了
 */
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int row = dungeon.size();
        if (row <= 0) return 1;
        int col = dungeon[0].size();
        vector<vector<int>> dp(row, vector<int>(col, 0));
        for (int i = row-1; i >= 0; i--) {
            for (int j = col - 1; j >= 0; j--) {
                if (i == row-1 && j == col-1)
                    /* 公主的房间, 只需要判断进入这个房间是否需要消耗HP
                     * 如果是, 则dp[i][j] = 需要消耗HP + 1
                     * 如果不是, dp[i][j] = 1
                     */
                    dp[i][j] = dungeon[i][j] >= 0 ? 1 : 1-dungeon[i][j];
                else if (i == row-1)
                    /* 最后一行 */
                    dp[i][j] = dungeon[i][j] >= dp[i][j+1] ? 1 : dp[i][j+1] - dungeon[i][j];
                else if (j == col-1)
                    /* 最后一列 */
                    dp[i][j] = dungeon[i][j] >= dp[i+1][j] ? 1 : dp[i+1][j] - dungeon[i][j];
                else {
                    /* 判断进入房间A能够获得的HP(可能为负数)是否大于等于进入房间B所需要的最小HP
                     * 如果是, 那么进入房间A前只要还活着就行, 即最小需要1HP
                     * 如果不是, 那么进入房间A前至少需要: 进入房间B所需要的最小HP - 进入房间A能够获得的HP
                     */
                    int down = dungeon[i][j] >= dp[i+1][j] ? 1 : dp[i+1][j] - dungeon[i][j];
                    int right = dungeon[i][j] >= dp[i][j+1] ? 1 : dp[i][j+1] - dungeon[i][j];
                    /* 进入房间B有两种方法, 取最小值 */
                    dp[i][j] = min(down, right);
                }
            }
        }
        return dp[0][0];
    }

    /* 优化空间复杂度后的做法, 为O(N)
     * dp数组记录前一行到达某个格子前最少需要多少HP
     */
    int calculateMinHP(vector<vector<int>>& dungeon) {
        int row = dungeon.size();
        if (row == 0) return 1;
        int col = dungeon[0].size();
        vector<int> dp(col, 0);
        for (int i = row-1; i >= 0; i--) {
            for (int j = col-1; j >= 0; j--) {
                if (i == row-1 && j == col-1)
                    dp[j] = dungeon[i][j] >= 0 ? 1 : 1-dungeon[i][j];
                else if (i == row-1)
                    dp[j] = dungeon[i][j] >= dp[j+1] ? 1 : dp[j+1]-dungeon[i][j];
                else if (j == col-1)
                    dp[j] = dungeon[i][j] >= dp[j] ? 1 : dp[j]-dungeon[i][j];
                else {
                    int below = dungeon[i][j] >= dp[j] ? 1 : dp[j]-dungeon[i][j];
                    int right = dungeon[i][j] >= dp[j+1] ? 1 : dp[j+1]-dungeon[i][j];
                    dp[j] = min(below, right);
                }
            }
        }
        return dp[0];
    }
};