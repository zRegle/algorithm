/* Leetcode 47 全排列2
 * 给定一个可包含重复数字的序列，返回所有不重复的全排列。
 * 示例
 * 输入: [1,1,2]
 * 输出
 * [
 *  [1,1,2],
 *  [1,2,1],
 *  [2,1,1]
 * ]
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end()); //首先排序, 这样相同数字就会紧挨在一起
        vector<bool> used(nums.size(), false);  //标记数组
        vector<int> tmp;
        permute(nums, tmp, used);
        return res;
    }

    void permute(vector<int>& nums, vector<int>& tmp, vector<bool>& used) {
        int size = nums.size();
        if (tmp.size() == size) {
            res.emplace_back(vector<int>(tmp));
        } else {
            for (int i = 0; i < size; i++) {
                if (!used[i]) { //这个位置的数字还没被使用
                    //这个数字是重复数字, 且它前面的数字已经被使用过了
                    if (i > 0 && nums[i] == nums[i-1] && used[i-1]) continue;
                    tmp.push_back(nums[i]);
                    used[i] = true;
                    permute(nums, tmp, used);
                    tmp.pop_back();
                    used[i] = false;
                }
            }
        }
    }
};