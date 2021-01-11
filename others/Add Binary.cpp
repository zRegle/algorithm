/* Leetcode 67 二进制就和
 * 给定两个二进制字符串，返回他们的和（用二进制表示）。
 * 输入为非空字符串且只包含数字1和0。
 * 示例 1:
 * 输入: a = "11", b = "1"
 * 输出: "100"
 */

#include <iostream>
using namespace std;

//就是简单模拟加法, 直接在较长的字符串上操作, 节省空间
class Solution {
public:
    string addBinary(string a, string b) {
        if (a.empty()) return b;
        if (b.empty()) return a;
        //确保a的长度比b的短
        if (a.size() > b.size())
            swap(a, b);
        int l1 = a.size(), l2 = b.size();
        int i, j, carry = 0; //carry表示有没有进位
        for (i = l1-1, j = l2-1; i >= 0; i--, j--) {
            int c1 = a[i] - '0', c2 = b[j] - '0';
            int res = c1 + c2 + carry;
            b[j] = (res % 2) + '0';
            carry = res / 2;
        }
        for (; j >= 0; j--) {
            int c2 = b[j] - '0';
            int res = c2 + carry;
            b[j] = (res % 2) + '0';
            carry = res / 2;
        }
        if (carry) b.insert(b.begin(), '1');
        return b;
    }
};