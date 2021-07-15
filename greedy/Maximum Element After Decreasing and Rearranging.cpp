/**
 * Leetcode 1846. 减小和重新排列数组后的最大元素
 * 给你一个正整数数组 arr 。请你对 arr 执行一些操作（也可以不进行任何操作），使得数组满足以下条件：
 *  (1)arr 中 第一个 元素必须为 1 。
 *  (2)任意相邻两个元素的差的绝对值 小于等于 1 ，也就是说，
 *     对于任意的 1 <= i < arr.length （数组下标从 0 开始），
 *     都满足 abs(arr[i] - arr[i - 1]) <= 1 。abs(x) 为 x 的绝对值。
 *
 * 你可以执行以下 2 种操作任意次：
 *  (1)减小 arr 中任意元素的值，使其变为一个 更小的正整数 。
 *  (2)重新排列 arr 中的元素，你可以以任意顺序重新排列。
 * 请你返回执行以上操作后，在满足前文所述的条件下，arr 中可能的 最大值 。
 *
 * 示例 1：
 *  输入：arr = [2,2,1,2,1]
 *  输出：2
 *  解释：我们可以重新排列 arr 得到 [1,2,2,2,1] ，该数组满足所有条件。
 *       arr 中最大元素为 2 。
 * 示例 2：
 *  输入：arr = [100,1,1000]
 *  输出：3
 *  解释：
 *   一个可行的方案如下：
 *   1. 重新排列 arr 得到 [1,100,1000] 。
 *   2. 将第二个元素减小为 2 。
 *   3. 将第三个元素减小为 3 。
 *   现在 arr = [1,2,3] ，满足所有条件。
 *   arr 中最大元素为 3 。
 * 示例 3：
 *  输入：arr = [1,2,3,4,5]
 *  输出：5
 *  解释：数组已经满足所有条件，最大元素为 5 。
 *
 * 提示：
 *  (1)1 <= arr.length <= 10^5
 *  (2)1 <= arr[i] <= 10^9
 */
#include <vector>
#include <algorithm>
using namespace std;

/**
 * 由条件
 *  (1)起始必须为1
 *  (2)相邻元素间差值不大于1
 * 得数组最大元素不超过n
 */

/* O(nlogn)做法
 * 排序之后, 将数组各个元素减少到满足题意的最大值 */
class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int n = arr.size();
        arr[0] = 1;
        for (int i = 1; i < n; i++) {
            arr[i] = min(arr[i], arr[i-1] + 1);
        }
        return arr[n-1];
    }
};

/**
 * 计数排序 + 贪心, O(n)
 *
 * 记arr的长度为n. 由于第一个元素必须为1, 且任意两个相邻元素的差要小于等于1, 故答案不会超过n
 * 我们只需要对arr中不超过n的元素进行计数排序, 对于值超过n的元素, 将其减小到n
 *
 * 从另一个视角来看，为了尽可能地构造出最大的答案，我们相当于是在用arr中的元素去填补自身在[1,n]中缺失的元素。
 * 首先，我们用一个长为n+1的数组cnt统计arr中的元素个数（将值超过n的元素视作n）。
 * 然后，从1到n遍历cnt数组，若cnt[i]=0，则说明缺失元素i，我们需要在后续找一个大于i的元素，将其变更为i。
 * 我们可以用一个变量miss记录cnt[i]=0的出现次数，当遇到cnt[i]>0时，则可以将多余的cnt[i]−1个元素减小，补充到之前缺失的元素上。
 * 遍历cnt结束后，若此时miss=0，则说明修改后的arr包含了[1,n]内的所有整数；
 * 否则，对于不同大小的缺失元素，我们总是优先填补较小的，因此剩余缺失元素必然是[n−miss+1,n]这一范围内的miss个数，
 * 因此答案为n−miss。
 */
class Solution1 {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        int n = arr.size(), ans = 0;
        vector<int> cnt(n+1);
        for (int x : arr)
            /* 统计元素出现的次数, 超过n的元素算作n */
            cnt[min(x, n)]++;
        int miss = 0;
        for (int i = 1; i <= n; ++i) {
            if (cnt[i] == 0) {
                ++miss;
            } else {
                // miss 不会小于 0，故至多减去 miss 个元素
                miss -= min(cnt[i] - 1, miss);
            }
        }
        return n - miss;
    }
};