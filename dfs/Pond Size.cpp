/**
 * 面试题 16.19. 水域大小
 * 你有一个用于表示一片土地的整数矩阵land，该矩阵中每个点的值代表对应地点的海拔高度。
 * 若值为0则表示水域。由垂直、水平或对角连接的水域为池塘。池塘的大小是指相连接的水域的个数。
 * 编写一个方法来计算矩阵中所有池塘的大小，返回值需要从小到大排序。
 * 
 * 示例：
 *  输入：
 *   [[0,2,1,0],
 *   [0,1,0,1],
 *   [1,1,0,1],
 *   [0,1,0,1]]
 *  输出： [1,2,4]
 */
#include <vector>
#include <algorithm>
using namespace std;

/* 常规dfs题目 */
class Solution {
public:
    vector<int> pondSizes(vector<vector<int>>& land) {
        vector<int> ans;
        row = land.size();
        if (row == 0) return ans;
        col = land[0].size();
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (land[i][j] == 0)
                    /* 开始遍历池塘 */
                    ans.push_back(dfs(i, j, land));
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    }

private:
    int row, col;
    /* 对角相连也可以形成池塘, 因此有8个方向 */
    int direction[8][2] = {
            {0,1}, {0,-1}, {1,0}, {-1,0},
            {1,1}, {1,-1}, {-1,1}, {-1,-1}
    };
    int dfs(int x, int y, vector<vector<int>>& land) {
        land[x][y] = -1; //原地修改, 充当visited数组
        int area = 1;
        for (auto& d : direction) {
            int i = x + d[0], j = y + d[1];
            if (isIn(i, j) && land[i][j] == 0) {
                area += dfs(i, j, land);
            }
        }
        return area;
    }
    inline bool isIn(int x, int y) const {
        return x >= 0 && x < row && y >= 0 && y < col;
    }
};