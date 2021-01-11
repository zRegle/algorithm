/* Leetcode 216.组合总和 III
 * 找出所有相加之和为n的k个数的组合。组合中只允许含有1-9的正整数，并且每种组合中不存在重复的数字。
 * 说明：
 *  所有数字都是正整数。
 *  解集不能包含重复的组合。
 * 示例 2:
 *  输入: k = 3, n = 9
 *  输出: [[1,2,6], [1,3,5], [2,3,4]]
 */
#include <vector>
using namespace std;

/* 没啥好说的, 标准的dfs */
class Solution {
public:
    vector<vector<int>> ans;
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> path;
        dfs(1, path, k, n);
        return ans;
    }

    /**
     * @param start 当前dfs深度
     * @param path 当前dfs路径
     * @param k 还需要再找多少个数
     * @param n 剩余多少
     */
    void dfs(int start, vector<int>& path, int k, int n) {
        if (k == 1) {
            if (n <= 9 && n >= start) {
                path.push_back(n);
                ans.push_back(path);
                path.pop_back();
            }
        } else {
            for (int i = start; i <= 9; i++) {
                path.push_back(i);
                dfs(i+1, path, k-1, n-i);
                path.pop_back();
            }
        }
    }
};