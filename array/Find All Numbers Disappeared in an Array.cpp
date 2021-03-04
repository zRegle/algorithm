/**
 * Leetcode 448. 找到所有数组中消失的数字
 * 给定一个范围在  1 ≤ a[i] ≤ n ( n = 数组大小 ) 的 整型数组，
 * 数组中的元素一些出现了两次，另一些只出现一次。
 * 找到所有在 [1, n] 范围之间没有出现在数组中的数字。
 *
 * 您能在不使用额外空间且时间复杂度为O(n)的情况下完成这个任务吗? 你可以假定返回的数组不算在额外空间内。
 * 示例:
 *  输入: [4,3,2,7,8,2,3,1]
 *  输出: [5,6]
 */
#include <vector>
#include <cmath>
using namespace std;

/**
 * 因为元素范围是[1, n], 我们可以用这个范围外的数字来表达"是否出现过"
 * 具体做法:
 * 设当前元素nums[i] = x, 我们将nums[x - 1]的元素置变成负数, 代表x这个元素出现过
 * 设nums[x - 1]的元素本来就是负数, 表明x这个元素已经出现过, x是多余的, 就不需要置负数了
 * 最后我们遍历数组, 如果位置i的元素是正数, 代表i+1没出现过
 */
class Solution0 {
public:
    vector<int> findDisapperedNumbers(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int x = abs(nums[i]);
            if (nums[x - 1] > 0)
                nums[x - 1] *= -1;
        }
        vector<int> ans;
        for (int i = 0; i < n; i++)
            if (nums[i] > 0)
                ans.push_back(i + 1);
        return ans;
    }
};

/**
 * 思路: 不断将元素放到数组对应下标的桶中
 */
class Solution1 {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            while (nums[i] != i + 1 && nums[i] != -1) {
                /* 设nums[i] = x, 那么我们应该把x放到nums[x-1]桶中 */
                if (nums[nums[i] - 1] == nums[i]) {
                    /* 如果nums[x-1]这个桶已经有x了, 代表nums[i]这个桶中的x是多余的
                     * 我们去除掉这个x, 将目前存放这个多余的x的桶置空 */
                    nums[i] = -1; /* 置空桶 */
                    break;
                }
                /* 把x放到nums[x-1]桶中
                 * nums[x-1]桶中原来的元素暂存到nums[i]这个桶中 */
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        vector<int> ans;
        /* 最后统计哪个桶是空闲的即可 */
        for (int i = 0; i < n; i++) {
            if (nums[i] == -1)
                ans.push_back(i + 1);
        }
        return ans;
    }
};