/**
 * 1293. 网格中的最短路径
 * 给你一个 m * n 的网格，其中每个单元格不是 0（空）就是 1（障碍物）。
 * 每一步，您都可以在空白单元格中上、下、左、右移动。
 * 如果您 最多 可以消除 k 个障碍物，请找出从左上角 (0, 0) 到右下角 (m-1, n-1) 的最短路径，
 * 并返回通过该路径所需的步数。如果找不到这样的路径，则返回 -1。
 * 示例：
 *  输入： 
 *   grid = 
 *    [[0,0,0],
 *     [1,1,0],
 *     [0,0,0],
 *     [0,1,1],
 *     [0,0,0]], 
 *   k = 1
 *  输出：6
 *  解释：不消除任何障碍的最短路径是 10。
 *  消除位置 (3,2) 处的障碍后，最短路径是 6 。
 *  该路径是 (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2).
 */
#include <vector>
#include <queue>
using namespace std;

/**
 * 求最短路径明显可以用bfs, 需要注意以下两点:
 * 1.不能类似dp那样只往下或者往左走, 因为可能有障碍但是可以绕过障碍
 * 2.第一点里, 绕过障碍明显增加了路程, 但是可以为我们省下一次消除障碍的次数, 用于消除其他障碍
 */
class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int row = grid.size();
        int col = grid[0].size();
        /* bfs用的队列, 第一个元素是i * col + j, 
         * 第二个元素是走到(i, j)还剩多少次消除障碍的机会 
         */
        queue<pair<int, int>> q;
        /* 矩阵标记数组, mark[i * col + j]记录了
         * 上一次走到(i, j)还剩多少次消除障碍的机会
         * -1表示还没访问过(i, j)
         */
        vector<int> mark(row * col, -1);
        int direct[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        q.push({0, k}); mark[0] = k;
        /* bfs深度 */
        int dist = 0;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto p = q.front(); q.pop();
                int x = p.first / col, y = p.first % col;
                if (x == row - 1 && y == col - 1) return dist;
                for (auto d : direct) {
                    int i = x + d[0], j = y + d[1];
                    if (i >= 0 && j >= 0 && i < row && j < col) {
                        int pos = i * col + j, cnt = p.second;
                        if (grid[i][j] == 1) {
                            /* 判断是否可以消除当前障碍 */
                            if (cnt == 0) continue;
                            cnt--;
                        }
                        /* 上一次走到(i, j)剩余消除障碍的机会比这次还多
                         * 而且这次花费的距离更长, 没必要继续bfs
                         */
                        if (mark[pos] >= cnt) continue;
                        /* 之前没访问过(i, j)或者这次剩余消除障碍的机会更多, 继续bfs */
                        q.push({pos, cnt}); mark[pos] = cnt;
                    }
                }
            }
            dist++;
        }
        return -1;
    }
};