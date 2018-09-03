#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/*
 * leetcode 417. Pacific Atlantic Water Flow
 */

class Solution {
public:
    int row, column;

    vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
        vector<pair<int, int>> res;
        row = matrix.size();
        if (!row) return res;
        column = matrix[0].size();
        if (!column) return res;
        vector<vector<int>> pac(row, vector<int>(column, INT_MAX));
        vector<vector<int>> atlan(row, vector<int>(column, INT_MAX));
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                int flow_pacific = pacific(i, j, pac, matrix);
                int flow_atlantic = atlantic(i, j, atlan, matrix);
                if (flow_atlantic == 2 && flow_pacific == 2)
                    res.emplace_back(pair<int, int>(i, j));
            }
        }
        return res;
    }

    //TODO, 如何解决在递归中, 从前一个格子到达当前格子的路径不符合要求, 但是在循环中可以从当前格子返回前一个格子的路径合法
    int pacific(int i, int j, vector<vector<int>>& pac, vector<vector<int>>& matrix) {
        if (pac[i][j] != INT_MAX) return pac[i][j];
        if (i == 0 || j == 0) return pac[i][j] = 2;
        pac[i][j] = 0;
        int top = 0, left = 0, down = 0, right = 0;
        if (i > 0 && matrix[i][j] >= matrix[i-1][j]) top = pacific(i-1, j, pac, matrix);
        if (j > 0 && matrix[i][j] >= matrix[i][j-1]) left = pacific(i, j-1, pac, matrix);
        if (i < row-1 && matrix[i][j] >= matrix[i+1][j]) down = pacific(i+1, j, pac, matrix);
        if (j < column-1 && matrix[i][j] >= matrix[i][j+1]) right = pacific(i, j+1, pac, matrix);
        pac[i][j] = (top == 2 || left == 2 || down == 2 || right == 2) ? 2 : 1;
        return pac[i][j];
    }

    int atlantic(int i, int j, vector<vector<int>>& atlan, vector<vector<int>>& matrix) {
        if (atlan[i][j] != INT_MAX) return atlan[i][j];
        if (i == row-1 || j == column-1) return atlan[i][j] = 2;
        atlan[i][j] = 0;
        int top = 0, left = 0, down = 0, right = 0;
        if (i > 0 && matrix[i][j] >= matrix[i-1][j]) top = atlantic(i-1, j, atlan, matrix);
        if (j > 0 && matrix[i][j] >= matrix[i][j-1]) left = atlantic(i, j-1, atlan, matrix);
        if (i < row-1 && matrix[i][j] >= matrix[i+1][j]) down = atlantic(i+1, j, atlan, matrix);
        if (j < column-1 && matrix[i][j] >= matrix[i][j+1]) right = atlantic(i, j+1, atlan, matrix);
        atlan[i][j] = (top == 2 || left == 2 || down == 2 || right == 2) ? 2 : 1;
        return atlan[i][j];
    }
};

int main() {
    vector<vector<int>> matrix;
    vector<int> v1({1,2,2,3,5});
    vector<int> v2({3,2,3,4,4});
    vector<int> v3({2,4,5,3,1});
    vector<int> v4({6,7,1,4,5});
    vector<int> v5({5,1,1,2,4});
    matrix.push_back(v1);
    matrix.push_back(v2);
    matrix.push_back(v3);
    matrix.push_back(v4);
    matrix.push_back(v5);
    Solution s;
    auto res = s.pacificAtlantic(matrix);
    for (auto p : res) {
        cout<<'['<<p.first<<','<<p.second<<']'<<" ";
    }
    return 0;
}