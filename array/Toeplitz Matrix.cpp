/**
 * ;eetcode 766. 托普利茨矩阵
 * 给你一个 m x n 的矩阵 matrix 。如果这个矩阵是托普利茨矩阵，返回 true ；否则，返回 false 。
 * 如果矩阵上每一条由左上到右下的对角线上的元素都相同，那么这个矩阵是 托普利茨矩阵 。
 *  
 * 示例 1：
 *  输入：matrix = [[1,2,3,4],[5,1,2,3],[9,5,1,2]]
 *  输出：true
 *  解释：
 *   在上述矩阵中, 其对角线为: 
 *   "[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]"。 
 *   各条对角线上的所有元素均相同, 因此答案是 True 。
 * 示例 2：
 *  输入：matrix = [[1,2],[2,2]]
 *  输出：false
 *  解释：
 *  对角线 "[1, 2]" 上的元素不同。
 *  
 * 提示：
 *  (1)m == matrix.length
 *  (2)n == matrix[i].length
 *  (3)1 <= m, n <= 20
 *  (4)0 <= matrix[i][j] <= 99
 *  
 * 进阶：
 * (1)如果矩阵存储在磁盘上，并且内存有限，以至于一次最多只能将矩阵的一行加载到内存中，该怎么办？
 * (2)如果矩阵太大，以至于一次只能将不完整的一行加载到内存中，该怎么办？
 */
#include <vector>
using std::vector;

class Solution0 {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        m = matrix.size();
        n = matrix[0].size();
        /* 首先检查第一行 */
        for (int i = 0; i < n; i++) {
            int x = 0, y = i;
            if (!check(x, y, matrix))
                return false;
        }
        /* 再检查第一列 */
        for (int j = 1; j < m; j++) {
            int x = j, y = 0;
            if (!check(x, y, matrix))
                return false;
        }
        return true;
    }

private:
    int m, n;
    /* 检查[x, y]开始的对角线 */
    bool check(int x, int y, vector<vector<int>>& matrix) {
        int cur, prev = matrix[x][y];
        while (x < m && y < n) {
            cur = matrix[x][y];
            if (cur != prev)
                return false;
            prev = cur;
            x++; y++;
        }
        return true;
    }
};

/* 更加优雅的做法, 每个元素检查跟它左上角的格子是否相等 */
class Solution1 {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] != matrix[i-1][j-1])
                    return false;
            }
        }
        return true;
    }
};