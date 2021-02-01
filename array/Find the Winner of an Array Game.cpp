/**
 * Leetcode 1535. 找出数组游戏的赢家
 * 给你一个由 不同 整数组成的整数数组 arr 和一个整数 k 。
 * 每回合游戏都在数组的前两个元素（即 arr[0] 和 arr[1] ）之间进行。
 * 比较 arr[0] 与 arr[1] 的大小，较大的整数将会取得这一回合的胜利并保留在位置 0 ，较小的整数移至数组的末尾。
 * 当一个整数赢得 k 个连续回合时，游戏结束，该整数就是比赛的 赢家 。
 * 返回赢得比赛的整数。
 * 题目数据 保证 游戏存在赢家。
 *
 * 示例 1：
 *  输入：arr = [2,1,3,5,4,6,7], k = 2
 *  输出：5
 *  解释：一起看一下本场游戏每回合的情况：
 *  Round |       arr       | winner | win_count
 *    1   | [2,1,3,5,4,6,7] | 2      | 1
 *    2   | [2,3,5,4,6,7,1] | 3      | 1
 *    3   | [3,5,4,6,7,1,2] | 5      | 1
 *    4   | [5,4,6,7,1,2,3] | 5      | 2
 *  因此将进行 4 回合比赛，其中 5 是赢家，因为它连胜 2 回合。
 * 示例 2：
 *  输入：arr = [1,11,22,33,44,55,66,77,88,99], k = 1000000000
 *  输出：99
 * 
 * 提示：
 *  (1)2 <= arr.length <= 10^5
 *  (2)1 <= arr[i] <= 10^6
 *  (3)arr 所含的整数 各不相同 。
 *  (4)1 <= k <= 10^9
 */
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/* 无论k有多大，胜利者都在arr数组中，通过一次遍历，
 * 如果在碰到数组最大值之前还没有满足条件的胜利者，此时数组最大值来到数组第一位，
 * 那么胜利者就必然是数组最大值。
 */
class Solution {
public:
    int getWinner(vector<int>& arr, int k) {
        int ans = arr[0]; /* 保存数组赢家 */
        int count = 0; /* 连胜次数 */
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] < ans) {
                count++;
            } else {
                count = 1;
                ans = arr[i];
            }
            if (count == k) return ans;
        }
        return ans;
    }
};

/* 手动模拟交换 */
class StupidSolution {
public:
    int getWinner(vector<int>& arr, int k) {
        int maxVal = *max_element(arr.begin(), arr.end());
        /* 如果要求连胜次数大于len-1, 则得胜数字一定是数组最大值 */
        if (k >= arr.size()-1) return maxVal;
        int count = 0; /* 连胜次数 */
        /* 手动模拟 */
        deque<int> q(arr.begin(), arr.end());
        while (true) {
            int first = q.front(); q.pop_front();
            int second = q.front(); q.pop_front();
            if (first > second) {
                count++;
                q.push_front(first);
                q.push_back(second);
            } else {
                count = 1;
                q.push_front(second);
                q.push_back(first);
            }
            if (count == k) return q.front();
        }
    }
};