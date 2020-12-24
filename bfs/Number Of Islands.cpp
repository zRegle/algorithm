/* leetcode 200. Number of Islands
 * 给定一个01矩阵, 1代表有土地, 0代表海水, 求岛屿的个数
 * Input:
 * 11000
 * 11000
 * 00100
 * 00011
 * 
 * Output: 3
 * 
 * 思路:
 * 利用队列BFS, 遇到一个1时, 就向上下左右扩展, 只要相邻的格子是1, 就标记为0, 直到没有相邻格子为1
 * 然后继续处理下一个格子
 */
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int row, col;

void markIsland(vector<vector<int>>& matrix, int i, int j) {
    int offset[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    queue<pair<int, int>> q;
    q.push({i, j});
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        for (auto o : offset) {
            int r = p.first + o[0], c = p.second + o[1];
            if (r < 0 || c < 0 || r >= row || c >= col || !matrix[r][c])
                continue;
            matrix[r][c] = 0;
            q.push({r, c});
        }
    }
}

int countIsland(vector<vector<int>>& matrix) {
    int cnt = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (matrix[i][j]) {
                matrix[i][j] = 0;
                cnt++;
                markIsland(matrix, i, j);
            }
        }
    }
    return cnt;
}

int main() {
    cin>>row>>col;
    vector<vector<int>> matrix(row, vector<int>(col));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            cin>>matrix[i][j];
    }
    cout<<countIsland(matrix);
    return 0;
}