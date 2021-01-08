/**
 * Leetcode 778. 水位上升的泳池中游泳
 * 在一个 N x N 的坐标方格 grid 中，每一个方格的值 grid[i][j] 表示在位置 (i,j) 的平台高度。
 * 现在开始下雨了。当时间为 t 时，此时雨水导致水池中任意位置的水位为 t 。
 * 
 * 你可以从一个平台游向四周相邻的任意一个平台，但是前提是此时水位必须同时淹没这两个平台。
 * 假定你可以瞬间移动无限距离，也就是默认在方格内部游动是不耗时的。
 * 当然，在你游泳的时候你必须待在坐标方格里面。
 * 
 * 你从坐标方格的左上平台 (0，0) 出发。最少耗时多久你才能到达坐标方格的右下平台 (N-1, N-1)？
 * 
 * 示例:
 *  输入:
 *   (0)  (1)  (2)  (3)   (4)
 *   24   23   22   21    (5)
 *   (12) (13) (14) (15) (16)
 *   (11) 17   18   19    20
 *   (10) (9)  (8)  (7)   (6)
 *  输出: 16
 *  解释: 最终的路线用'()'进行了标记。我们必须等到时间为 16，
 *        此时才能保证平台 (0, 0) 和 (4, 4) 是连通的
 */
#include <vector>
#include <climits>
#include <queue>
using namespace std;

/**
 * 我的思路:
 * 从左上角到右下角有许多条路径, 每条路径中许多个格子, 取这些格子的最大值, 即为走这条路径要需要等待的时间
 * 本质上就是求所有路径中花费时间最少的那条路径(最小化最大值)
 * 可以采用dijstra算法, 将每个格子看成一个节点, 求(0, 0)到(n-1, n-1)的最短距离
 *
 * 关键点:
 * 现假设(i, j)与(k, l)在网格上相邻, 求经过(i, j), 从(0, 0) -> (k, l)所花费的时间
 * 如果我们到达(i, j)时, 水位已经淹没了(k, l), 那我们可以直接到达(k, l)
 * 反之, 我们必须等到水位淹没(k, l)
 * 设到达(i, j)要花费的时间为t, 则我们要在(i, j)等待的时间为grid(k, l) - t
 * 也就是说, 我们从(0, 0) -> (k, l)要花的时间为t + (grid(k, l) - t) = grid(k, l)
 * PS: 此时grid(k, l) - t就是(i, j) -> (k, l)这条边的权重
 *
 * 综上, 设(0, 0) -> (i, j)要花费的时间为t, 那么我们经过(i, j)从(0, 0) -> (k, l)要花费的时间t'为:
 * t' = grid(k, l) > t ? gird(k, l) : t
 * 我们可以通过四个相邻的格子到达(k, l), 各自求出从这四条路径到达(k, l)的时间
 * 取最小值, 即为从(0, 0) -> (k, l)最少需要花费的时间
 */
class Solution {
public:
    int direction[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        vector<vector<int>> vis(n, vector<int>(n, 0));
        /* 到达(0, 0)需要花费的时间就是grid(0, 0)的高度 */
        dist[0][0] = grid[0][0];
        /* 构建最小堆 */
        auto cmp = [&dist](const pair<int, int>& p1, const pair<int, int>& p2) -> bool {
            return dist[p1.first][p1.second] > dist[p2.first][p2.second];
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);
        q.push({0, 0});
        while (!q.empty()) {
            auto p = q.top(); q.pop();
            int x = p.first, y = p.second;
            if (vis[x][y] == 1) continue;
            vis[x][y] = 1;
            for (auto& d : direction) {
                int i = x + d[0], j = y + d[1];
                if (i >= 0 && j >= 0 && i < n && j < n) {
                    /* 到达(i, j)花费的时间 */
                    int ndist = grid[i][j] > dist[x][y] ? grid[i][j] : dist[x][y];
                    if (dist[i][j] > ndist) {
                        dist[i][j] = ndist;
                        q.push({i, j});
                    }
                }
            }
        }
        return dist[n-1][n-1];
    }
};

/**
 * Leetcode官解
 * 保存下一步能够到达的平台, 每次从中取出高度最小的平台
 * 以这种方式到达终点时, 路径中遇到的最高平台就是答案
 */
class Solution2 {
public:
    int direction[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        auto cmp = [&grid, n](int pos1, int pos2) -> bool {
            int i = pos1 / n, j = pos1 % n;
            int k = pos2 / n, l = pos2 % n;
            return grid[i][j] > grid[k][l];
        };
        priority_queue<int, vector<int>, decltype(cmp)> q(cmp);
        vector<int> vis(n * n, 0);
        q.push(0); vis[0] = 1;
        int time = 0; /* 当前时刻 */
        while (!q.empty()) {
            int pos = q.top(); q.pop();
            int x = pos / n, y = pos % n;
            time = max(time, grid[x][y]);
            if (x == n - 1 && y == n - 1) return time;
            for (auto& d : direction) {
                int i = x + d[0], j = y + d[1];
                if (i >= 0 && j >= 0 && i < n && j < n) {
                    int npos = i * n + j;
                    if (vis[npos] == 0) {
                        vis[npos] = 1;
                        q.push(npos);
                    }
                }
            }
        }
        return -1;
    }
};