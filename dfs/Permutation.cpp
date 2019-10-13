/* Leetcode 46 全排列
 * 给定一个没有重复数字的序列，返回其所有可能的全排列。
 * 示例
 * 输入: [1,2,3]
 * 输出
 *  [
 *  [1,2,3],
 *  [1,3,2],
 *  [2,1,3],
 *  [2,3,1],
 *  [3,1,2],
 *  [3,2,1]
 *  ]
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> permute(vector<int>& nums) {
        Permute(nums, 0);
        return res;
    }

    void swap(vector<int>& nums, int i, int j) {
        int tmp = nums[j];
        nums[j] = nums[i];
        nums[i] = tmp;
    }

    void Permute(vector<int>& nums, int cnt) {
        int size = nums.size();
        if (cnt == size-1) {
            res.push_back(nums);
        } else {
            for (int i = cnt; i < size; i++) {
                swap(nums, i, cnt);
                Permute(nums, cnt+1);
                swap(nums, cnt, i);
            }
        }
    }

    void backtrack(vector<int>& nums, vector<int>& tmp) {
        if (tmp.size() == nums.size()) {
            for (int a : tmp)
                cout<<a<<" ";
            cout<<endl;
        } else {
            for (int i = 0; i < nums.size(); i++) {
                if (find(tmp.begin(), tmp.end(), nums[i]) == tmp.end()) {
                    tmp.push_back(nums[i]);
                    backtrack(nums, tmp);   //dfs
                    tmp.erase(tmp.end()-1); //这一层不放这个数字, 把这个数字删掉
                }
            }
        }
    }
};

