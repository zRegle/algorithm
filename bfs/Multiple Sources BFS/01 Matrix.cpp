/**
 * Leetcode 542. 01 矩阵
 * 给定一个由 0 和 1 组成的矩阵，找出每个元素到最近的 0 的距离。
 * 两个相邻元素间的距离为 1 。
 * 
 * 示例：
 *  输入：
 *      [[0,0,0],
 *       [0,1,0],
 *       [1,1,1]]
 *  输出：
 *      [[0,0,0],
 *       [0,1,0],
 *       [1,2,1]]
 * 提示：
 *  (1)给定矩阵的元素个数不超过 10000。
 *  (2)给定矩阵中至少有一个元素是 0。
 *  (3)矩阵中的元素只在四个方向上相邻: 上、下、左、右。
 */
#include <vector>
#include <queue>
using namespace std;

/* DP解法见DP文件夹 */

#define MAX 10001
#define IS_IN(x, y) x >= 0 && y >= 0 && x < row && y < col
#define MAKE_POS(x, y) x * col + y;
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int row = matrix.size(), col = matrix[0].size();
        int direction[4][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}};
        vector<vector<int>> ans(row, vector<int>(col, MAX));
        queue<int> q;
        vector<int> vis(row * col, 0);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (matrix[i][j] == 0) {
                    /* 每个 0 都算一个bfs起点, 多起点泛洪 */
                    ans[i][j] = 0;
                    int pos = MAKE_POS(i, j);
                    q.push(pos); 
                    vis[pos] = 1;
                }
            }
        }
        while (!q.empty()) {
            int pos = q.front(); q.pop();
            int x = pos / col, y = pos % col;
            for (auto& d : direction) {
                int i = x + d[0], j = y + d[1];
                if (IS_IN(i, j)) {
                    pos = MAKE_POS(i, j);
                    if (vis[pos] == 0) {
                        ans[i][j] = ans[x][y] + 1;
                        q.push(pos);
                        vis[pos] = 1;
                    }
                }
            }
        }
        return ans;
    }
};