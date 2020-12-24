/**
 * Leetcode 1263.推箱子
 * 「推箱子」是一款风靡全球的益智小游戏，玩家需要将箱子推到仓库中的目标位置。
 * 游戏地图用大小为 n * m 的网格 grid 表示，其中每个元素可以是墙、地板或者是箱子。
 * 现在你将作为玩家参与游戏，按规则将箱子 'B' 移动到目标位置 'T' ：
 * 玩家用字符 'S' 表示，只要他在地板上，就可以在网格中向上、下、左、右四个方向移动。
 * 地板用字符 '.' 表示，意味着可以自由行走。
 * 墙用字符 '#' 表示，意味着障碍物，不能通行。 
 * 箱子仅有一个，用字符 'B' 表示。相应地，网格上有一个目标位置 'T'。
 * 玩家需要站在箱子旁边，然后沿着箱子的方向进行移动，此时箱子会被移动到相邻的地板单元格。记作一次「推动」。
 * 玩家无法越过箱子。
 * 返回将箱子推到目标位置的最小 推动 次数，如果无法做到，请返回 -1。
 * 
 * 输入：grid = [["#","#","#","#","#","#"],
 *              ["#","T","#","#","#","#"],
 *              ["#",".",".","B",".","#"],
 *              ["#",".","#","#",".","#"],
 *              ["#",".",".",".","S","#"],
 *              ["#","#","#","#","#","#"]]
 * 输出：3
 * 解释：我们只需要返回推箱子的次数。玩家移动路线为:
 * (4,4) -> (2,4) ->[推动箱子] (2,3) ->[推动箱子] (2,1) -> (3,1) ->[推动箱子] (1,1)
 */
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/**
 * 思路: 双bfs, 玩家推动箱子bfs求最短推动次数
 * 玩家在网格里移动但不推动箱子, bfs判断能否到达目标位置
 * 
 * 注意点————玩家只能"推"箱子, 不能"拉"箱子, 例如:
 * 玩家在箱子的左边, 那么玩家只能往右推箱子, 不能拉着箱子往左或者上下移动
 */
class Solution {
public:
    int minPushBox(vector<vector<char>>& grid) {
        row = grid.size();
        col = grid[0].size();
        int bx = -1, by = -1;
        int sx = -1, sy = -1;
        /* 首先确定盒子和玩家起始坐标 */
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (grid[i][j] == 'B') {
                    bx = i;
                    by = j;
                } else if (grid[i][j] == 'S') {
                    sx = i;
                    sy = j;
                }
                if (bx != -1 && sx != -1) 
                    goto out;
            }
        }
    out:
        /* bfs队列, pair.first = 盒子坐标, pair.second = 玩家坐标 */
        queue<pair<int, int>> q;
        /* 玩家bfs移动的标记数组 */
        vector<int> visited(row * col, 0);
        /* 玩家推盒子的标记数组, 例如盒子坐标为(i, j), 玩家坐标为(x, y)
         * 其对应的标记为mark[i * col + j][x * col + y]
         */
        vector<vector<int>> mark(row * col, vector<int>(row * col, 0));
        int bpos = bx * col + by, spos = sx * col + sy;
        q.push({bpos, spos});
        int cnt = 0;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto state = q.front(); q.pop();
                bx = state.first / col, by = state.first % col;
                if (grid[bx][by] == 'T') return cnt;
                /* 尝试走到盒子四个相邻的格子 */
                for (auto d : direction) {
                    int tmpx = bx + d[0], tmpy = by + d[1];
                    /* 首先检查盒子四个相邻的格子是否越界或者有障碍 */
                    if (isValid(tmpx, tmpy, grid)) {
                        int tpos = tmpx * col + tmpy;
                        sx = state.second / col, sy = state.second % col;
                        /* 接着检查从玩家当前位置能否走到目标格子 */
                        if (bfs(state.second, tpos, state.first, grid, visited)) {
                            sx = tmpx, sy = tmpy;
                            /* 盒子在玩家的哪一边, 玩家就只能往哪一边推盒子
                             * 比如盒子在玩家的左边, 玩家就只能往左边推盒子
                             */
                            int nbx = bx - d[0], nby = by - d[1];
                            /* 最后检查盒子的前进方向是否越界或者有障碍 */
                            if (isValid(nbx, nby, grid)) {
                                int nbpos = nbx * col + nby;
                                if (mark[nbpos][state.first] == 0) {
                                    mark[nbpos][state.first] = 1;
                                    q.push({nbpos, state.first});
                                }
                            }
                        }
                    }
                }
            }
            cnt++;
        }
        return -1;
    }
private:
    int row, col;
    int direction[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    /**
     * bfs判断玩家能否从起始位置走到目标位置
     * 
     * \param spos start position 玩家起始位置
     * \param tpos target position 目标位置
     * \param bpos box postition 盒子当前位置
     * \param grid 网格
     * \param visited bfs标记数组, 记录遍历过的格子
     */
    bool bfs(int spos, int tpos, int bpos, vector<vector<char>>& grid, vector<int>& visited) {
        queue<int> q;
        q.push(spos);
        visited[spos] = 1;
        bool flag = false;
        while (!q.empty()) {
            auto pos = q.front(); q.pop();
            int sx = pos / col, sy = pos % col;
            if (pos == tpos) {
                flag = true;
                break;
            }
            for (auto d : direction) {
                int nsx = sx + d[0], nsy = sy + d[1];
                if (isValid(nsx, nsy, grid)) {
                    int nspos = nsx * col + nsy;
                    if (nspos != bpos && visited[nspos] == 0) {
                        visited[nspos] = 1;
                        q.push(nspos);
                    }
                }
            }
        }
        fill(visited.begin(), visited.end(), 0);
        return flag;
    }
    inline bool isValid(int i, int j, vector<vector<char>>& grid) {
        return i >= 0 && j >= 0 && i < row && j < col && grid[i][j] != '#';
    }
};