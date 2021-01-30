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
using namespace std;

/* dfs暴搜 + 记忆化搜索 */
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        row = matrix.size(), col = matrix[0].size();
        memo.resize(row, vector<int>(col, 0));
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                ans = max(ans, dfs(i, j, matrix));
            }
        }
        return ans;
    }

private:
    int row, col, ans = 0;
    int direction[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
    /* 记忆化, memo[x][y]表示从(x,y)开始的最长递增路径长度 */
    vector<vector<int>> memo;
    int dfs(int x, int y, vector<vector<int>>& matrix) {
        if (memo[x][y] > 0)
            return memo[x][y];
        int val = matrix[x][y];
        matrix[x][y] = -1; /* 就地更改, 充当visited数组 */
        int length = 1; /* 从(x, y)始的最长递增路径长度 */
        for (auto& d : direction) {
            int i = x + d[0], j = y + d[1];
            if (isIn(i, j)) {
                if (matrix[i][j] > val)
                    /* dfs() + 1是因为要算上当前网格 */
                    length = max(length, dfs(i, j, matrix) + 1);
            }
        }
        matrix[x][y] = val; /* 回溯 */
        memo[x][y] = length;
        return length;
    }

    inline bool isIn(int x, int y) const {
        return x >= 0 && y >= 0 && x < row && y < col;
    }
};