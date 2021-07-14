/**
 * Leetcode 1818. 绝对差值和
 * 给你两个正整数数组 nums1 和 nums2 ，数组的长度都是 n 。
 * 数组 nums1 和 nums2 的 绝对差值和 定义为所有 ：
 *   |nums1[i] - nums2[i]|（0 <= i < n）的 总和（下标从 0 开始）。
 * 你可以选用 nums1 中的 任意一个 元素来替换 nums1 中的 至多 一个元素，以 最小化 绝对差值和。
 * 在替换数组 nums1 中最多一个元素 之后 ，返回最小绝对差值和。
 * 因为答案可能很大，所以需要对 109 + 7 取余 后返回。
 * |x| 定义为：
 *  如果 x >= 0 ，值为 x ，或者
 *  如果 x <= 0 ，值为 -x
 * 
 * 示例 1：
 *  输入：nums1 = [1,7,5], nums2 = [2,3,5]
 *  输出：3
 *  解释：有两种可能的最优方案：
 *  - 将第二个元素替换为第一个元素：[1,7,5] => [1,1,5] ，或者
 *  - 将第二个元素替换为第三个元素：[1,7,5] => [1,5,5]
 *  两种方案的绝对差值和都是 |1-2| + (|1-3| 或者 |5-3|) + |5-5| = 3
 * 示例 2：
 *  输入：nums1 = [2,4,6,8,10], nums2 = [2,4,6,8,10]
 *  输出：0
 *  解释：nums1 和 nums2 相等，所以不用替换元素。绝对差值和为 0
 * 示例 3：
 *  输入：nums1 = [1,10,4,4,2,7], nums2 = [9,3,5,1,7,4]
 *  输出：20
 *  解释：将第一个元素替换为第二个元素：[1,10,4,4,2,7] => [10,10,4,4,2,7]
 *  绝对差值和为 |10-9| + |10-3| + |4-5| + |4-1| + |2-7| + |7-4| = 20
 * 
 * 提示：
 *  (1)n == nums1.length
 *  (2)n == nums2.length
 *  (3)1 <= n <= 105
 *  (4)1 <= nums1[i], nums2[i] <= 10^5
 */
#include <vector>
#include <cstdint>
#include <algorithm>
using namespace std;

/**
 * 错误做法:
 * 找到下标i, 使得abs(A[i] - B[i])最大化
 * 在A中找到跟B[i]最接近的数A[j], 替换掉A[i]
 *
 * 反例:
 * A = [1,28,21]
 * B = [9,21,20]
 * 按照这种做法, 找到的i是0 (A[0] - B[0] = 8)
 * 在A中找到跟B[0]最接近的数: 1, 替换A[0]
 * 最终得到A = [1,28,21], 绝对差值和没变
 * 我们应该用21替换28, 得到A = [1,21,21], 绝对差值和为9
 *
 * 归根结底, 按照这种做法我们只关注某一个下标
 * 替换之后不一定能使绝对差值更小
 * 我们应该对每个下标都进行类似的操作
 */
class WrongAnswer {
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        uint64_t sum = 0;
        int n = nums1.size(), idx = 0, maxGap = 0;
        /* 找到abs(A[i] - B[i])最大的下标i */
        for (int i = 0; i < n; i++) {
            int gap = abs(nums1[i] - nums2[i]);
            if (gap > maxGap) {
                maxGap = gap;
                idx = i;
            }
            sum += gap;
        }
        /* 在nums1中找到最接近nums2[idx]的数字进行替换 */
        sort(nums1.begin(), nums1.end());
        auto it = lower_bound(nums1.begin(), nums1.end(), nums2[idx]);
        if (it == nums1.end()) {
            sum += abs(nums1.back() - nums2[idx]);
        } else if (it == nums1.begin()) {
            sum += abs(*it - nums2[idx]);
        } else {
            auto iter = it;
            sum += min(abs(*(--iter) - nums2[idx]), abs(*it - nums2[idx]));
        }
        return sum % ((int)1e9 + 7);
    }
};

/**
 * 正确做法:
 * 我们应该对A,B数组的每一个下标i, 都算出它们之间的差值gap[i]
 * 然后尝试替换A[i], 算出替换后的与B[i]的gap'[i]
 * 对于每个下标i都可以算出gap[i], gap'[i]
 * 取max{gap[i] - gap'[i], 0 <= i <= n}, 就是我们要替换的数字
 */
class Solution {
public:
    static constexpr int mod = (int)1e9 + 7;
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        vector<int> copy(nums1);
        sort(copy.begin(), copy.end());
        int n = nums1.size(), sum = 0, maxDiff = 0;
        for (int idx = 0; idx < n; idx++) {
            /* 计算gap[i] */
            int gap = abs(nums1[idx] - nums2[idx]);
            sum = (sum + gap) % mod;
            /* 在nums1中找到跟nums2[idx]最接近的数字x */
            int i = lower_bound(copy.begin(), copy.end(), nums2[idx]) - copy.begin();
            /* 数字x既可能大于nums2[idx]也可能小于nums2[idx]
             * 需要各检查一次 */
            if (i > 0)
                /* 数字x小于nums2[idx] */
                maxDiff = max(maxDiff, gap - (nums2[idx] - nums1[i-1]));
            if (i < n)
                /* 数字x大于nums2[idx] */
                maxDiff = max(maxDiff, gap - (nums1[i] - nums2[idx]));
        }
        /* sum - maxDiff后可能会变成负数, 加上mod后再取模 */
        return (sum - maxDiff + mod) % mod;
    }
};