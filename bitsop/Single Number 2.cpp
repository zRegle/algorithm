/* Leetcode 137.只出现一次的数字 II
 * 给定一个非空数组, 每一个元素都出现了3次, 只有一个元素出现了一次, 找到这个数字
 */
#include <vector>
using namespace std;


/* 1.我们来考虑更一般的情况:
 *  一个数组里所有数字都出现了k次, 只有一个数字只出现一次, 找到这个数字 A
 *  我们可以设计一个counter, 来记录这个数组中所有数字的各个bit出现1的次数.
 *  这个counter需要满足以下性质:
 *   (1)遇到1要加一
 *   (2)遇到0要保持不变
 *   (3)达到k要归零
 *  设这个counter的二进制形式为xm,xm-1,...xi,...,x1,x0
 * 
 * 2.为了满足性质(2), 我们有两个选择, xi |= bit 或者 xi ^= bit
 *  如果我们选择xi |= bit, 假设xi和bit都为1, 那么xi需要归0并且向下一位进1
 *  但是xi |= 1还是1. 因此不满足我们的需求, 所以选择xi ^= bit
 * 
 * 3.为了满足性质(1), 我们还需要考虑进位情况.一般地, xi在什么情况下才会从0变成1?
 *  很明显, 当且仅当xi-1 & ... & x1 & x0 & bit = 1的时候, xi才会从0变成1
 *  那么xi ^= (xi-1 & ... & x1 & x0 & bit)
 * 
 * 4.为了满足性质(3), 我们需要一个mask, 满足性质:
 *  (1)当counter != k时, mask & counter = counter
 *  (2)当counter == k时, mask & counter = 0
 *  设k的二进制形式为km,km-1,...,k1,k0, mask为ym,ym-1,...y1,y0
 *  不妨考虑当counter != k时, 令mask = 11...1; counter == k时, 令mask = 00...0
 *  因此, mask = ~(ym & ym-1 & ... & y1 & y0), yi = ki == 1 ? xi : ~xi
 *  这样, 当counter只要有一个bit跟k不一样, 那么ym & ... & y0就为1;
 *        当counter与k所有bit一样, ym & ... & y0就为0.
 *  例如当k = 3, 即k = 11, mask = ~(x1 & x0)
 *     当k = 5, 即k = 101, mask = ~(x2 & ~x1 & x0)
 * 
 * 5.现在考虑这个counter的形式, 很直观地想, 我们可以设32个这样的counter来统计每一个bit
 *  但是还有更方便的方法, 假设k < 2^m, 我们可以用m个32位的数字来代替32个m位的counter
 *  即设变量int vm, vm-1, ... , v1, v0, 我们可以将各个数字的每一个bit合并起来当做一个m位的counter
 *  例如各个变量的二进制形式如下:
 *  vm  | xm, ..., x1, x0
 *  ... |    ......
 *  v1  | xm, ..., x1, x0
 *  v0  | xm, ..., x1, x0
 *  我们可以将vm到v0的第i位的bit合起来当做一个m bit的计数器
 * 
 * 6.返回值应该是什么?
 *  因为我们要找到只出现一次的数字 A, 其他数字都出现了k次, 并且counter达到k就归零
 *  所以最后counter的值必定为1, 也就是说m bit的计数器其他的bit都为0, 只有最后一个bit为1
 *  并且这个bit必定来自A. 考虑到counter的形式, 不难看出v0就是A.
 *  更一般地, 设我们要找到出现q次的数字, 即要找到出现q'次的数字(q' = q % k), 记为N
 *  q'的二进制形式为q'm, ... , q0, 那么任意q'i = 1, 我们都有vi = N
 */
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        /* x1, x2的每一个bit组成一个2 bit的计数器 */
        int x1 = 0, x2 = 0, mask = 0;
        for (int i : nums) {
            x2 ^= x1 & i;
            x1 ^= i;
            mask = ~(x2 & x1);
            x2 &= mask;
            x1 &= mask;
        }
        return x1;
    }
};