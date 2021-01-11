/* Leetcode 209.长度最小的子数组
 * 给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的 连续 子数组，并返回其长度。如果不存在符合条件的子数组，返回 0。
 * 示例：
 *  输入：s = 7, nums = [2,3,1,2,4,3]
 *  输出：2
 *  解释：子数组 [4,3] 是该条件下的长度最小的子数组。
 * 进阶：如果你已经完成了 O(n) 时间复杂度的解法, 请尝试 O(n log n) 时间复杂度的解法。
 */
#include <climits>
#include <vector>
using namespace std;

/* 双指针, 一看就懂, i,j最多各移动n次, 因此是O(n) */
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if (nums.empty()) return 0;
        int i = 0, j = 0, minLen = INT_MAX, sum = 0;
        while (j < nums.size()) {
            sum += nums[j];
            while (sum >= s) {
                minLen = min(minLen, j - i + 1);
                sum -= nums[i];
                i++;
            }
            j++;
        }
        return minLen == INT_MAX ? 0 : minLen;
    }
};

/* 进阶的O(nlogn), 第一次看见要增加时间复杂度的
 *
 * 假设一个数组sums[i], 代表从第1个数字到第i个数字之和
 * 因为题目假设数组数字全为正数, s也是正数
 * 所以sums[i]一定是单调递增的
 *
 * 如果我们能在sums数组中找到第一个大于等于s+sums[i]的数字, 记下标为bound
 * 即sums[bound] - sums[i] >= s
 * 那么第i个数字加到第bound个数字一定大于等于s
 */
int minSubArrayLen(int s, vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    int minLen = INT_MAX;
    vector<int> sums(n+1, 0);
    for (int i = 1; i <= n; i++)
        sums[i] = nums[i-1] + sums[i-1];
    for (int i = 1; i <= n; i++) {
        int target = s + sums[i-1];
        /* lower_bound用二分查找找到数组中第一个大于等于target的数字
         * 反之, upper_bound是找到第一个大于target的数字
         */
        auto bound = lower_bound(sums.begin(), sums.end(), target);
        if (bound != sums.end()) {
            minLen = min(minLen, static_cast<int>((bound - sums.begin()) - i + 1));
        }
    }
    return minLen == INT_MAX ? 0 : minLen;
}