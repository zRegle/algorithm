/* Leetcode 263.丑数
 * 编写一个程序判断给定的数是否为丑数。
 * 丑数就是只包含质因数 2, 3, 5 的正整数.
 * 示例 1:
 *  输入: 6
 *  输出: true
 *  解释: 6 = 2 × 3
 * 示例 2:
 *  输入: 14
 *  输出: false 
 *  解释: 14 不是丑数，因为它包含了另外一个质因数 7。
 * 
 * 说明: 1是丑数
 */

class Solution {
public:
    bool isUgly(int num) {
        if (num == 0) return false;
        while (true) {
            if (num == 1) 
                return true;
            else if (num % 5 == 0)
                num /= 5;
            else if (num % 3 == 0)
                num /= 3;
            else if ((num & 1) == 0)
                num >>= 1;
            else
                return false;
        }
    }
};