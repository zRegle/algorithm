/**
 * Leetcode 338. 比特位计数
 * 给定一个非负整数 num。对于 0 ≤ i ≤ num 范围中的每个数字 i ，
 * 计算其二进制数中的 1 的数目并将它们作为数组返回。
 * 示例 1:
 *  输入: 2
 *  输出: [0,1,1]
 * 示例 2:
 *  输入: 5
 *  输出: [0,1,1,2,1,2]
 *
 * 要求:
 *  (1)时间复杂度为O(n*sizeof(int))的解法很简单, 请给出O(n)解法
 *  (2)除了返回结果外, 不允许开辟额外空间
 */
#include <vector>
using namespace std;

/**
 * 动态规划: 求i的"一比特数"时, 如果已经知道j的"一比特数"
 * 那么直接bits[i] = bits[j] + 1即可
 */

/* 方法一 —— 最低有效位置零 */
class Solution0 {
public:
    vector<int> countBits(int num) {
        auto bits = vector<int>(num + 1, 0);
        for (int i = 1; i <= num; i++) {
            bits[i] = bits[i & (i-1)] + 1;
        }
        return bits;
    }
};

/* 方法二 —— 最高有效位
 * 求x的"一比特数"时, 设y = max{y <= x, y是2的整次幂}
 * 即y是x的最高有效位代表的数字, 设z = x - y, 即z为去除x的最高有效位后代表的数字
 * bits[x] = bits[z] + 1 */
class Solution1 {
public:
    vector<int> countBits(int num) {
        auto bits = vector<int>(num + 1, 0);
        int highBit = 0; /* 不断维护当前最高有效位 */
        for (int i = 1; i <= num; i++) {
            if ((i & (i-1)) == 0)
                /* i是2的整次幂 */
                highBit = i;
            bits[i] = bits[i - highBit] + 1;
        }
        return bits;
    }
};

/**
 * 方法三 —— 最低位
 * 对于整数x, 我们将其右移一位, 相当于去除最低位
 * 如果x是偶数, 那么两者的"一比特数"相同
 * 如果x是奇数, 那么两者的"一比特数"相差一
 */
class Solution2 {
public:
    vector<int> countBits(int num) {
        auto bits = vector<int>(num + 1, 0);
        for (int i = 1; i <= num; i++) {
            bits[i] = bits[i >> 1] + (i & 1);
        }
        return bits;
    }
};