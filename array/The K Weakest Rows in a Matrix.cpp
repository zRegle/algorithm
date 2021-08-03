/**
 * Leetcode 1337. 矩阵中战斗力最弱的 K 行
 * 给你一个大小为 m * n 的矩阵 mat，矩阵由若干军人和平民组成，分别用 1 和 0 表示。
 * 请你返回矩阵中战斗力最弱的 k 行的索引，按从最弱到最强排序。
 * 如果第 i 行的军人数量少于第 j 行，或者两行军人数量相同但 i 小于 j，
 * 那么我们认为第 i 行的战斗力比第 j 行弱。
 * 军人 总是 排在一行中的靠前位置，也就是说 1 总是出现在 0 之前。
 *
 * 示例 1：
 * 输入：mat =
 *   [[1,1,0,0,0],
 *   [1,1,1,1,0],
 *   [1,0,0,0,0],
 *   [1,1,0,0,0],
 *   [1,1,1,1,1]],
 *   k = 3
 * 输出：[2,0,3]
 * 解释：
 *  每行中的军人数目：
 *  行 0 -> 2
 *  行 1 -> 4
 *  行 2 -> 1
 *  行 3 -> 2
 *  行 4 -> 5
 *  从最弱到最强对这些行排序后得到 [2,0,3,1,4]
 * 示例 2：
 * 输入：mat =
 *  [[1,0,0,0],
 *  [1,1,1,1],
 *  [1,0,0,0],
 *  [1,0,0,0]],
 *  k = 2
 * 输出：[0,2]
 * 解释：
 *  每行中的军人数目：
 *  行 0 -> 1
 *  行 1 -> 4
 *  行 2 -> 1
 *  行 3 -> 1
 *  从最弱到最强对这些行排序后得到 [0,2,3,1]
 *
 * 提示：
 *  (1)m == mat.length
 *  (2)n == mat[i].length
 *  (3)2 <= n, m <= 100
 *  (4)1 <= k <= m
 *  (5)matrix[i][j] 不是 0 就是 1
 */

#include <vector>
#include <queue>
using namespace std;

/**
 * 注意题目条件, 1总是在0之前
 * 因此在确定每行有多少个1时, 可以用二分查找确定
 */
class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        int m = mat.size(), n = mat[0].size();
        /* first = 军人数量, second = 行号 */
        vector<pair<int, int>> power;
        for (int i = 0; i < m; i++) {
            /* 二分查找每行最后一个1 */
            int l = 0, r = n-1, pos = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (mat[i][mid] == 1) {
                    pos = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            power.emplace_back(pos, i);
        }
        /* 大顶堆 */
        priority_queue<pair<int,int>, vector<pair<int,int>>> q;
        for (int i = 0; i < m; i++) {
            /* move: 使pair调用移动构造函数
             * forward: 保持右值引用类型传到函数中 */
            q.push(forward<pair<int,int>&&>(move(power[i])));
            if (q.size() > k)
                q.pop();
        }
        /* 按战斗力从小到大排序, 所以倒序遍历 */
        vector<int> ans(k);
        int i = k-1;
        while (!q.empty()) {
            ans[i--] = q.top().second;
            q.pop();
        }
        return ans;
    }
};