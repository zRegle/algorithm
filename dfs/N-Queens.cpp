/* Leetcode 51 N皇后
 * 给定一个整数 n，返回所有不同的 n 皇后问题的解决方案。
 * 每一种解法包含一个明确的 n 皇后问题的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位
 * 示例
 * 输入: 4
 * 输出:
 *  [".Q..",  // 解法1
 *  "...Q",
 *  "Q...",
 *  "..Q."]
 *
 *  ["..Q.",  // 解法2
 *  "Q...",
 *  "...Q",
 *  ".Q.."]
 * 解释: 4 皇后问题存在两个不同的解法。
 */

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

//当[i,j]放了一个皇后后, 第i行和第j列就不能再放皇后了
//dfs+回溯, 不断调整皇后位置
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        bool** chessboard = new bool*[n];
        for (int i = 0; i < n; i++) {
            chessboard[i] = new bool[n];
            memset(chessboard[i], false, sizeof(bool)*n);
        }
        vector<vector<string>> res;
        queen(chessboard, res, n, 0);
        for (int i = 0; i < n; i++) {
            delete[](chessboard[i]);
            chessboard[i] = nullptr;
        }
        delete[](chessboard); chessboard = nullptr;
        return res;
    }
private:
    void queen(bool** chessboard, vector<vector<string>>& res, int n, int row) {
        if (row == n) {
            vector<string> v(n);
            string s;
            for (int i = 0; i < n; i++) {
                s = "";
                for (int j = 0; j < n ; j++) {
                    if (chessboard[i][j])
                        s += 'Q';
                    else
                        s += '.';
                }
                v[i] = s;
            }
            res.push_back(v);
        } else {
            for (int col = 0; col < n; col++) {
                if (check(chessboard, row, col, n)) {
                    chessboard[row][col] = true; //这一层尝试在col上放皇后
                    queen(chessboard, res, n, row+1);   //dfs
                    chessboard[row][col] = false;   //dfs完后, 还原数据, 再在别的col尝试
                }
            }
        }
    }

    bool check(bool** chessboard, int row, int col, int n) {
        //检查行
        for (int i = 0; i < n; i++) {
            if (chessboard[row][i] && i != col)
                return false;
        }
        //检查列
        for (int j = 0; j < n; j++) {
            if (chessboard[j][col] && j != row)
                return false;
        }
        //检查左上角
        for (int i = row-1, j = col-1; i >= 0 && j >= 0; i--, j--) {
            if (chessboard[i][j])
                return false;
        }
        //检查右上角
        for (int i = row-1, j = col+1; i >= 0 && j < n; i--, j++) {
            if (chessboard[i][j])
                return false;
        }
        //检查右下角
        for (int i = row+1, j = col+1; i < n && j < n; i++, j++) {
            if (chessboard[i][j])
                return false;
        }
        //检查左下角
        for (int i = row+1, j = col-1; i < n && j >= 0; i++, j--) {
            if (chessboard[i][j])
                return false;
        }
        return true;
    }
};