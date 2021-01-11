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
using namespace std;

/* 本质上判断起点终点是否相连, 等价于是否处在同一个连通分量
 * 用dfs, bfs, 并查集都可以
 */

/** 
 * 如何判断相邻两个格子的街道是否相连?
 * 现将四个方向进行编号:
 *     0
 *     |
 * 3 -- -- 1
 *     |
 *     2
 * 每一种单元格都可以用一个长度为 4 的二进制数表示, 二进制数的第 i 位为 1 等价于该单元格在第 i 个方向存在街道
 * 这样以来，每一种单元格对应的二进制数中都恰好有 2 个 1。
 * 因此, 只有在这些情况下, 两个相邻的单元格才能相连:
 *  (1)如果某一个单元格有第 0 个方向，那么它上方的单元格必须有第 2 个方向；
 *  (2)如果某一个单元格有第 1 个方向，那么它右侧的单元格必须有第 3 个方向；
 *  (3)如果某一个单元格有第 2 个方向，那么它下方的单元格必须有第 0 个方向；
 *  (4)如果某一个单元格有第 3 个方向，那么它左侧的单元格必须有第 1 个方向。
 * 结论: 某一个单元格有第 i 个方向，那么它在第 i 个方向相邻的单元格必须有第 (i + 2) % 4 个方向
 */

/* 四个方向的编号, 0 -> up, 1 -> right, 2 -> down, 3 -> left */
int direction[4][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}};
/* 6种街道对应的二进制表示 */
int patterns[7] = {0 /* dummy element */,
                   0b1010, 0b0101, 0b1100, 0b0110, 0b1001, 0b0011};
/* self-explained的宏 */                
#define HAS_DIRECTION(x, i) x & (1 << i)
#define IS_IN(x, y) x >= 0 && y >= 0 && x < row && y < col

class Solution {
/* 并查集判断起点和终点是否在同一个连通分量 */
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int row = grid.size(), col = grid[0].size();
        father.resize(row * col);
        rank.resize(row * col);
        for (int i = 0; i < row * col - 1; i++) {
            father[i] = i;
            rank[i] = 1;
        }
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                /* 当前街道的二进制表示 */
                int p_cur = patterns[grid[i][j]];
                for (int d = 0; d < 4; d++) {
                    /* 判断当前街道是否有对应的前进方向 */
                    if (HAS_DIRECTION(p_cur, d)) {
                        int x = i + direction[d][0];
                        int y = j + direction[d][1];
                        if (IS_IN(x, y)) {
                            int dir = (d + 2) % 4;
                            /* 下一个街道的二进制表示 */
                            int p_next = patterns[grid[x][y]];
                            /* 判断前进方向的街道是否有对应方向相连 */
                            if (HAS_DIRECTION(p_next, dir)) {
                                int pos_cur = i * col + j;
                                int pos_next = x * col + y;
                                merge(pos_cur, pos_next);
                            }
                        }
                    }
                }
            }
        }
        return find(0) == find(row * col - 1);
    }

private:
    vector<int> father;
    vector<int> rank;

    int find(int x) {
        return x == father[x] ? x : (father[x] = find(father[x]));
    }

    void merge(int i, int j) {
        int x = find(i), y = find(j);
        if (x == y) return;
        if (rank[x] >= rank[y])
            father[y] = x;
        else
            father[x] = y;
        if (rank[x] == rank[y])
            rank[x]++;
    }
};