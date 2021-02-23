/**
 * Leetcode 300. 最长递增子序列
 * 给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
 * 子序列是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。
 * 例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。
 *
 * 示例 1：
 *  输入：nums = [10,9,2,5,3,7,101,18]
 *  输出：4
 *  解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。
 * 示例 2：
 *  输入：nums = [0,1,0,3,2,3]
 *  输出：4
 *
 * 提示：
 *  (1)1 <= nums.length <= 2500
 *  (2)-10^4 <= nums[i] <= 10^4
 *
 * 进阶：
 *  你可以设计时间复杂度为 O(n²) 的解决方案吗？
 *  你能将算法的时间复杂度降低到O(n log(n)) 吗?
 */
#include <vector>
using namespace std;

/**
 * 假如我们在子序列中要插入元素X，希望找出插入之后的最长子序列，从贪心的角度考虑（尽可能增加递增子序列的长度），
 * 我们需要在当前允许插入的 最长 子序列之后添加元素
 * 我们发现，对每一个序列长度 l，只需要检查长度为l的序列中的最小值val是否小于x即可
 * 如果val < X，表明长度为 l 的递增子序列后可添加元素 X
 *
 * 因此, 我们定义d[i]为, 长度为i的递增子序列的最后一个元素的最小值
 * 例如: [10, 9, 2, 5, 3, 7, 101, 4, 1]
 * 长度为3的递增子序列有:
 *  [2,5,7], [2,3,7], [2,3,4]
 * 其中最后一个元素的最小值为4, 因此d[3] = 4
 *
 * 我们可以保证, d[i]是随着i单调递增的, 反证法证明:
 * 假设存在j < i且d[j] > d[i], 那么我们在d[i]对应的长度为i的子序列A中,
 * 删除最后的i-j个元素, 形成一个长度为j的子序列B, 设B最后一个元素为k
 * 因为在原来的子序列中, k < d[i], 因此有k < d[i] < d[j]
 * d[j]就不是长度为j的递增子序列的最后一个元素的最小值, 证毕
 *
 * 保证了d[i]的单调性, 我们就可以利用二分法来不断更新d[i]
 *
 * 注意: 数组d不是真实存在于数组nums中的递增子序列
 *
 * 详细图解参考:
 * https://leetcode-cn.com/problems/longest-increasing-subsequence/solution/yi-bu-yi-bu-tui-dao-chu-guan-fang-zui-you-jie-fa-x/
 */
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int len = 1, n = nums.size();
        vector<int> d(n+1, 0);
        d[len] = nums[0];
        for (int i = 1; i < n; i++) {
            if (nums[i] > d[len])
                /* nums[i] > d[len]
                 * 根据贪心, 我们加到最长的子序列中 */
                d[++len] = nums[i];
            else {
                /* nums[i]不能加到长度为len的递增子序列中
                 * 找到当前允许插入的最长子序列中 */
                int left = 1, right = len, pos = 0;
                while (left <= right) {
                    int mid = (left + right) / 2;
                    if (d[mid] < nums[i]) {
                        /* nums[i] > min{长度为mid的递增子序列的最大值}
                         * 即nums[i]能够插入到长度为mid的递增子序列中
                         * mid可能就是最长的子序列, 先保存, 继续二分 */
                        pos = mid;
                        left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                }
                /* 更新 所有长度为pos+1的递增序列的最大值 中的最小值 */
                d[pos + 1] = nums[i];
            }
        }
        return len;
    }
};