#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/*
 * leetcode 417. Pacific Atlantic Water Flow
 * 给定一个m x n的矩阵, 每个元素代表那个格子的高度, 矩阵的上方和左边是太平洋, 下方和右边是大西洋
 * 海水只能从高流向低, 或者在相同高度的两个格子流过, 求出所有既能流向太平洋, 也能流向大西洋的格子
 * 例如:
 * Pacific ~  ~  ~  ~  ~
 *      ~  1  2  2  3 (5) *
 *      ~  3  2  3 (4)(4) *
 *      ~  2  4 (5) 3  1  *
 *      ~ (6)(7) 1  4  5  * 
 *      ~ (5) 1  1  2  4  *
 *         *  *  *  *  * Atlantic
 * 结果: [[0,4], [1,3], [1,4], [2,2], [3,0], [3,1], [4,0]] 
 *       带括号的就是符合要求的格子
 *
 * 思路: 暴力dfs就行, 过程中需要记录已经遍历过的格子
 *
 * vector<vector<int>> pac(row, vector<int>(column, INT_MAX));
 * vector<vector<int>> atlan(row, vector<int>(column, INT_MAX));
 * 这两个变量分别记录了当前格子能否流到对应的大洋的状态, 存在4种值
 * 1. INT_MAX -> 还没计算确认
 * 2. 0 -> 正在计算结果
 * 3. 1 -> 不能流向该大洋
 * 4. 2 -> 可以流向该大洋
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
                if (flow_pacific == 1) flow_pacific = re_check(i, j, pac);
                if (flow_atlantic == 1) flow_atlantic = re_check(i, j, atlan);
                if (flow_pacific == 2 && flow_atlantic == 2)
                    res.emplace_back(pair<int, int>(i, j));
            }
        }
        return res;
    }

    //在递归中, 从前一个格子到达当前格子的路径不符合要求, 但是在循环中可以从当前格子返回前一个格子的路径合法
    //所以我们确认是否可以从当前格子出发, 经过之前循环过的格子, 流到大洋    
    int re_check(int i, int j, vector<vector<int>>& res) {
        int left = 0, top = 0;
        if (i > 0) top = res[i-1][j];
        if (j > 0) left = res[i][j-1];
        return top | left; 
    }

    int pacific(int i, int j, vector<vector<int>>& pac, vector<vector<int>>& matrix) {
        if (pac[i][j] != INT_MAX) return pac[i][j]; //已经计算过结果
        if (i == 0 || j == 0) return pac[i][j] = 2;
        pac[i][j] = 0;
        int top = 0, left = 0, down = 0, right = 0;
        if (i > 0 && matrix[i][j] >= matrix[i-1][j]) top = pacific(i-1, j, pac, matrix);
        if (top != 2) { if (j > 0 && matrix[i][j] >= matrix[i][j-1]) left = pacific(i, j-1, pac, matrix); }
        if (top != 2 && left != 2) { if (i < row-1 && matrix[i][j] >= matrix[i+1][j]) down = pacific(i+1, j, pac, matrix); }
        if (top != 2 && left != 2 && down != 2) { if (j < column-1 && matrix[i][j] >= matrix[i][j+1]) right = pacific(i, j+1, pac, matrix); }
        pac[i][j] = top | left | down | right;
        return pac[i][j];
    }

    int atlantic(int i, int j, vector<vector<int>>& atlan, vector<vector<int>>& matrix) {
        if (atlan[i][j] != INT_MAX) return atlan[i][j];
        if (i == row-1 || j == column-1) return atlan[i][j] = 2;
        atlan[i][j] = 0;
        int top = 0, left = 0, down = 0, right = 0;
        if (i > 0 && matrix[i][j] >= matrix[i-1][j]) top = atlantic(i-1, j, atlan, matrix);
        if (top != 2) { if (j > 0 && matrix[i][j] >= matrix[i][j-1]) left = atlantic(i, j-1, atlan, matrix); }
        if (top != 2 && left != 2) { if (i < row-1 && matrix[i][j] >= matrix[i+1][j]) down = atlantic(i+1, j, atlan, matrix); }
        if (top != 2 && left != 2 && down != 2) { if (j < column-1 && matrix[i][j] >= matrix[i][j+1]) right = atlantic(i, j+1, atlan, matrix); }
        atlan[i][j] = top | left | down | right;
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
