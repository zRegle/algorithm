/**
 * Leetcode 363. 矩形区域不超过 K 的最大数值和
 * 给你一个 m x n 的矩阵 matrix 和一个整数 k ，找出并返回矩阵内部矩形区域的不超过 k 的最大数值和。
 * 题目数据保证总会存在一个数值和不超过 k 的矩形区域。
 * 
 * 示例 1：
 *  输入：matrix = [[1,0,1],[0,-2,3]], k = 2
 *  输出：2
 *  解释：矩形区域 [[0, 1], [-2, 3]] 的数值和是 2，
 *       且 2 是不超过 k 的最大数字（k = 2）。
 * 示例 2：
 *  输入：matrix = [[2,2,-1]], k = 3
 *  输出：3
 * 
 * 提示：
 *  (1)m == matrix.length
 *  (2)n == matrix[i].length
 *  (3)1 <= m, n <= 100
 *  (4)-100 <= matrix[i][j] <= 100
 *  (5)-10^5 <= k <= 10^5
 */
#include <vector>
#include <set>
#include <climits>
using std::vector;
using std::set;
using std::max;

/**
 * 与leetcode 1074类似, 先计算每一行的前缀和
 * 然后通过枚举矩阵的左右边界, 在每次枚举的过程中
 * 可以将问题看成leetcode 560类似的过程
 * 本质上是将二维矩阵转化为一维数组求解
 * 
 * 时间复杂度: O(n²mlogm)
 * 优化点: 选取m, n较小的那个去枚举左右边界或者上下边界
 * 最优复杂度: O(min(m,n)²max(m,n)log(max(m,n))
 */
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int m = matrix.size();
        int n = matrix[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 1; j < n; j++) {
                /* 计算每行的前缀和 */
                matrix[i][j] += matrix[i][j-1];
            }
        }
        set<int> set;
        int ans = INT_MIN;
        /* 枚举左右边界 */
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                /* 接下来跟leetcode 560类似 */
                /* 关键, 要先插入0表示没有任何元素相加的情况
                 * 不插入0的话, 第一次调用lower_bound时, 就会返回end()
                 * 此时curSum可能小于k, 就会把curSum漏算了 */
                set.insert(0);
                int curSum = 0;
                for (int idx = 0; idx < m; idx++) {
                    /* [i, j]的和看成一个element */
                    int val = matrix[idx][j] - (i ? matrix[idx][i-1] : 0);
                    curSum += val;
                    /* curSum - k <= it ---> curSum - it <= k
                     * curSum - it就是和不大于k的矩阵 */
                    auto it = set.lower_bound(curSum - k);
                    if (it != set.end())
                        ans = max(ans, curSum - *it);
                    set.insert(curSum);
                }
                set.clear();
            }
        }
        return ans;
    }
};