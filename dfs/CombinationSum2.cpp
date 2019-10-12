/* Leetcode 40.组合总和2
 * 给定一个数组 candidates(允许有重复的数字)和一个目标数target, 找出candidates中所有可以使数字和为target的组合。
 * candidates中的每个数字在每个组合中只能使用一次。
 * 示例:
 * 输入: candidates = [10,1,2,7,6,1,5], target = 8,
 * 所求解集为:
 * [
 *  [1, 7],
 *  [1, 2, 5],
 *  [2, 6],
 *  [1, 1, 6]
 * ]
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        if (candidates.empty()) return ans;
        vector<int> tmp;
        sort(candidates.begin(), candidates.end());
        findCombination(candidates, target, tmp, 0, 0);
        return ans;
    }
private:
    vector<vector<int>> ans;
    void findCombination(vector<int>& candidates, int target, vector<int>& tmp, int sum, int idx) {
        if (sum > target)
            return;
        else if (sum == target)
            ans.push_back(tmp);
        else {
            for (int i = idx; i < candidates.size(); i++) {
                //idx是递归的深度, i是当前层从左往右节点的标号
                //在当前的递归深度下, 如果相邻的两个节点的值一样, 那么这两棵子树肯定一样, 所以我们只需要跳过就行
                if (i > idx && candidates[i] == candidates[i-1]) continue;
                tmp.push_back(candidates[i]);
                findCombination(candidates, target, tmp, sum+candidates[i], i + 1); //只能用一次, 所以i+1
                tmp.pop_back();
            }
        }
    }
};