/* Leetcode 201.数字范围按位与
 * 给定范围 [m, n]，其中 0 <= m <= n <= 2147483647，返回此范围内所有数字的按位与（包含 m, n 两端点）。
 * 暴力解法会TLE
 * 两个数字按位与其实就是保留了两个数字的公共前缀
 */

/* 借鉴Leetcode 191的思路
 * n & (n-1) 会把n最低位的1置零, 设结果为n'
 * 若m < n‘, 证明n'还不是公共前缀, n'的最低位1还需要置零, 继续循环
 * 若m >= n', 那么n'就是公共前缀
 */
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        while (m < n)
            n &= (n-1);
        return n;
    }
};

/* 找两个数的公共前缀, 只需要不断右移直到两个数相等
 * 然后再左移相应的位数即可
 */
class Solution1 {
public:
    int rangeBitwiseAnd(int m, int n) {
        int shift = 0;
        while (m != n) {
            m >>= 1;
            n >>= 1;
            shift++;
        }
        return m << shift;
    }
};