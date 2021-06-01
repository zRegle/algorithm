/**
 * Leetcode 304.二维区域和检索 - 矩阵不可变
 * 给定一个二维矩阵，计算其子矩形范围内元素的总和，该子矩阵的左上角为 (row1, col1) ，右下角为 (row2, col2) 。
 *  
 * 示例：
 * 给定 matrix = [
 *   [3, 0, 1, 4, 2],
 *   [5, 6, 3, 2, 1],
 *   [1, 2, 0, 1, 5],
 *   [4, 1, 0, 1, 7],
 *   [1, 0, 3, 0, 5]
 * ]
 * sumRegion(2, 1, 4, 3) -> 8
 * (左上角 (row1, col1) = (2, 1) ，右下角(row2, col2) = (4, 3)，该子矩形内元素的总和为 8。)
 * 
 * sumRegion(1, 1, 2, 2) -> 11
 * sumRegion(1, 2, 2, 4) -> 12
 *  
 * 提示：
 * (1)你可以假设矩阵不可变。
 * (2)会多次调用 sumRegion 方法。
 * (3)你可以假设 row1 ≤ row2 且 col1 ≤ col2 。
 */
#include <vector>
using std::vector;


/**
 * 设preSum[i][j] = 以(i, j)为右下角的矩阵的元素总和
 * 递推公式为:
 *  preSum[i][j] = preSum[i-1][j] + preSum[i][j-1] - preSum[i-1][j-1] + matrix[i][j]
 * 
 * 那么对于任意的矩阵(r1, c1, r2, c2)
 * sum(r1, c1, r2, c2) = preSum[r2][c2] - preSum[r2][c1-1] - preSum[r1-1][c2] + preSum[r1-1][c1-1]
 * 
 * (画个图很好理解)
 */
class NumMatrix {
public:
    NumMatrix(vector<vector<int> >& matrix) {
        int m = matrix.size();
        if (m > 0) {
            int n = matrix[0].size();
            preSum.resize(m, vector<int>(n));
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (i > 0) preSum[i][j] += preSum[i-1][j];
                    if (j > 0) preSum[i][j] += preSum[i][j-1];
                    if (i > 0 && j > 0) preSum[i][j] -= preSum[i-1][j-1];
                    preSum[i][j] += matrix[i][j];
                }
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        int ans = preSum[row2][col2];
        if (col1 > 0) ans -= preSum[row2][col1-1];
        if (row1 > 0) ans -= preSum[row1-1][col2];
        if (row1 > 0 && col1 > 0) ans += preSum[row1-1][col1-1];
        return ans;
    }

private:
    vector<vector<int> > preSum;
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */