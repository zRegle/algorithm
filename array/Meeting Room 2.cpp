/**
 * Leectcode 253. 会议室 II
 * 给你一个会议时间安排的数组 intervals ，
 * 每个会议时间都会包括开始和结束的时间 intervals[i] = [starti, endi] ，
 * 为避免会议冲突，同时要考虑充分利用会议室资源，请你计算至少需要多少间会议室，才能满足这些会议安排。
 * 
 * 示例 1：
 *  输入：intervals = [[0,30],[5,10],[15,20]]
 *  输出：2
 * 示例 2：
 *  输入：intervals = [[7,10],[2,4]]
 *  输出：1
 */
#include <vector>
#include <algorithm>
using namespace std;

/**
 * 思路:
 * 可以转化为上下车问题, 会议开始看做有人上车, 会议结束看做有人下车
 * 求车上最多同时有多少人
 * 
 * 将上车下车的时间分成两组, 然后双指针遍历即可
 */

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int n = intervals.size();
        /* 会议开始时间和结束时间分为两组 */
        vector<int> start, finish;
        for (auto& meeting : intervals) {
            start.push_back(meeting[0]);
            finish.push_back(meeting[1]);
        }
        /* 各自排序 */
        sort(start.begin(), start.end());
        sort(finish.begin(), finish.end());
        int ans = 0; /* 会议室最多同时有多少个会议进行 */
        int cnt = 0; /* 会议室当前有多少个会议进行 */
        /* 双指针同时遍历 */
        int i = 0, j = 0;
        while (i < n && j < n) {
            if (start[i] < finish[j]) {
                i++;
                cnt++;
            } else {
                j++;
                cnt--;
            }
            ans = max(cnt, ans);
        }
        return ans;
    }
};