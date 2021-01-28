/**
 * Leetcode 1034. 边框着色
 * 
 * 给出一个二维整数网格 grid，网格中的每个值表示该位置处的网格块的颜色。
 * 只有当两个网格块的颜色相同，而且在四个方向中任意一个方向上相邻时，它们属于同一连通分量。
 * 连通分量的边界是指连通分量中的所有与不在分量中的正方形相邻（四个方向上）的所有正方形，
 * 或者在网格的边界上（第一行/列或最后一行/列）的所有正方形。
 * 
 * 给出位于 (r0, c0) 的网格块和颜色 color，
 * 使用指定颜色 color 为所给网格块的连通分量的边界进行着色，并返回最终的网格 grid 。
 * 
 * 示例 1：
 *  输入：grid = [[1,1],[1,2]], r0 = 0, c0 = 0, color = 3
 *  输出：[[3, 3], [3, 2]]
 * 示例 2：
 *  输入：grid = [[1,2,2],[2,3,2]], r0 = 0, c0 = 1, color = 3
 *  输出：[[1, 3, 3], [2, 3, 3]]
 * 示例 3：
 *  输入：grid = [[1,1,1],[1,1,1],[1,1,1]], r0 = 1, c0 = 1, color = 2
 *  输出：[[2, 2, 2], [2, 1, 2], [2, 2, 2]]
 * 
 * 提示：
 *  (1)1 <= grid.length <= 50
 *  (2)1 <= grid[0].length <= 50
 *  (3)1 <= grid[i][j] <= 1000
 *  (4)0 <= r0 < grid.length
 *  (5)0 <= c0 < grid[0].length
 *  (6)1 <= color <= 1000
 */
#include <vector>
using std::vector;

/* bfs方法参考bfs文件夹 */

/* 判断是否为边界:
 * (1)是否处于网格边界?
 * (2)相邻的四个格子是否有颜色跟grid[r0][c0]不一样的?
 * 任意满足一个即为边界
 */

#define VALID(x, y) (x >= 0 && y >= 0 && x < row && y < col)
class Solution {
public:
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int r0, int c0, int color) {
        row = grid.size(), col = grid[0].size();
        vis.resize(row, vector<int>(col, 0));
        vis[r0][c0] = 1;
        ans = grid;
        dfs(r0, c0, grid, color);
        return ans;
    }

private:
    int row, col;
    vector<vector<int>> vis;
    vector<vector<int>> ans;
    int direction[4][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}};
    void dfs(int x, int y, vector<vector<int>>& grid, int color) {
        int c = grid[x][y];
        bool flag = false; /* 判断是否为边界的flag */
        for (auto& d : direction) {
            int i = x + d[0], j = y + d[1];
            if (VALID(i, j)) {
                if (grid[i][j] != c) {
                    /* 相邻格子颜色不同 */
                    flag = true;
                    continue;
                }
                if (vis[i][j] == 0) {
                    /* 这里要用vis数组, 不能就地更改grid表示遍历过
                     * 假如就地改, 设当前格子为(x, y), 下一个递归的格子为(i, j)
                     * 下一次地递归中, (i, j)会看到(x, y)跟自己颜色不一样
                     * (i, j)可能就会错误地认为自己是边界
                     */
                    vis[i][j] = 1;
                    dfs(i, j, grid, color);
                }
            } else {
                /* 处于网格边缘 */
                flag = true;
            }
        }
        ans[x][y] = flag ? color : grid[x][y];
    }
};