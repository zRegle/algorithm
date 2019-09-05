/* Leetcode 78.子集
 * 给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
 * 说明：解集不能包含重复的子集。
 * 示例:
 * 输入: nums = [1,2,3]
 * 输出:
 * [
 *   [3],
 *   [1],
 *   [2],
 *   [1,2,3],
 *   [1,3],
 *   [2,3],
 *   [1,2],
 *   []
 * ]
 */
#include <vector>
#include <iostream>
using namespace std;

//没啥好说的, 全排列的变种
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> tmp;
        for (int i = 0; i <= nums.size(); i++)
            dfs(i, 0, ans, tmp, nums);
        return ans;
    }

    void dfs(int k, int cnt, vector<vector<int>>& ans, vector<int>& tmp, vector<int>& nums) {
        if (tmp.size() == k)
            ans.emplace_back(tmp);
        else {
            for (int i = cnt; i < nums.size(); i++) {
                tmp.push_back(nums[i]);
                dfs(k, i+1, ans, tmp, nums);
                tmp.pop_back();
            }
        }
    }
};