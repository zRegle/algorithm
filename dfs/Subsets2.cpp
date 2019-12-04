/* Leetcode 90.子集2
 * 给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
 * 说明：解集不能包含重复的子集。
 * 示例:
 *  输入: [1,2,2]
 *  输出:
 *   [
 *    [2],
 *    [1],
 *    [1,2,2],
 *    [2,2],
 *    [1,2],
 *    []
 *   ]
 */
#include <vector>
#include <algorithm>
using namespace std;

//回溯
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> tmp;
        for (int i = 0; i <= nums.size(); i++)
            dfs(nums, i, tmp, 0);
        return ans;
    }
private:
    vector<vector<int>> ans;
    void dfs(vector<int>& nums, int depth, vector<int>& tmp, int start) {
        if (tmp.size() == depth)
            ans.emplace_back(tmp);
        else {
            for (int i = start; i < nums.size(); i++) {
                //去重
                //i > start是在当前深度下, 我们是从nums中选择一个数字来填写
                //如果nums[i]跟之前一个数字一样, 那么它是重复的, 可以跳过
                if (i > start && nums[i] == nums[i-1]) continue;
                tmp.push_back(nums[i]);
                dfs(nums, depth, tmp, i+1);
                tmp.pop_back();
            }
        }
    }
};