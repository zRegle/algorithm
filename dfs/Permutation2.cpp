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
                    /**
                     * 我们要保证在当前深度时, 相同的数字只会被填入一次
                     * 我们对原数组排序后, 保证相同的数字都相邻
                     * 然后规定: 每次填入的数是这个数所在重复数集合中"从左往右第一个未被填过的数字"
                     * 
                     * 如果used[i-1] == false, 表明这个数字不是"从左往右第一个未被填过的数字"
                     * 实际上used[i-1] == false是回溯回来后设置成false的
                     */
                    if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;
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