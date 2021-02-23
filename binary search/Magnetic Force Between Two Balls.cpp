/**
 * Leetcode 1552. 两球之间的磁力
 * 在代号为 C-137 的地球上，Rick 发现如果他将两个球放在他新发明的篮子里，它们之间会形成特殊形式的磁力。
 * Rick 有 n 个空的篮子，第 i 个篮子的位置在 position[i] ，
 * Morty 想把 m 个球放到这些篮子里，使得任意两球间 最小磁力 最大。
 *
 * 已知两个球如果分别位于 x 和 y ，那么它们之间的磁力为 |x - y| 。
 * 给你一个整数数组 position 和一个整数 m ，请你返回最大化的最小磁力。
 *
 * 示例 1：
 *  输入：position = [1,2,3,4,7], m = 3
 *  输出：3
 * 解释：将 3 个球分别放入位于 1，4 和 7 的三个篮子，两球间的磁力分别为 [3, 3, 6]。
 *     最小磁力为 3 。我们没办法让最小磁力大于 3 。
 * 示例 2：
 *  输入：position = [5,4,3,2,1,1000000000], m = 2
 *  输出：999999999
 *  解释：我们使用位于 1 和 1000000000 的篮子时最小磁力最大。
 *
 * 提示：
 *  (1)n == position.length
 *  (2)2 <= n <= 10^5
 *  (3)1 <= position[i] <= 10^9
 *  (4)所有 position 中的整数 互不相同 。
 *  (5)2 <= m <= position.length
 */
#include <climits>
#include <vector>
#include <algorithm>
using std::vector;

/**
 * 典型的最大化最小值问题, 用二分法:
 * 此类题目的答案都有一个确定的范围, 我们不断在这个范围里二分
 * 用一个函数来检验当前二分的值是否符合要求, 如果是, 则继续二分
 * 返回最后一个符合题意的值, 即为答案
 */

class Solution {
public:
    int maxDistance(vector<int>& position, int m) {
        sort(position.begin(), position.end());
        int left = 1, right = position.back() - position[0];
        int ans = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (judge(position, m, mid)) {
                ans = mid; /* mid可能就是答案, 先保存下来 */
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return ans;
    }

private:
    /**
     * 判断distance是否满足要求
     * @param position 篮子数组
     * @param m 球的个数
     * @param distance 相邻两个球的距离
     * @return true or false
     */
    bool judge(vector<int>& position, int m, int distance) {
        int prev = INT_MIN; /* 前一个球的位置 */
        for (int pos : position) {
            if (m == 0) break; /* 全部球放置完毕, 返回true */
            if (pos >= prev + distance) {
                /* 当前位置与前一个球的位置的距离大于等于distance
                 * 当前位置可以放一个球
                 */
                prev = pos;
                m--;
            }
        }
        return m == 0;
    }
};