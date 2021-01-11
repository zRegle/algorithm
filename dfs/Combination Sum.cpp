/* Leetcode 39.组合总和
 * 给定一个无重复元素的数组candidates和一个目标数target, 找出candidates中所有可以使数字和为target的组合.
 * candidates 中的数字可以无限制重复被选取
 * 示例:
 * 输入:candidates = [2,3,5], target = 8
 * 所求解集为:
 * [
 *   [2,2,2,2],
 *   [2,3,3],
 *   [3,5]
 * ]
 */
#include <vector>
using namespace std;

//明显要用dfs, 然后回溯
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        if (candidates.empty()) return ans;
        vector<int> tmp;
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
                tmp.push_back(candidates[i]);
                findCombination(candidates, target, tmp, sum+candidates[i], i); //从i重新开始, 因为一个数字可以被重复使用
                tmp.pop_back();
            }
        }
    }
};