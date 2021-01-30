/**
 * Leetcode 329. 矩阵中的最长递增路径
 * 给定一个 m x n 整数矩阵 matrix ，找出其中 最长递增路径 的长度。
 * 对于每个单元格，你可以往上，下，左，右四个方向移动。
 * 你不能在对角线方向上移动或移动到边界外（即不允许环绕）。
 *
 * 示例 1：
 *  输入：[[9,9,4],
 *        [6,6,8],
 *        [2,1,1]]
 *  输出：4
 *  解释：最长递增路径为 [1, 2, 6, 9]。
 * 示例 2：
 *  输入：[[3,4,5],
 *        [3,2,6],
 *        [2,2,1]]
 *  输出：4
 *  解释：最长递增路径是 [3, 4, 5, 6]。注意不允许在对角线方向上移动。
 * 示例 3：
 *  输入：matrix = [[1]]
 *  输出：1
 *
 * 提示：
 * (1)m == matrix.length
 * (2)n == matrix[i].length
 * (3)1 <= m, n <= 200
 * (4)0 <= matrix[i][j] <= 2^31 - 1
 */
#include <vector>
#include <queue>
using std::vector;
using std::queue;

/* dfs方法查看dfs文件夹 */

/**
 * 将矩阵看成一个有向图，如果相邻的两个单元格的值不相等，
 * 则在相邻的两个单元格之间存在一条从较小值指向较大值的有向边。
 * 计算每个单元格对应的出度，即有多少条边从该单元格出发。
 *
 * 基于出度的概念，可以使用拓扑排序求解。
 * 从所有出度为 0 的单元格开始广度优先搜索，每一轮搜索都会遍历当前层的所有单元格，
 * 更新其余单元格的出度，并将出度变为 0 的单元格加入下一层搜索。
 * 当搜索结束时，搜索的总层数即为矩阵中的最长递增路径的长度。
 */

#define ID(x, y) (x * col + y)
#define VALID(x, y) (x >= 0 && y >= 0 && x < row && y < col)
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int row = matrix.size(), col = matrix[0].size();
        int direction[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
        vector<vector<int>> outDegrees(row, vector<int>(col, 0));
        queue<int> q;
        /* 统计出度 */
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                for (auto& d : direction) {
                    int x = i + d[0], y = j + d[1];
                    if (VALID(x, y))
                        if (matrix[x][y] > matrix[i][j])
                            outDegrees[i][j]++;
                }
                if (outDegrees[i][j] == 0)
                    /* 出度为0的入队列 */
                    q.push(ID(i ,j));
            }
        }
        int level = 0;
        /* 多起点bfs */
        while (!q.empty()) {
            level++;
            int size = q.size();
            while (size--) {
                int pos = q.front(); q.pop();
                int x = pos / col, y = pos % col;
                for (auto& d : direction) {
                    int i = x + d[0], j = y + d[1];
                    if (VALID(i, j)) {
                        if (matrix[i][j] < matrix[x][y]) {
                            outDegrees[i][j]--; /* 出度减一 */
                            if (outDegrees[i][j] == 0)
                                /* 出度为0的入队列 */
                                q.push(ID(i, j));
                        }
                    }
                }
            }
        }
        return level;
    }
};