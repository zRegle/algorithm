/**
 * Leetcode 849. 到最近的人的最大距离
 * 给你一个数组 seats 表示一排座位，其中 seats[i] = 1 代表有人坐在第 i 个座位上，
 * seats[i] = 0 代表座位 i 上是空的（下标从 0 开始）。
 * 至少有一个空座位，且至少有一人已经坐在座位上。
 * 
 * 亚历克斯希望坐在一个能够使他与离他最近的人之间的距离达到最大化的座位上。
 * 返回他到离他最近的人的最大距离。
 * 
 * 示例 1：
 *  输入：seats = [1,0,0,0,1,0,1]
 *  输出：2
 *  解释：如果亚历克斯坐在第二个空位（seats[2]）上，他到离他最近的人的距离为 2 。
 *      如果亚历克斯坐在其它任何一个空位上，他到离他最近的人的距离为 1 。
 *      因此，他到离他最近的人的最大距离是 2 。 
 * 示例 2：
 *  输入：seats = [1,0,0,0]
 *  输出：3
 *  解释：如果亚历克斯坐在最后一个座位上，他离最近的人有 3 个座位远。
 *      这是可能的最大距离，所以答案是 3 。
 * 
 * 示例 3：
 *  输入：seats = [0,1]
 *  输出：1
 * 
 * 提示：
 *  1.2 <= seats.length <= 2 * 104
 *  2.seats[i] 为 0 或 1
 *  3.至少有一个 空座位
 *  4.至少有一个 座位上有人
 */
#include <vector>
#include <climits>
using namespace std;

/**
 * 分三种情况:
 *  1.如果第一个座位为空, 坐到第一个座位
 *    此时到最近的人的距离就是第一个有人坐的座位到开头的距离
 *  2.如果最后一个座位为空, 坐到最后一个座位
 *    此时到最近的人的距离就是第后一个有人坐的座位到结尾的距离
 *  3.坐到相邻两个有人坐的座位的中间
 *
 *  分别判断三种情况即可
 */
class Solution0 {
public:
    int maxDistToClosest(vector<int>& seats) {
        int len = seats.size();
        int prev = 0;
        /* 确定开头有多少个连续的空座位 */
        while (prev < len && seats[prev] != 1)
            prev++;
        int ans = prev; /* 尝试坐到第一个座位 */
        int cur = prev + 1;
        /* prev和cur分别指向相邻的两个有人坐的位置
         * 尝试坐到prev和cur的中间 */
        while (cur < len) {
            /* 从prev+1开始, 找到下一个有人坐的座位 */
            while (cur < len && seats[cur] != 1) cur++;
            /* prev之后的座位都是空的, 退出循环交给后面判断 */
            if (cur == len) break;
            /* 尝试坐到prev和cur中间 */
            ans = max(ans, (cur - prev) / 2);
            prev = cur;
            cur++;
        }
        /* prev到结尾一共有多少个连续的空座位
         * 尝试坐到最后一个座位 */
        ans = max(ans, len - prev - 1);
        return ans;
    }
};

/**
 * 双指针
 * 遍历所有座位 seats，找出每个空位左边最近的人和右边最近的人，更新当前空位到最近的人的距离。
 * 使用 prev 记录 i 最左边第一个有人的位置，future 记录 i 最右边第一个有人的位置。
 * 座位 i 到最近的人的距离为 min(i - prev, future - i)。
 * 另外有一种特殊情况，如果座位 i 左边没有人，则认为到左边第一个人的距离是无限大，右边同理。
 *
 * 时间复杂度:O(N)
 */
class Solution1 {
    int maxDistToClosest(vector<int>& seats) {
        int n = seats.size();
        int prev = -1, future = 0;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (seats[i] == 1)
                prev = i;
            else {
                /* 确定i右边第一个有人坐的位置
                 * i确定好之后, [i, future]这个区间的右边第一个有人坐的位置都确定好了
                 * (future, n)之间的就需要 future < i这个条件重新确定啦 */
                while (future < n && seats[future] == 0 || future < i)
                    future++;
                /* i离左边第一个有人坐的位置的距离 */
                int left = prev == -1 ? INT_MAX : i - prev;
                /* i离右边第一个有人坐的位置的距离 */
                int right = future == n ? INT_MAX : future - i;
                ans = max(ans, min(left, right));
            }
        }
        return ans;
    }
};