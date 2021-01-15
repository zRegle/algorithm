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
using namespace std;

#define MAX 10001
/* 双向dp, 一次左上到右下, 一次右下到左上 */
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int row = matrix.size(), col = matrix[0].size();
        vector<vector<int>> dp(row, vector<int>(col, MAX));
        /* 第一次dp, 确定(i, j)离它左上方的 0 的最短距离 */
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (matrix[i][j] == 0) {
                    dp[i][j] = 0;
                    continue;
                }
                if (i == 0 && j == 0) continue;
                if (i > 0) dp[i][j] = min(dp[i][j], dp[i-1][j] + 1);
                if (j > 0) dp[i][j] = min(dp[i][j], dp[i][j-1] + 1);
            }
        }
        /* 第二次dp, 确定(i, j)离它右下方的 0 的最短距离. 
         * 再结合第一次dp的结果即为答案 
         */
        for (int i = row-1; i >= 0; i--) {
            for (int j = col-1; j >= 0; j--) {
                if (matrix[i][j] == 0) {
                    dp[i][j] = 0;
                    continue;
                }
                if (i == row-1 && j == col-1) continue;
                if (i < row-1) dp[i][j] = min(dp[i][j], dp[i+1][j] + 1);
                if (j < col-1) dp[i][j] = min(dp[i][j], dp[i][j+1] + 1);
            }
        }
        return dp;
    }
};