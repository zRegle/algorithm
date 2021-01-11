/* 190. 颠倒二进制位
 * 颠倒给定的 32 位无符号整数的二进制位。
 * 示例 1：
 *  输入: 00000010100101000001111010011100
 *  输出: 00111001011110000010100101000000
 * 解释: 输入的二进制串 00000010100101000001111010011100 表示无符号整数 43261596，
 *      因此返回 964176192，其二进制表示形式为 00111001011110000010100101000000。
 */
#include <string>
using namespace std;

/* 我只想到了的这种 */
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        /* num -> bits
         * 注意得到的字符串就是翻转后的字符串
         */
        string bits;
        while (n) {
            bits += (n & 1) + '0';
            n >>= 1;
        }
        int len = bits.length();
        /* bits -> num */
        uint32_t res = 1;
        int start = 0;
        /* 跳过翻转后高位的0 */
        while (bits[start++] == '0');
        for (int i = start; i < len; i++)
            res = (res << 1) + (bits[i] - '0');
        /* 补充翻转后低位的0 */
        for (int i = 0; i < 32 - bits.length(); i++)
            res <<= 1;
        return res;
    }
};

class Solution1 {
public:
    uint32_t reverseBits(uint32_t n) {
        /* 原数字的第i位就是翻转后数字的第32-i位 */
        uint32_t res = 0, power = 31;
        while (n) {
            /* n & 1取原数字的第i位, 然后左移到翻转数字的第32-i位 */
            res += (n & 1) << power;
            n >>= 1;
            power--;
        }
        return res;
    }
};

class Solution2 {
public:
    /* 首先，我们将原来的 32 位分为 2 个 16 位的块, 然后翻转这两个块
     * 然后我们将 16 位块分成 2 个 8 位的块, 翻转这两个块
     * 然后我们继续将这些块分成更小的块，继续翻转, 直到达到 1 位的块。
     * 在上述每个步骤中，我们将中间结果合并为一个整数，作为下一步的输入。
     * 例如: abcdefgh -> efghabcd -> ghefcdab -> hgfedcba 
     */
    uint32_t reverseBits(uint32_t n) {
        n = (n >> 16) | (n << 16);
        n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
        n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
        n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
        n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
        return n;
    }
};