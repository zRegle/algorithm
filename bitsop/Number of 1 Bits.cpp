/* Leetcode 191.位1的个数
 * 编写一个函数，输入是一个无符号整数，返回其二进制表达式中数字位数为'1'的个数（也被称为汉明重量）。
 */
#include <iostream>
using namespace std;

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int cnt = 0;
        while (n) {
            cnt += n & 1;
            n >>= 1;
        }
        return cnt;
    }
};

/* n & (n-1) 总是能把n的最低的1置为0
 * 假设n是奇数, 那么最低位的比特为1, n-1是偶数, 最低位为0, 满足结论
 * 假设n是偶数, 例如10100, n-1为10011, 相与也满足结论
 */
class Solution1 {
public:
    int hammingWeight(uint32_t n) {
        int cnt = 0;
        while (n) {
            cnt++;
            n &= (n-1);
        }
        return cnt;
    }
};