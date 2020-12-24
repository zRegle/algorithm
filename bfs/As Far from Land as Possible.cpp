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
 */
#include <vector>
#include <queue>
using namespace std;

/**
 * 以陆地bfs, 多源bfs, 与leetcode 847相似
 * 时间复杂度O(n^2), 一个格子只遍历一次
 */
class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int n = grid.size();
        queue<pair<int, int>> q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    q.push({i, j});
                }
            }
        }
        int dist = 0;
        int direction[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto p = q.front(); q.pop();
                int x = p.first, y = p.second;
                for (auto d : direction) {
                    int i = x + d[0], j = y + d[1];
                    if (i < 0 || j < 0 || i == n || j == n || grid[i][j] == 1) continue;
                    grid[i][j] = 1; /* 直接修改grid, 故不需要visited数组 */
                    q.push({i, j});
                }
            }
            /* 若队列已空, 代表无法走到下一个格子或者已经遍历完, 步数不能再加一 */
            if (!q.empty()) dist++;
        }
        return dist == 0 ? -1 : dist;
    }
};

/**
 * 每个海洋都bfs, TLE了
 * 因为有大量的海洋被重复bfs, 尝试利用dp的思想记忆化搜索, 但还是TLE了
 * 时间复杂度: 一个海洋bfs是O(n^2), 最坏情况是O(n^4)
 */
class MySolution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        n = grid.size();
        int ans = -1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) 
                    ans = max(ans, bfs(i, j, grid));
            }
        }
        return ans;
    }
private:
    int n;
    int direction[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int bfs(int i, int j, vector<vector<int>>& grid) {
        queue<int> q;
        int pos = i * n + j;
        vector<int> mark(n * n, 0);
        q.push(pos); mark[pos] = 1;
        int dist = 0;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                int p = q.front(); q.pop();
                int x = p / n, y = p % n;
                if (grid[x][y] == 1) return dist;             
                for (auto d : direction) {
                    i = x + d[0], j = y + d[1];
                    if (i < 0 || j < 0 || i == n || j == n) continue;
                    int npos = i * n + j;
                    if (mark[npos] == 0) {
                        mark[npos] = 1;
                        q.push(npos);
                    }
                }
            }
            dist++;
        }
        return -1;
    }
};