/**
 * Leetcode 1074. 元素和为目标值的子矩阵数量
 * 给出矩阵 matrix 和目标值 target，返回元素总和等于目标值的非空子矩阵的数量。
 * 子矩阵 x1, y1, x2, y2 是满足 x1 <= x <= x2 且 y1 <= y <= y2 的所有单元 matrix[x][y] 的集合。
 * 如果 (x1, y1, x2, y2) 和 (x1', y1', x2', y2') 两个子矩阵中部分坐标不同（如：x1 != x1'），
 * 那么这两个子矩阵也不同。
 *
 * 示例 1：
 * 输入：matrix = [[0,1,0],
 *                [1,1,1],
 *                [0,1,0]],
 *      target = 0
 *  输出：4
 *  解释：四个只含 0 的 1x1 子矩阵。
 * 示例 2：
 *
 * 输入：matrix = [[1,-1],
 *                [-1,1]],
 *      target = 0
 * 输出：5
 * 解释：两个 1x2 子矩阵，加上两个 2x1 子矩阵，再加上一个 2x2 子矩阵。
 *
 * 提示：
 *  (1)1 <= matrix.length <= 300
 *  (2)1 <= matrix[0].length <= 300
 *  (3)-1000 <= matrix[i] <= 1000
 *  (4)-10^8 <= target <= 10^8
 */
#include <vector>
#include <unordered_map>
using std::vector;
using std::unordered_map;

/* 参考 leetcode 560 Subarray Sum Equals K 的思路
 * 1.首先计算每一行的前缀和
 * 2.接着对于任意两列i, j, 满足(i <= j), 我们来考察这两列"夹"住的子矩阵
 *    (1)"夹"住的子矩阵有很多行, 将每一行的所有元素之和看成一个element
 *    (2)这样这个子矩阵就转化成一维的element数组
 *    (3)问题就转化为leetcode 560 和为K的子数组
 */
class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        auto& preSum = matrix; /* 就地更改, 把matrix变成前缀和 */
        /* 计算每一行的前缀和 */
        for (int i = 0; i < m; i++) {
            for (int j = 1; j < n; j++) {
                preSum[i][j] = preSum[i][j-1] + matrix[i][j];
            }
        }
        int ans = 0;
        unordered_map<int, int> map;
        /* 滑动窗口, 可以枚举任意两列 */
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                /* 模仿leetcode 560的思路, 求和为K的子数组 */
                map = {{0, 1}}; /* 清空map */
                int sum = 0;
                for (int k = 0; k < m; k++) {
                    /* 利用之前计算好的每一行的前缀和
                     * preSum[k][j] - preSum[k][i-1]就得出 从(k, i)到(k, j)之和 */
                    sum += preSum[k][j] - (i > 0 ? preSum[k][i - 1] : 0);
                    if (map.find(sum - target) != map.end())
                        ans += map[sum - target];
                    map[sum]++;
                }
            }
        }
        /* 时间复杂度O(MN²) */
        return ans;
    }
};