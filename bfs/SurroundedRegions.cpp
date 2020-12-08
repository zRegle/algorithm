#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        row = board.size();
        if (row == 0) return;
        col = board[0].size();
        for (int i = 0; i < row; i++) {
            bfs(i, 0, board);
            bfs(i, col - 1,  board);
        }
        for (int j = 0; j < col; j++) {
            bfs(0, j, board);
            bfs(row - 1, j, board);
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
    void bfs(int i, int j, vector<vector<char>>& board) {
        queue<int> q;
        if (board[i][j] == 'O') {
            board[i][j] = '#';
            q.push(i * col + j);
        }
        while (!q.empty()) {
            int pos = q.front(); q.pop();
            i = pos / col, j = pos % col;
            for (auto d : direct) {
                int x = i + d[0], y = j + d[1];
                if (x >= 0 && y >= 0 && x < row && y < col && board[x][y] == 'O') {
                    board[x][y] = '#';
                    q.push(x * col + y);
                }
            }
        }
    }
};