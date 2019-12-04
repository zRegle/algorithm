/* Leetcdoe 73 矩阵置零
 * 给定一个 m x n 的矩阵，如果一个元素为 0，则将其所在行和列的所有元素都设为0。
 * 请使用原地算法, 即空间复杂度要为O(1)
 * 示例 2:
 * 输入
 * [
 *   [0,1,2,0],
 *   [3,4,5,2],
 *   [1,3,1,5]
 * ]
 * 输出
 * [
 *   [0,0,0,0],
 *   [0,4,5,0],
 *   [0,3,1,0]
 * ]
 */

#include <vector>
using namespace std;

//利用额外的存储空间存放为0的坐标
//时间复杂度O(mn), 空间复杂度O(m+n)
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if (matrix.empty()) return;
        vector<pair<int, int>> coordinate;
        int r = matrix.size();
        int c = matrix[0].size();
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (!matrix[i][j]) {
                    pair<int, int> p(i, j);
                    coordinate.emplace_back(p);
                }
            }
        }
        for (pair<int, int>& p : coordinate) {
            int row = p.first, col = p.second;
            for (int i = 0; i < c; i++)
                matrix[row][i] = 0;
            for (int j = 0; j < r; j++)
                matrix[j][col] = 0;
        }
    }
};

//将状态值存在矩阵的第一个元素, 如果(i, j)是0, 那么将(i, 0)和(0, j)置为0, 检查完后统一处理
//要首先判断第一行和第一列有没有0
//时间复杂度O(mn), 空间复杂度O(1)
class Solution2 {
public:
    void setZeros(vector<vector<int>>& matrix) {
        bool isZeroCol = false;
        bool isZeroRow = false;
        for (int i = 0; i < matrix.size(); i++) { //判断第一行是否存在0元素
            if (matrix[i][0] == 0) {
                isZeroCol = true;
                break;
            }
        }
        for (int i = 0; i < matrix[0].size(); i++) { //判断第一列是否存在0元素
            if (matrix[0][i] == 0) {
                isZeroRow = true;
                break;
            }
        }
        for (int i = 1; i < matrix.size(); i++) { //检查剩下的行和列
            for (int j = 1; j < matrix[0].size(); j++)
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
        }
        for (int i = 1; i < matrix.size(); i++) { //将0元素所在的行和列置0
            for (int j = 1; j < matrix[0].size(); j++)
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;
        }
        if (isZeroCol) { //回头再来处理第一行
            for (int i = 0; i < matrix.size(); i++)
                matrix[i][0] = 0;
        }
        if (isZeroRow) { //处理第一列
            for (int i = 0; i < matrix[0].size(); i++)
                matrix[0][i] = 0;
        }
    }
};