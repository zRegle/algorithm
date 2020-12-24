/* Leetcode 221.最大正方形
 * 在一个由0和1组成的二维矩阵内，找到只包含1的最大正方形，并返回其面积。
 * 示例:
 *  输入:
 *  1 0 1 0 0
 *  1 0 1 1 1
 *  1 1 1 1 1
 *  1 0 0 1 0
 *  输出: 4
 */
#include <vector>
using namespace std;

/* dp[i][j]表示以当前格子为右下端点的最大正方形边长
 * 这是优化过空间复杂度的版本
 */
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int row = matrix.size();
        if (row == 0) return 0;
        int col = matrix[0].size();
        vector<int> pre(col, 0); /* 上一行的值 */
        vector<int> cur(col, 0); /* 当前行的值 */
        int max_length = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (matrix[i][j] == '0')
                    cur[j] = 0;
                else {
                    if (i == 0 || j == 0)
                        cur[j] = 1;
                    else
                        /* 左、上、左上角三者取最小值加一
                         * 左、上取最小值是看当前格子能够延伸的最远长度
                         * 左上角是确保是个正方形, 例如:
                         * 左、上的值都是1, 但左上角是0, 此时只取左、上的最小值加一就出错了
                         */
                        cur[j] = min(min(cur[j-1], pre[j]), pre[j-1]) + 1;
                }
                max_length = max(cur[j], max_length);
            }
            /* 更新上一行的值 */
            pre.assign(cur.begin(), cur.end());
        }
        return max_length * max_length;
    }
};

/* my solution
 * 这个可以只用一个一维数组解决
 * 因为没用到左上角的值, 不过效率比较低
 */
class Solution1 {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int row = matrix.size();
        if (row == 0) return 0;
        int col = matrix[0].size();
        vector<vector<int>> dp(row, vector<int>(col, 0));
        int max_length = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (matrix[i][j] == '0')
                    dp[i][j] = 0;
                else {
                    if (i > 0 && j > 0) {
                        /* 以左上角格子为右下端点的正方形边长 */
                        int length = dp[i-1][j-1];
                        if (length == 0) {
                            dp[i][j] = 1;
                        } else {
                            int expand_length = 0;
                            /* 当前格子向左、向上延伸, 延伸长度不超过Length
                             * 因为就算超过了length, 也形成不了正方形
                             */
                            for (int cnt = 1; cnt <= length; cnt++) {
                                if (matrix[i][j-cnt] == '1' && matrix[i-cnt][j] == '1')
                                    expand_length++;
                                else
                                    break;
                            }
                            /* 当前格子能够形成的正方形边长和length取较小值 */
                            dp[i][j] = min(length, expand_length) + 1;
                        }
                    } else {
                        dp[i][j] = 1;
                    }
                }
                max_length = max(max_length, dp[i][j]);
            }
        }
        return max_length * max_length;
    }
};