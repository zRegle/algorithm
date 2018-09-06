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
                if (flow_pacific == 2 && flow_atlantic == 2)
                    res.emplace_back(pair<int, int>(i, j));
            }
        }
        return res;
    }

    //在dfs的过程中, 我们可能得知从A出发, 经过B不能流到对应的海洋, 那么在计算完A之后, ocean[B] = 1
    //但是可能在计算B时, 我们可以从B出发, 经过A流到对应的海洋
    //如果我们错误地把记录下来的值当做最终的计算结果, 那就会出错
    //所以我们要重新检查ocean[B]是否可以经过上一行格子或者左边的格子流到对应的海洋
    int re_check(int i, int j, vector<vector<int>>& ocean, vector<vector<int>>& matrix) {
        int left = 0, top = 0;
        if (i > 0 && matrix[i][j] >= matrix[i-1][j]) top = ocean[i-1][j];
        if (j > 0 && matrix[i][j] >= matrix[i][j-1]) left = ocean[i][j-1];
        return (top == 2 || left == 2) ? 2 : 1;
    }

    int pacific(int i, int j, vector<vector<int>>& pac, vector<vector<int>>& matrix) {
        if (pac[i][j] == 2 || !pac[i][j]) return pac[i][j]; //已经计算过结果
        if (pac[i][j] == 1) return re_check(i, j, pac, matrix) = pac[i][j]; //复检
        if (i == 0 || j == 0) return pac[i][j] = 2; //就在边缘, 直接流到太平洋
        pac[i][j] = 0;  //开始计算结果
        int top = 0, left = 0, down = 0, right = 0;
        if (i > 0 && matrix[i][j] >= matrix[i-1][j]) top = pacific(i-1, j, pac, matrix);
        if (top != 2) { if (j > 0 && matrix[i][j] >= matrix[i][j-1]) left = pacific(i, j-1, pac, matrix); }
        if (top != 2 && left != 2) { if (i < row-1 && matrix[i][j] >= matrix[i+1][j]) down = pacific(i+1, j, pac, matrix); }
        if (top != 2 && left != 2 && down != 2) { if (j < column-1 && matrix[i][j] >= matrix[i][j+1]) right = pacific(i, j+1, pac, matrix); }
        pac[i][j] = (top == 2 || left == 2 || down == 2 || right == 2) ? 2 : 1;
        return pac[i][j];
    }

    int atlantic(int i, int j, vector<vector<int>>& atlan, vector<vector<int>>& matrix) {
        if (atlan[i][j] == 2 || !atlan[i][j]) return atlan[i][j];
        if (atlan[i][j] == 1) return re_check(i, j, atlan, matrix) = atlan[i][j];
        if (i == row-1 || j == column-1) return atlan[i][j] = 2;
        atlan[i][j] = 0;
        int top = 0, left = 0, down = 0, right = 0;
        if (i > 0 && matrix[i][j] >= matrix[i-1][j]) top = atlantic(i-1, j, atlan, matrix);
        if (top != 2) { if (j > 0 && matrix[i][j] >= matrix[i][j-1]) left = atlantic(i, j-1, atlan, matrix); }
        if (top != 2 && left != 2) { if (i < row-1 && matrix[i][j] >= matrix[i+1][j]) down = atlantic(i+1, j, atlan, matrix); }
        if (top != 2 && left != 2 && down != 2) { if (j < column-1 && matrix[i][j] >= matrix[i][j+1]) right = atlantic(i, j+1, atlan, matrix); }
        atlan[i][j] = (top == 2 || left == 2 || down == 2 || right == 2) ? 2 : 1;
        return atlan[i][j];
    }
};

/**
 * 更加优雅的做法, from leetcode
 *
 * 基本思路: 从两个大洋出发, 看能否到达某个格子
 */
class Solution2 {
public:
    vector<pair<int, int>> res;
    vector<vector<int>> visited;

    /**
     *
     * @param matrix 高度矩阵
     * @param x 横坐标
     * @param y 纵坐标
     * @param pre 上一个格子的高度
     * @param preval 上一个格子的状态, 1代表可以到达太平洋, 2代表可以到达大西洋, 3代表都可以
     */
    void dfs(vector<vector<int>>& matrix, int x, int y, int pre, int preval){
        if (x < 0 || x >= matrix.size() || y < 0 || y >= matrix[0].size()
            || matrix[x][y] < pre || (visited[x][y] & preval) == preval)
            //(visit[x][y] & preval) == preval
            //前一个格子和这个格子都可以流到太平洋或者大西洋, 或者都可以, 表明已经dfs过了
            return;
        //如果(visit[x][y] & preval) != preval
        //证明前一个格子和后一个格子的状态不一致, 需要判断当前格子能否能否达到前一个格子可以到达的大洋
        //譬如: preval = 1, visit[x][y] = 2, 则当前格子符合最终条件, 加入结果集,
        //      preval = 1, visit[x][y] = 0, 当前格子可以流到太平洋, 继续判断是否可以流到大西洋
        visited[x][y] |= preval;
        if (visited[x][y] == 3) res.emplace_back(pair<int, int>(x, y));
        dfs(matrix, x + 1, y, matrix[x][y], visited[x][y]); dfs(matrix, x - 1, y, matrix[x][y], visited[x][y]);
        dfs(matrix, x, y + 1, matrix[x][y], visited[x][y]); dfs(matrix, x, y - 1, matrix[x][y], visited[x][y]);
    }

    vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
        if (matrix.empty()) return res;
        int m = matrix.size(), n = matrix[0].size();
        visited.resize(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            dfs(matrix, i, 0, INT_MIN, 1);  //从左边界太平洋出发
            dfs(matrix, i, n - 1, INT_MIN, 2);  //从右边界大西洋出发
        }
        for (int i = 0; i < n; i++) {
            dfs(matrix, 0, i, INT_MIN, 1);  //从上边界太平洋出发
            dfs(matrix, m - 1, i, INT_MIN, 2);  //从下边界大西洋出发
        }
        return res;
    }
};

int main() {
    vector<vector<int>> matrix;
    int row, column;
    cin>>row>>column;
    for (int i = 0; i < row; i++) {
        vector<int> v(column, INT_MAX);
        for (int j = 0; j < column; ++j) {
            cin>>v[j];
        }
        matrix.push_back(v);
    }
    Solution s;
    auto res = s.pacificAtlantic(matrix);
    for (auto p : res) {
        cout<<'['<<p.first<<','<<p.second<<']'<<" ";
    }
    return 0;
}
