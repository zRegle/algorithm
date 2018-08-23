#include <iostream>
#include <vector>
using namespace std;

/*
 * leetcode 200. Number of Islands
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
 * 一开始想利用grid[i-1][j]和grid[i][j-1]动态规划来求解的, 但是发现又有一个问题
 * 例如
 * 111
 * 010
 * 111
 * 在最后一行的第一个1, 满足上面和左边都不为1, 应该算作一个岛屿, 但是在第二个1那与上面相连了
 * 想来想去没有比较好的办法解决, 最终还是利用dfs来解决问题了
 * 思路很简单, 遇到一个1时, 就向上下左右扩展, 只要相邻的格子是1, 就标记为0, 直到没有相邻格子为1
 * 然后继续处理下一个格子
 */

class Solution {
public:
    int row = -1;
    int column = -1;
    int numIslands(vector<vector<char>>& grid) {
        row = grid.size();
        if (!row) return 0;
        column = grid[0].size();
        if (!column) return 0;
        int cnt = 0;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                if (grid[i][j] == '1') {
                    markIsland(grid, i, j);
                    cnt++;
                }
            }
        }
        return cnt;
    }

    void markIsland(vector<vector<char>>& grid, int i, int j) {
        if (i < 0 || j < 0 || i >= row || j >= column || grid[i][j] != '1') return;
        grid[i][j] = 0;
        markIsland(grid, i+1 ,j);
        markIsland(grid, i-1 ,j);
        markIsland(grid, i ,j+1);
        markIsland(grid, i ,j-1);
    }
};