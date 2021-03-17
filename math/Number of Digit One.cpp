/**
 * Leetcode 233. 数字 1 的个数
 * 给定一个整数 n，计算所有小于等于 n 的非负整数中数字 1 出现的个数。
 *
 * 示例 1：
 *  输入：n = 13
 *  输出：6
 *  解释: 1, 10, 11, 12, 13
 *
 * 示例 2：
 *  输入：n = 0
 *  输出：0
 *
 * 提示：0 <= n <= 2 * 109
 */

/* TLE的做法, 遍历1 - n, 对每一个i都统计1出现的次数
 * 假设n有k位, 统计i中1出现的次数是O(logk), 总的时间复杂度是O(nlogk) */
class Trivial {
public:
    int countDigitOne(int n) {
        int cnt = 0;
        for (int i = 1; i <= n; i++)
            cnt += numberOf1(i);
        return cnt;
    }

private:
    inline int numberOf1(int n) {
        int cnt = 0;
        while (n) {
            cnt += (n % 10) == 1;
            n /= 10;
        }
        return cnt;
    }
};

/**
 * 从个位开始, 统计每一位上出现1的数字的总数, 累计求和就是结果
 * 设数字n是一个k位数, n的第i位数字是ni
 * 我们设:
 *  cur: 当前位, 即ni
 *  high: ni左边的数字
 *  low: ni右边的数字
 *  digit: 10^i
 *  例如: n = 12345, 当前位是百位,
 *      cur = 3, high = 12, low = 45, digit = 100
 *
 * 根据cur位值的不同, 分为下面三种情况
 *  (1) cur = 0: 此时1在第i为出现的次数只由high决定, 公式为 high * digit
 *   例如: n = 2304, 求digit = 10(即10位)的1出现次数
 *      10位上出现1的范围: 0010 - 2219
 *      因为十位上1是固定不动的, 因此变化的数字只能是其余3位,
 *      把10位遮住, 剩下能变的就是000 - 229, 229 - 0 + 1 = 230 = high * digit
 *      
 *  (2) cur = 1: 此时1在第i位上出现次数由高位high和低位low决定，计算公式为 high * digit + low + 1
 *   例如: n = 2314, 求 digit = 10（即十位）的 1出现次数。
 *   10位上出现1的范围: 0010 - 2314
 *   同理, 能够变化的就是000 - 234, 234 - 0 + 1 = high * digit + low + 1
 *   
 *  (3) cur = 2,3,...,9, 此时1在第i位上出现次数只由高位high决定，计算公式为：(high + 1) * digit
 *   例如: n = 2324, 求 digit = 10（即十位）的 1出现次数。
 *   10位上出现1的范围是: 0010 - 2319
 *   同理, 能够变化的就是000 - 239, 239 - 0 + 1 = (high + 1) * digit
 *
 * 有了规律就很好求了, 假设n有k位, 只需要log(k)就能求出答案
 *
 * 参考链接:
 * https://leetcode-cn.com/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof/solution/mian-shi-ti-43-1n-zheng-shu-zhong-1-chu-xian-de-2/
 */
class Solution {
public:
    int countDigitOne(int n) {
        /* 从个位开始, 逐步统计每一位1出现的次数 */
        int high = n / 10;
        int cur = n % 10;
        int low = 0;
        int digit = 1;
        int ans = 0;
        /* high为0, 有正在处理最高位
         * cur为0, cur到最高位的都还没处理
         * 当high == 0 && cur == 0, 表示最高位处理完了*/
        while (high != 0 || cur != 0) {
            if (cur == 0)
                ans += high * digit;
            else if (cur == 1)
                ans += high * digit + low + 1;
            else
                ans += (high + 1) * digit;
            low += cur * digit;
            cur = high % 10;
            high /= 10;
            digit *= 10;
        }
        return ans;
    }
};