/**
 * Leetcode 1391.检查网格中是否存在有效路径
 * 给你一个 m x n 的网格 grid。网格里的每个单元都代表一条街道。grid[i][j] 的街道可以是：
 *  1 表示连接左单元格和右单元格的街道。
 *  2 表示连接上单元格和下单元格的街道。
 *  3 表示连接左单元格和下单元格的街道。
 *  4 表示连接右单元格和下单元格的街道。
 *  5 表示连接左单元格和上单元格的街道。
 *  6 表示连接右单元格和上单元格的街道。
 *  图片link: https://leetcode-cn.com/problems/check-if-there-is-a-valid-path-in-a-grid/
 * 你最开始从左上角的单元格 (0,0) 开始出发，网格中的「有效路径」是指从左上方的单元格 (0,0) 开始,
 * 一直到右下方的 (m-1,n-1) 结束的路径。该路径必须只沿着街道走。
 * 如果网格中存在有效的路径，则返回 true，否则返回 false 。
 * 
 * 示例:
 *  输入: grid = [[1,1,2]]
 *  输入: false
 * 注意, 街道相连要求从当前街道有前进方向到达下一个街道, 下一个街道也有前进方向可以返回到当前街道
 * 输入的街道对应的图形如下:
 *  -- -- |
 * [0, 1]有向右的方向, 但是[0, 2]没有向左的方向, 因此[0, 1]与[0, 2]不想连
 */
#include <vector>
#include <stack>
using namespace std;

/* 本质上判断起点终点是否相连, 等价于是否处在同一个连通分量
 * 用dfs, bfs, 并查集都可以
 * 
 * 并查集做法请查看并查集文件夹, 其中有很巧妙判断街道是否相连的做法
 */

#define IS_IN(x, y) x >= 0 && y >= 0 && x < row && y < col
class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int row = grid.size(), col = grid[0].size();
        vector<int> vis(row * col, 0);
        stack<int> stk;
        stk.push(0); vis[0] = 1;
        /* 用栈模拟dfs */
        while (!stk.empty()) {
            int pos = stk.top(); stk.pop();
            int x = pos / col, y = pos % col;
            if (x == row - 1 && y == col - 1) return true;
            for (auto& d : direction[grid[x][y]]) {
                int i = x + d[0], j = y + d[1];
                if (IS_IN(i, j)) {
                    /* (x, y)有前进方向可以到达(i, j), 反过来也要检查(i, j) */
                    if (isConnected(x, y, i, j, grid)) {
                        pos = i * col + j;
                        if (vis[pos] == 0) {
                            vis[pos] = 1;
                            stk.push(pos);
                        }
                    }

                }
            }
        }
        return false;
    }

private:
    /* 检查能否(k, l)的街道是否有前进方向可以到达(i, j) */
    inline bool isConnected(int i, int j, int k, int l,
                            vector<vector<int>>& grid) const {
        for (auto& d : direction[grid[k][l]]) {
            int x = k + d[0], y = l + d[1];
            if (x == i && y == j)
                return true;
        }
        return false;
    }
    /* 6种街道代表的方向数组 */
    int direction[7][2][2] = {
            {{}}, /* dummy element */
            {{0, -1}, {0, 1}},
            {{1, 0}, {-1, 0}},
            {{0, -1}, {1, 0}},
            {{0, 1}, {1, 0}},
            {{0, -1}, {-1, 0}},
            {{0, 1}, {-1, 0}}
    };
};