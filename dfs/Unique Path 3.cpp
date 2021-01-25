/**
 * Leetcode 980. 不同路径 III
 * 在二维网格 grid 上，有 4 种类型的方格：
 *  1 表示起始方格。且只有一个起始方格。
 *  2 表示结束方格，且只有一个结束方格。
 *  0 表示我们可以走过的空方格。
 *  -1 表示我们无法跨越的障碍。
 * 返回在四个方向（上、下、左、右）上行走时，从起始方格到结束方格的不同路径的数目。
 * <<每一个无障碍方格都要通过一次>>，但是一条路径中不能重复通过同一个方格。
 *
 * 示例 1：
 *  输入：[[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
 *  输出：2
 *  解释：我们有以下两条路径：
 *   1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
 *   2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)
 * 示例 2：
 *  输入：[[1,0,0,0],[0,0,0,0],[0,0,0,2]]
 *  输出：4
 *  解释：我们有以下四条路径：
 *   1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
 *   2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
 *   3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
 *   4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)
 *
 * 提示：1 <= grid.length * grid[0].length <= 20
 */
#include <vector>
using std::vector;

/* 位操作 */
#define GET(x, y) (x & (1 << y)) /* 查看bit */
#define SET(x, y) x |= (1 << y) /* 将bit置1 */
#define CLEAR(x, y) x &= ~(1 << y) /* 将bit置0 */

#define VALID(x, y) (x >= 0 && y >= 0 && x < row && y < col)
#define ID(x, y) (x * col + y) /* 二维网格压缩成一维 */
class Solution {
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        row = grid.size(), col = grid[0].size();
        int x, y;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (grid[i][j] == 1) {
                    /* 确定起点 */
                    x = i;
                    y = j;
                }
                if (grid[i][j] == 0)
                    /* 统计无障碍方格数目 */
                    cnt++;
            }
        }
        /* 因为方格数量不超过20个, 因此可以用一个32 bit的int来表示visited数组 */
        int visited = 0;
        SET(visited, ID(x, y));
        dfs(x, y, grid, visited, 0);
        return ans;
    }

private:
    int row, col, cnt = 0, ans = 0;
    int direction[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    /**
     * dfs统计路径数目
     * @param x 当前横坐标
     * @param y 当前纵坐标
     * @param grid 网格
     * @param visited visited数组, 第i个bit表示id为i的方格是否已经在当前路径中, 相当于当前路径
     * @param passed 到达(x, y)之前, 走过了多少个无障碍方格
     */
    void dfs(int x, int y, vector<vector<int>>& grid, int visited, int passed) {
        if (grid[x][y] == 0)
            /* 无障碍方格, 计数加一 */
            passed++;
        if (grid[x][y] == 2) {
            /* 走到终点, 需要判断是否走完了所有无障碍方格 */
            if (passed == cnt)
                /* 走过了所有无障碍方格 */
                ans++;
            return;
        }
        for (auto& d : direction) {
            int i = x + d[0], j = y + d[1];
            if (VALID(i, j) && grid[i][j] != -1) {
                if (!GET(visited, ID(i, j))) {
                    SET(visited, ID(i, j));
                    dfs(i, j, grid, visited, passed);
                    CLEAR(visited, ID(i, j)); /* 回溯 */
                }
            }
        }
    }
};