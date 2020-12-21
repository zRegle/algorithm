/**
 * Leetcode 934. 最短的桥
 * 在给定的二维二进制数组 A 中，存在两座岛。（岛是由四面相连的 1 形成的一个最大组。）
 * 现在，我们可以将 0 变为 1，以使两座岛连接起来，变成一座岛。
 * 返回必须翻转的 0 的最小数目。（可以保证答案至少是 1。）
 *  
 * 示例 1：
 *  输入：[[0,1],
 *        [1,0]]
 *  输出：1
 * 示例 2：
 *  输入：[[0,1,0],
 *        [0,0,0],
 *        [0,0,1]]
 *  输出：2
 */
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int shortestBridge(vector<vector<int>>& A) {
        row = A.size(), col = A[0].size();
        vector<int> visited(row * col, 0);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (A[i][j] == 1) {
                    /* 首先dfs随机遍历一座岛屿, 目的是为了标记这个岛屿 */
                    dfs(i, j, A, visited);
                    goto out;
                }
            }
        }
    out:
        /* BFS拓展, 拓展到未遍历过的1即连通了 */
        int cnt = 0;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                int pos = q.front(); q.pop();
                int x = pos / col, y = pos % col;
                for (auto d : direction) {
                    int i = x + d[0], j = y + d[1];
                    int npos = -1;
                    if (i < 0 || j < 0 || i == row || j == col || 
                        (npos = i * col + j, visited[npos] == 1))
                        continue;
                    if (A[i][j] == 1) return cnt;
                    visited[npos] = 1;
                    q.push(npos);
                }
            }
            cnt++;
        }
        return -1;
    }
private:
    int row, col;
    int direction[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    queue<int> q;
    /**
     * dfs遍历岛, 标记为已访问
     * 
     * \param x 当前格子的横坐标
     * \param y 当前格子的纵坐标
     * \param A 网格
     * \param visited 标记数组
     */
    void dfs(int x, int y, vector<vector<int>>& A, vector<int>& visited) {
        int pos = -1;
        if (x < 0 || y < 0 || x == row || y == col || A[x][y] == 0 || 
            (pos = x * col + y, visited[pos] == 1))
            return;
        visited[pos] = 1;
        /* 岛屿中的每一个格子都算作一个bfs起点 */
        q.push(pos);
        for (auto d : direction) {
            int i = x + d[0], j = y + d[1];
            dfs(i, j, A, visited);
        }
    }
};