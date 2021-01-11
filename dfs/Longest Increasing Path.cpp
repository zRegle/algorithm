#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/*
 * leetcode 329. Longest Increasing Path in a Matrix
 * 给定一个矩阵, 求最长递增路径(每个格子可以往上下左右走)
 *
 * 初步想法: 遍历每一个格子, 暴力dfs递归所有结果, 求最大值, 结果超时了
 * 在原来的思路里, 我们会重复经过已经知道结果的格子, 所以我们要尽量缓存已经遍历过的结果
 * dp[i][j]表示以(i,j)结尾的, 最长递增路径的长度
 */
class Solution {
public:
    int row = -1;
    int column = -1;

    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int max_len = INT_MIN;
        row = matrix.size();
        if (!row) return 0;
        column = matrix[0].size();
        if (!column) return 0;
        vector<vector<int>> dp((unsigned int)row, vector<int>(column, 0));
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++)
                max_len = max(max_len, dfs(matrix, dp, i, j));
        }
        return max_len;
    }

    //实际上我们在递归的时候走的是递减的路线
    int dfs(vector<vector<int>>& matrix, vector<vector<int>>& dp, int i, int j) {
        if (dp[i][j]) return dp[i][j];
        int cur = matrix[i][j];
        if (i > 0 && cur > matrix[i-1][j]) dp[i][j] = max(dp[i][j], dfs(matrix, dp, i-1, j));
        if (j > 0 && cur > matrix[i][j-1]) dp[i][j] = max(dp[i][j], dfs(matrix, dp, i, j-1));
        if (i < row-1 && cur > matrix[i+1][j]) dp[i][j] = max(dp[i][j], dfs(matrix, dp, i+1, j));
        if (j < column-1 && cur > matrix[i][j+1]) dp[i][j] = max(dp[i][j] ,dfs(matrix, dp, i, j+1));
        dp[i][j]++;
        return dp[i][j];
    }
};

