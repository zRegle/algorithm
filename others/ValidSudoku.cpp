/* Leetcode 36.有效的数独
 * 判断一个数独9x9的数独是否有效
 * (1)该数独只被填写了一部分, 没填写的以'.'代替
 * (2)只需要判断已经填写了的数独是否有效
 * (3)该数独不一定可解
 */
#include <vector>
using namespace std;

#define SET(num, flag) flag |= (1 << num)   //设置对应的bit为1
#define CHECK(num, flag) flag & (1 << num)  //检查对应的bit是否为1, 不为1则返回0

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int row;    //当前行的位图
        int col[9] = {0}, matrix[9] = {0};  //9列, 9个3x3矩阵的位图
        for (int i = 0; i < 9; i++) {
            row = 0;
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') continue;
                int x = board[i][j] - '0';
                int m_idx = (i / 3) * 3 + j / 3;    //3x3矩阵的下标, 从左往右, 从上往下数
                if (CHECK(x,row) || CHECK(x, col[j]) || CHECK(x, matrix[m_idx]))
                    return false;
                else {
                    SET(x, row);
                    SET(x, col[j]);
                    SET(x, matrix[m_idx]);
                }
            }
        }
        return true;
    }
};