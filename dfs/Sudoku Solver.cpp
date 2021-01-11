/* Leetcode 37.解数独
 * 编写一个程序，通过已填充的空格来解决数独问题。
 */
#include <vector>
using namespace std;

//SET: 设置数字对应的bit为1
//CHECK: 检查数字对应的bit是否为0, 是则结果为0(这个宏记得加括号,不然!CHECK宏展开后就变成!flag & (1 << x))
//REMOVE: 设置数字对应的bit为0
#define SET(x, flag) flag |= (1 << x)
#define CHECK(x, flag) (flag & (1 << x))
#define REMOVE(x, flag) flag &= ~(1 << x)

class Solution {
public:
    //9行9列9矩阵的位图
    int row[9] = {0}, col[9] = {0}, matrix[9] = {0};
    void solveSudoku(vector<vector<char>>& board) {
        //初始化整个棋盘的位图
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    int x = board[i][j] - '0';
                    int mIdx = (i/3)*3 + j/3;
                    SET(x,row[i]);
                    SET(x,col[j]);
                    SET(x,matrix[mIdx]);
                }
            }
        }
        (void)solver(board, 0, 0);
    }

    bool solver(vector<vector<char>>& board, int i, int j) {
        if (j >= 9) return solver(board, i+1, 0);   //这一行到头了, 递归下一行
        if (i >= 9) return true;    //递归完毕, 寻找到解, 返回true
        if (board[i][j] != '.') return solver(board, i, j+1);   //这列已经被填了, 递归下一列
        int mIdx = (i/3)*3 + j/3, k = 1;
    Test:
        for (; k <= 9; k++) {
            if (!CHECK(k, row[i]) && !CHECK(k,col[j]) && !CHECK(k,matrix[mIdx])) 
                break;
        }
        if (k > 9) return false;  //没数字可以填进去, 返回false
        //设置位图
        SET(k,row[i]);
        SET(k,col[j]);
        SET(k,matrix[mIdx]);
        //如果填了这个数字导致没有解, 则去除这个数字, 尝试下一个
        if (!solver(board, i, j+1)) {
            REMOVE(k,row[i]);
            REMOVE(k,col[j]);
            REMOVE(k,matrix[mIdx]);
            k++;    //试填下一个数字
            goto Test;
        } else {
            board[i][j] = (char)(k + '0');
            return true;
        }
    }
};