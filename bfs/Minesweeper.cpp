/**
 * Leetcode 529.扫雷游戏
 * 让我们一起来玩扫雷游戏！
 * 给定一个代表游戏板的二维字符矩阵。 'M' 代表一个未挖出的地雷，'E' 代表一个未挖出的空方块，
 * 'B' 代表没有相邻（上，下，左，右，和所有4个对角线）地雷的已挖出的空白方块，
 * 数字（'1' 到 '8'）表示有多少地雷与这块已挖出的方块相邻，'X' 则表示一个已挖出的地雷。
 * 
 * 现在给出在所有未挖出的方块中（'M'或者'E'）的下一个点击位置（行和列索引），根据以下规则，
 * 返回相应位置被点击后对应的面板：
 *  1.如果一个地雷（'M'）被挖出，游戏就结束了- 把它改为 'X'。
 *  2.如果一个没有相邻地雷的空方块（'E'）被挖出，修改它为（'B'），并且所有和其相邻的未挖出方块都应该被递归地揭露。
 *  3.如果一个至少与一个地雷相邻的空方块（'E'）被挖出，修改它为数字（'1'到'8'），表示相邻地雷的数量。
 *  4.如果在此次点击中，若无更多方块可被揭露，则返回面板。
 * 
 * 示例 1：
 *  输入: 
 *   [['E', 'E', 'E', 'E', 'E'],
 *    ['E', 'E', 'M', 'E', 'E'],
 *    ['E', 'E', 'E', 'E', 'E'],
 *    ['E', 'E', 'E', 'E', 'E']]
 *   Click : [3,0]
 *  输出: 
 *   [['B', '1', 'E', '1', 'B'],
 *    ['B', '1', 'M', '1', 'B'],
 *    ['B', '1', '1', '1', 'B'],
 *    ['B', 'B', 'B', 'B', 'B']]
 */
#include <queue>
#include <vector>
using namespace std;

/* dfs方法参考dfs文件夹 */

class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        row = board.size();
        col = board[0].size();

        int x = click[0], y = click[1];
        if (board[x][y] == 'M') {
            /* 踩雷就直接game over */
            board[x][y] = 'X';
            return board;
        }

        queue<int> q;
        q.push(x * col + y);
        while (!q.empty()) {
            int pos = q.front(); q.pop();
            x = pos / col, y = pos % col;
            int mine_cnt = 0;
            for (auto&d : direction) {
                /* 数一下周围有多少个地雷 */
                int i = x + d[0], j = y + d[1];
                if (isIn(i, j) && board[i][j] == 'M') 
                    mine_cnt++;
            }
            if (mine_cnt > 0) {
                /* 周围有地雷, 不用bfs周围的格子 */
                board[x][y] = mine_cnt + '0';
            } else {
                /* 周围没有地雷, 继续bfs */
                board[x][y] = 'B';
                for (auto&d : direction) {
                    int i = x + d[0], j = y + d[1];
                    if (isIn(i, j) && board[i][j] == 'E') {
                        board[i][j] = 'V'; /* 原地修改, 充当visited */
                        q.push(i * col + j);
                    }
                }
            }
        }
        return board;
    }
private:
    int row, col;
    int direction[8][2] = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0},
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };
    inline bool isIn(int x, int y) const {
        return x >= 0 && x < row && y >= 0 && y < col;
    }
};