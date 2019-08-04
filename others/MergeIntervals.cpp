/* Leetcode 56 合并区间
 * 给出一个区间的集合，请合并所有重叠的区间。
 * 示例 1
 * 输入: [[1,3],[2,6],[8,10],[15,18]
 * 输出: [[1,6],[8,10],[15,18]
 * 解释: 区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
 */
#include <vector>
#include <algorithm>
using namespace std;

//按区间的最小值排序, 然后比较前后两个区间的最大值
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int size = intervals.size();
        if (size < 2) return intervals;
        auto cmp = [](vector<int>& v1, vector<int>& v2)->bool {
            return v1[0] < v2[0];
        };
        sort(intervals.begin(), intervals.end(), cmp);
        vector<vector<int>> res;
        res.emplace_back(intervals[0]);
        for (int i = 1; i < size; i++) {
            auto cur = res.back();
            if (cur[1] >= intervals[i][0]) {
                res.pop_back();
                cur[1] = max(cur[1], intervals[i][1]);
                res.emplace_back(cur);
            } else {
                res.emplace_back(intervals[i]);
            }
        }
        return res;
    }
};
