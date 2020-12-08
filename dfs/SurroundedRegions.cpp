/**
 * 130. 被围绕的区域
 * 给定一个二维的矩阵，包含 'X' 和 'O'（字母 O）。
 * 找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。
 * 示例:
 *  X X X X
 *  X O O X
 *  X X O X
 *  X O X X
 * 运行你的函数后，矩阵变为：
 *  X X X X
 *  X X X X
 *  X X X X
 *  X O X X
 * 解释:
 * 被围绕的区间不会存在于边界上，换句话说，任何边界上的 'O' 都不会被填充为 'X'。 
 * 任何不在边界上，或不与边界上的 'O' 相连的 'O' 最终都会被填充为 'X'。
 * 如果两个元素在水平或垂直方向相邻，则称它们是“相连”的。
 */
#include <vector>
using namespace std;

/* 从边界的'O'出发, dfs或者bfs遍历所有与边界相连的'O', 全部置为'#' 
 * 然后在遍历矩阵, 遇到'O'表明这个'O'不会与边界的'O'相连, 即被'X'围绕
 * 遇到'#'就复原为'O'
 */
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        row = board.size();
        if (row == 0) return;
        col = board[0].size();
        for (int i = 0; i < row; i++) {
            dfs(i, 0, board);
            dfs(i, col - 1,  board);
        }
        for (int j = 0; j < col; j++) {
            dfs(0, j, board);
            dfs(row - 1, j, board);
        }
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (board[i][j] == '#')
                    board[i][j] = 'O';
                else if (board[i][j] == 'O')
                    board[i][j] = 'X';
            }
        }
    }
private:
    int row, col;
    int direct[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    void dfs(int i, int j, vector<vector<char>>& board) {
        if (i < 0 || j < 0 || i == row || j == col || board[i][j] != 'O')
            return;
        board[i][j] = '#';
        for (auto d : direct) {
            dfs(i + d[0], j + d[1], board);
        }
    }
};