/**
 * Leetcode 1162. 地图分析
 * 你现在手里有一份大小为 N x N 的 网格 grid，上面的每个 单元格 都用 0 和 1 标记好了。
 * 其中 0 代表海洋，1 代表陆地，请你找出一个海洋单元格，
 * 这个海洋单元格到离它最近的陆地单元格的距离是最大的。
 * 
 * 我们这里说的距离是「曼哈顿距离」（ Manhattan Distance）：
 * (x0, y0) 和 (x1, y1) 这两个单元格之间的距离是 |x0 - x1| + |y0 - y1| 。
 * 
 * 如果网格上只有陆地或者海洋，请返回 -1。
 * 
 * 1 <= grid.length == grid[0].length <= 100
 */
#include <vector>
#include <queue>
using namespace std;



/**
 * 一个海洋离它最近的陆地区域到它的路径要么从上方或者左方来，要么从右方或者下方来
 * 故可以做两次dp, 一次从左上角到右下角, 一次从右下角到左上角
 * dp[i][j] = 离(i, j)最近的陆地距离
 * 
 * 从左上到右下的转移方程:
 * dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + 1
 * 
 * 从右下到左上的转移方程:
 * dp[i][j] = min(dp[i+1][j], dp[i][j+1]) + 1
 */

/* 因为grid <= 100 * 100, 所以结果最大不会超过200
 * 设置成1024表示INF
 */
#define INF 1024
class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dp(n, vector<int>(n, INF));
        int ans = -1;
        /* 左上到右下 */
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    dp[i][j] = 0;
                    continue;
                }
                if (i > 0) 
                    /* 1.dp[i-1][j]可能是INF, 因此需要与dp[i][j]进行min
                     * 2.如果INF设置成INT_MAX, +1就会溢出, 所以设置INF为1024 
                     */
                    dp[i][j] = min(dp[i][j], dp[i-1][j] + 1);
                if (j > 0)
                    dp[i][j] = min(dp[i][j], dp[i][j-1] + 1);
            }
        }
        /* 右下到左上 */
        for (int i = n-1; i >= 0; i--) {
            for (int j = n-1; j >= 0; j--) {
                if (grid[i][j] == 1) continue;
                if (i < n-1)
                    /* 第二阶段需要与第一阶段进行比较, 所以和dp[i][j]进行min */
                    dp[i][j] = min(dp[i][j], dp[i+1][j] + 1);
                if (j < n-1) 
                    dp[i][j] = min(dp[i][j], dp[i][j+1] + 1);
                ans = max(ans, dp[i][j]);
            }
        }
        return ans == INF ? -1 : ans;
    }
};