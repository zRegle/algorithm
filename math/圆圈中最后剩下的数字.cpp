/**
 * 剑指 Offer 圆圈中最后剩下的数字
 * 0,1,···,n-1这n个数字排成一个圆圈，从数字0开始，
 * 每次从这个圆圈里删除第m个数字（删除后从下一个数字开始计数）。
 * 求出这个圆圈里剩下的最后一个数字。
 *
 * 例如，0、1、2、3、4这5个数字组成一个圆圈，从数字0开始每次删除第3个数字，
 * 则删除的前4个数字依次是2、0、4、1，因此最后剩下的数字是3。
 *
 * 示例 1：
 *  输入: n = 5, m = 3
 *  输出: 3
 * 示例 2：
 *  输入: n = 10, m = 17
 *  输出: 2
 *
 * 限制：
 *  (1)1 <= n <= 10^5
 *  (2)1 <= m <= 10^6
 *  (3)数组的数取值为 [0, 13] .
 */

/* 约瑟夫环问题
 * dp[i]: i个元素围成一圈, 删除圆圈里第m个数字的最后剩下的数字
 * 递推关系: dp[i] = (dp[i-1] + m) % i
 * 详情参考链接:
 * https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/solution/jian-zhi-offer-62-yuan-quan-zhong-zui-ho-dcow/ */
class Solution {
public:
    int lastRemaining(int n, int m) {
        int cur = 0; /* f(1, m)的答案 */
        for (int i = 2; i <= n; i++)
            cur = (cur + m) % i;
        return cur;
    }
};