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

/**
 * 改进版: 求路径
 */
 class Solution2 {
     vector<int> minimumTotal(vector<vector<int>>& triangle) {
        int row = triangle.size();
        if (!row) {
            vector<int> v;
            return v;
        }
        auto first = triangle[0];
        if (!first.size()) {
            vector<int> v;
            return v;
        }
        //上一行的最短路径, 这一行的最短路径
        vector<vector<int>> prev_path, cur_path;
        prev_path.emplace_back(first);
        for (int i = 0; i < row; i++) {
            auto prev_value = triangle[i-1];    //上一行的原始数值
            auto cur_value = triangle[i];   //当前行的数值
            int cur_size = cur_value.size();
            int prev_size = prev_value.size();
            for (int j = 0; j < cur_size; j++) {
                int prev_left = j-1 >= 0 ? j-1 : j; //获取下标
                int prev_right = j < prev_size ? j : j-1;   //获取下标   
                vector<int> new_path;   //新的路径
                //比较, 然后拷贝一份
                if (prev_value[prev_left] < prev_value[prev_right]) {
                    new_path.swap(prev_path[prev_left]);
                } else {
                    new_path.swap(prev_path[prev_right]);
                }
                //新路径加入当前的格子的数值
                new_path.push_back(cur_value[j]);
                //添加新路径
                cur_path.push_back(new_path);
            }
            prev_path.clear(); prev_path.swap(cur_path);
            cur_path.resize(cur_size+1);
        }
        //各路径求和, 返回最小值
        int minSum = INT_MAX, minIndex = -1;
        for (int i = 0; i < prev_path.size(); i++) {
            int sum = 0;
            for (auto num : prev_path[j]) sum += num;
            if (sum < minSum) {
                minSum = sum;
                minIndex = i;
            }
        }
        return prev_path[minIndex];
     }
 }
