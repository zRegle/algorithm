/* Leetcode 48 旋转图像
 * 给定一个 n × n 的二维矩阵表示一个图像。
 * 将图像顺时针旋转 90 度。
 * 说明：
 * 你必须在原地旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要使用另一个矩阵来旋转图像。
 * 示例 1:
 * 给定 matrix =
 * [ 
 *  [1,2,3], 
 *  [4,5,6], 
 *  [7,8,9]
 * ],
 * 原地旋转输入矩阵，使其变为:
 * [ 
 *  [7,4,1], 
 *  [8,5,2], 
 *  [9,6,3]
 * ]
 */

#include <vector>
#include <algorithm>
using namespace std;

//思路1: 转置矩阵再翻转
class Solution {
public:
    inline void transposition(vector<vector<int>>& matrix, int i, int j) {
        int tmp = matrix[j][i];
        matrix[j][i] = matrix[i][j];
        matrix[i][j] = tmp;
    }
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if (n < 2) return;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++)
                transposition(matrix, i, j);
        }
        for (int i = 0; i < n; i++) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};

//思路2, 实质是几个矩形在旋转
// https://leetcode-cn.com/problems/rotate-image/solution/yi-ci-xing-jiao-huan-by-powcai/
// [i, j] -> [j, n-i-1]
// [j, n-i-1] -> [n-i-1][n-j-1]
// [n-i-1, n-j-1] -> [n-j-1, i]
// [n-j-1, i] -> [i, j]
//
class Solution2 {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for (int i = 0; i < n/2; i++) {
            for (int j = 0; j < n-i-1; j++) {
                int tmp = matrix[i][j];
                matrix[i][j] = matrix[n-j-1][i];
                matrix[n-j-1][i] = matrix[n-i-1][n-j-1];
                matrix[n-i-1][n-j-1] = matrix[j][n-i-1];
                matrix[j][n-i-1] = tmp;
            }
        }
    }
};