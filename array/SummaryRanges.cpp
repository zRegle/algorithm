/* Leetcode 228.汇总区间
 * 给定一个无重复元素的有序整数数组，返回数组区间范围的汇总。
 * 示例:
 *  输入: [0,1,2,4,5,7]
 *  输出: ["0->2","4->5","7"]
 *  解释: 0,1,2 可组成一个连续的区间; 4,5 可组成一个连续的区间。
 */
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> ans;
        int n = nums.size();
        string s;
        for (int i = 0; i < n; i++) {
            s = to_string(nums[i]);
            int start = i;
            while (i < n-1 && (long)nums[i+1] - nums[i] == 1) i++;
            if (start != i)
                s += "->" + to_string(nums[i]);
            ans.push_back(s);
        }
        return ans;
    }
};

class MySolution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> ans;
        int n = nums.size();
        if (n == 0) return ans;
        string s = to_string(nums[0]);
        bool consecutive = false;
        for (int i = 1; i < n; i++) {
            /* 转成long防止溢出 */
            if ((long)nums[i] - nums[i-1] == 1) {
                if (!consecutive) {
                    /* 之前没有连续的区间, 现在有了, 设置"->" */
                    consecutive = true;
                    s += "->";
                }
            } else {
                /* nums[i]与nums[i-1]不连续 */
                if (consecutive) {
                    /* 之前有连续的区间, 设置该区间的右边界 */
                    consecutive = false;
                    s += to_string(nums[i-1]);
                }
                /* 添加上一个连续的区间 */
                ans.push_back(s);
                /* 设置下一个区间的左边界 */
                s = to_string(nums[i]);
            }
        }
        /* 处理剩余元素 */
        if (!consecutive)
            /* 上个区间不连续, 不需要设置上个区间的右边界, 直接clear */
            s.clear();
        /* 这里可以是设置上个区间的右边界, 也可以是单独最后一个数字做一个区间 */
        s += to_string(nums.back());
        ans.push_back(s);
        return ans;
    }
};