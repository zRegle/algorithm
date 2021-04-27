/**
 * Leetcode 611.有效三角形的个数
 * 给定一个包含非负整数的数组，你的任务是统计其中可以组成三角形三条边的三元组个数。
 *
 * 示例 1:
 *  输入: [2,2,3,4]
 *  输出: 3
 *  解释:
 *   有效的组合是:
 *   2,3,4 (使用第一个 2)
 *   2,3,4 (使用第二个 2)
 *   2,2,3
 *
 * 注意:
 * (1)数组长度不超过1000。
 * (2)数组里整数的范围为 [0, 1000]。
 */
#include <vector>
#include <algorithm>
using namespace std;

/**
 * 思路:
 * 先排序, 然后固定两条边i, j
 * 二分查找数组中第一个大于等于nums[i] + nums[j]的元素, 下标为k
 * 那么(j, k)之间的任意元素都可以跟i, j组成三角形
 *
 * 时间复杂度: O(n²logn)
 */
class Solution0 {
public:
    int triangleNumber(vector<int>& nums) {
        int len = nums.size();
        if (len < 3) return 0;
        sort(nums.begin(), nums.end());
        int count = 0;
        /* i最大为倒数第三个 */
        for (int i = 0; i < len-2; i++) {
            /* j最大为倒数第二个 */
            for (int j = i+1; j < len-1; j++) {
                int sum = nums[i] + nums[j];
                auto lower = lower_bound(nums.begin()+j+1, nums.end(), sum);
                if (lower != nums.end())
                    /* 此时有nums[i] + nums[j] <= nums[lower]
                     * 那么(j, lower)之间的任意k, 都满足
                     *  nums[i] + nums[j] > nums[k]    (1)
                     * 又易知
                     *  nums[i] <= nums[j] <= nums[k]  (2)
                     * 由(2)得:
                     *  nums[j] - nums[i] <= nums[k] - nums[i] < nums[k]
                     * 由(1)得:
                     *  nums[k] - nums[j] < nums[i]
                     *  nums[k] - nums[i] < nums[j]
                     * 因此(j, lower)之间的任意k都可以与i, j组成三角形 */
                    count += distance(nums.begin(), lower) - j - 1;
            }
        }
        return count;
    }
};

/**
 * 双指针:
 * 首先对数组排序, 接着固定最长的一条边，运用双指针扫描
 *  (1)如果 nums[l] + nums[r] > nums[i],
 *       说明 nums[l + 1] + nums[r] > nums[i], ..., nums[r - 1] + nums[r] > nums[i]，
 *       满足的条件的有 r - l 种，r左移进入下一轮。
 *  (2)如果 nums[l] + nums[r] <= nums[i]，l右移进入下一轮。
 * 枚举结束后，总和就是答案。
 * 时间复杂度为 O(n²)
 */
class Solution1 {
public:
    int triangleNumber(vector<int>& nums) {
        int len = nums.size();
        if (len < 3) return 0;
        sort(nums.begin(), nums.end());
        int count = 0;
        for (int i = len-1; i >= 2; i--) {
            int l = 0, r = i-1;
            while (l < r) {
                if (nums[l] + nums[r] > nums[i]) {
                    count += r-l;
                    r--;
                } else {
                    l++;
                }
            }
        }
        return count;
    }
};