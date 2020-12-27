/* Leetcode 229.求众数 II
 * 给定一个大小为 n 的数组，找出其中所有出现超过 ⌊n/3⌋ 次的元素。
 * 说明: 要求算法的时间复杂度为O(n)，空间复杂度为O(1)。
 */
#include <vector>
using namespace std;

/* 摩尔投票法进阶版
 * 首先, 一个大小为n的数组, 出现超过⌊n/m⌋的元素最多只有m-1个
 * 因此这题最多只有2个元素
 *
 * 思路:
 * 首先假设出现次数最大的两个数是A, B, 注意, 它们出现的次数不一定超过⌊n/3⌋
 * 那么我们每次拿走3个不一样的数, 最后剩下来的一定是A, B, 分以下情况讨论
 * (1)3个数中包含A和B, 那么A,B的个数各减一, 其他数也减一, A,B还是出现次数最多的数
 * (2)3个数中只包含A或者B, 假设为A, A个数减一, 其他数个数减一, A,B还是出现次数最多的数
 * (3)3个数中不包含A和B, 那么其他数个数减一, A,B不变, A,B还是出现次数最多的数
 * 最后验证A, B出现次数是否大于⌊n/3⌋
 * https://leetcode-cn.com/problems/majority-element-ii/solution/cong-zhu-xing-tu-jiao-chao-ji-su-li-jie-wei-shi-ya/
 */
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> ans;
        int len = nums.size();
        /* 两个候选人, 两个计数器 */
        int cand1 = nums[0], cnt1 = 0;
        int cand2 = nums[0], cnt2 = 0;
        for (int n : nums) {
            if (cand1 == n)
                /* 投A, A票数加一 */
                cnt1++;
            else if (cand2 == n)
                /* 投B, B票数加一 */
                cnt2++;
            else if (cnt1 == 0) {
                /* 不投A也不投B, 检查计数是否为0, 是则更新候选人 */
                cand1 = n;
                cnt1 = 1;
            } else if (cnt2 == 0) {
                cand2 = n;
                cnt2 = 1;
            } else {
                /* 不投A也不投B, A,B计数都不为0, A,B票数减一 */
                cnt1--;
                cnt2--;
            }
            /* 为什么不是先检查计数再投票呢?
             * 因为虽然可能某个计数已经变为0了,此时候选人只剩一个
             * 我们要先投票, 才能确定第二个候选人是谁
             */
        }
        cnt1 = cnt2 = 0;
        /* 检查出现次数是否大于⌊n/3⌋ */
        for (int n : nums) {
            if (n == cand1) {
                cnt1++;
            } else if (n == cand2) {
                cnt2++;
            }
        }
        if (cnt1 > len / 3)
            ans.push_back(cand1);
        if (cnt2 > len / 3)
            ans.push_back(cand2);
        return ans;
    }
};