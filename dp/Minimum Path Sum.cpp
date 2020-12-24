/* Leetcode 64 最小路径和
 * 给定一个包含非负整数的 m x n 网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
 * 说明：每次只能向下或者向右移动一步。
 * 示例:
 * 输入:
 * [
 *  [1,3,1],
 *  [1,5,1],
 *  [4,2,1]
 * ]
 * 输出: 7
 * 解释: 因为路径 1→3→1→1→1 的总和最小。
 */
#include <vector>
using namespace std;

//明显用dp, 直接在参数上操作, 节省空间
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.empty()) return 0;
        int row = grid.size();
        int col = grid[0].size();
        //初始化第一行
        for (int i = 1; i < col; i++)
            grid[0][i] += grid[0][i-1];
        //初始化第一列
        for (int i = 1; i < row; i++)
            grid[i][0] += grid[i-1][0];
        for (int i = 1; i < row; i++) {
            for (int j = 1; j < col; j++) {
                grid[i][j] += min(grid[i-1][j], grid[i][j-1]);
            }
        }
        return grid[row-1][col-1];
    }
};