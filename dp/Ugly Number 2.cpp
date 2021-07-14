/* Leetcode 264.丑数 II
 * 编写一个程序，找出第 n 个丑数。
 * 丑数就是质因数只包含 2, 3, 5 的正整数。
 * 示例:
 *  输入: n = 10
 *  输出: 12
 *  解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。
 *
 */
#include <vector>
#include <set>
using namespace std;

/* 优先级队列方法查看other文件夹 */

/* 丑数只能是丑数 x 丑数得到 */

/* 动态规划
 * 类似于合并排序链表, 有3条链表
 *  (1)丑数 * 2得到的序列
 *  (2)丑数 * 3得到的序列
 *  (3)丑数 * 5得到的序列
 * 每次比较三条链, 取最小的元素放到结果链中即可
 * 唯一要注意的是, 如果有多个最小值时, 都要把元素取出, 不然下一次循环就会出现重复元素
 */
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(1690, 0);
        dp[0] = 1;
        int p2, p3, p5;
        p2 = p3 = p5 = 0; /* 对应3条链的指针 */
        for (int i = 1; i < n; i++) {
            /* 三个指针对应的丑数乘以各自的因子, 取最小值 */
            dp[i] = min(min(2 * dp[p2], 3 * dp[p3]), 5 * dp[p5]);
            if (dp[i] == 2 * dp[p2])
                p2++;
            if (dp[i] == 3 * dp[p3])
                p3++;
            if (dp[i] == 5 * dp[p5])
                p5++;
        }
        return dp[n-1];
    }
};