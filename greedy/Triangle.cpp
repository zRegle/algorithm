#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/**
 * leetcode 120 Triangle
 * 给定一个三角形, 求从顶到底的最短路径之和, 每一步只能走到下一行相邻的数字
 * 例如:
 *    2
 *   3,4
 *  6,5,7
 * 4,5,6,3
 * 输出: 2+3+5+5=15
 *
 * 思路: 用贪心算法解决即可, 两个数组, 一个数组保存上一行的结果, 一个用来处理当前行的结果
 * 上面那个例子, 整理一下就变成
 * 2
 * 3,4
 * 6,5,7
 * 4,5,6,3
 * 在处理(i, j)时候, 只能从(i-1, j-1)或者(i-1, j)走过来, 我们每次都取较小的, 然后注意一下边界条件即可
 */ 

class Solution {
    int minimumTotal(vector<vector>>& triangle) {
        int row = triangle.size();
        if (!row) return 0;
        auto first = triangle[0];
        if (!first.size()) return 0;
        vector<int> prev(first);
        vector<int> cur(first.size()+1, 0);
        for (int i = 1; i < row; i++) {
            int prev_size = triangle[i-1].size();
            int cur_size = triangle[i].size();
            for (int j = 0; j < cur_size; j++) {
                int prev_left = j-1 >= 0 ? prev[j-1] : prev[j];
                int prev_right = j < prev_size ? prev[j] : prev[j-1];
                cur[j] = min(prev_left, prev_right) + triangle[i][j];
            }
            prev.clear(); prev.swap(cur);
            cur.resize(cur_size+1);
        }
        int minSum = INT_MAX;
        for (int sum : prev) minSum = min(minSum, sum);
        return minSum;
    }
};
