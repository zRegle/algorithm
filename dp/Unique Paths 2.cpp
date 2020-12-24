/* Leetcode 63 不同路径2
 * 一个机器人位于一个 m x n 网格的左上角。
 * 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角。
 * 现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？
 * 网格中的障碍物和空位置分别用1和0来表示。
 */
#include <vector>
using std::vector;

//直接在参数obstacleGrid上操作, 不需要额外空间
//时间复杂度O(mn), 空间复杂度O(1)
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        if (obstacleGrid.empty() || obstacleGrid[0][0]) return 0;
        int r = obstacleGrid.size();
        int c = obstacleGrid[0].size();
        obstacleGrid[0][0] = 1;
        //初始化第一列, obstacleGrid[i-1][0] == 1表示上一行的同一个格子可以到达, 下同
        for (int i = 1; i < r; i++)
            obstacleGrid[i][0] = (!obstacleGrid[i][0] && obstacleGrid[i-1][0]) ? 1 : 0;
        //初始化第一行
        for (int i = 1; i < c; i++)
            obstacleGrid[0][i] = (!obstacleGrid[0][i] && obstacleGrid[0][i-1]) ? 1 : 0;
        for (int i = 1; i < r; i++) {
            for (int j = 1; j < c; j++) {
                if (!obstacleGrid[i][j])
                    obstacleGrid[i][j] = obstacleGrid[i-1][j] + obstacleGrid[i][j-1];
                else
                    obstacleGrid[i][j] = 0;
            }
        }
        return obstacleGrid[r-1][c-1];
    }
};

