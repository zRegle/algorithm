#include <vector>
using namespace std;

/* dfs版本, 思路基本一致, 详细解释参考dp版本
 * dfs(i, j)表示从(i, j)出发到达终点所需要的最小HP
 * minHp二维数组用来记忆化搜索
 */
class Solution1 {
    int row, col;
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        row = dungeon.size();
        if (row <= 0) return 1;
        col = dungeon[0].size();
        vector<vector<int>> minHp(row, vector<int>(col, -1));
        return dfs(0, 0, minHp, dungeon);
    }

    int dfs(int i, int j, vector<vector<int>>& minHp, vector<vector<int>>& dungeon) {
        if (minHp[i][j] != -1)
            return minHp[i][j];
        int right, down, tmp;
        if (i == row-1 && j == col-1) {
            minHp[i][j] = dungeon[i][j] >= 0 ? 1 : 1-dungeon[i][j];
        } else if (i == row-1) {
            right = dfs(i, j+1, minHp, dungeon);
            minHp[i][j] = dungeon[i][j] >= right ? 1 : right-dungeon[i][j];
        } else if (j == col-1) {
            down = dfs(i+1, j, minHp, dungeon);
            minHp[i][j] = dungeon[i][j] >= down ? 1 : down-dungeon[i][j];
        } else {
            tmp = dfs(i, j+1, minHp, dungeon);
            right = dungeon[i][j] >= tmp ? 1 : tmp-dungeon[i][j];
            tmp = dfs(i+1, j, minHp, dungeon);
            down = dungeon[i][j] >= tmp ? 1 : tmp-dungeon[i][j];
            minHp[i][j] = min(right, down);
        }
        return minHp[i][j];
    }
};