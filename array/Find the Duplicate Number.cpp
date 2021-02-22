/**
 * Leetcode 287. 寻找重复数
 * 给定一个包含 n + 1 个整数的数组 nums ，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。
 * 假设 nums 只有 一个重复的整数 ，找出 这个重复的数 。
 *
 * 示例：
 *  输入：nums = [1,3,4,2,2]
 *  输出：2
 *
 * 提示：
 *  (1)2 <= n <= 3 * 104
 *  (2)nums.length == n + 1
 *  (3)1 <= nums[i] <= n
 *  (4)nums 中 只有一个整数 出现 两次或多次 ，其余整数均只出现 一次
 *  
 * 进阶：
 *  (1)你可以在不修改数组 nums 的情况下解决这个问题吗？
 *  (2)你可以只用常量级 O(1) 的额外空间解决这个问题吗？
 *  (3)你可以设计一个时间复杂度小于 O(n2) 的解决方案吗？
 */
#include <vector>
#include <algorithm>
using namespace std;

/* 排序 */
class Solution0 {
public:
    int findDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i-1])
                return nums[i];
        }
        return 0;
    }
};

/* 辅助数组 */
class Solution1 {
public:
    int findDuplicate(vector<int>& nums) {
        int len = nums.size();
        auto auxiliary = vector<int>(len, 0);
        for (int x : nums) {
            if (auxiliary[x-1] != 0)
                return x;
            auxiliary[x-1] = 1;
        }
        return 0;
    }
};

/* 下面是满足进阶要求的做法 */

/**
 * 设cnt(i)为数组中小于等于i的数字的数量, 我们要找的数字是t
 * 那么我们可以归纳出性质:
 *  (1) [1, t-1]内, 对于任意的i, 都有cnt(i) <= i
 *  (2) [t, n]内, 对于任意的j, 都有cnt(j) > j
 *
 * 对于性质(1), 若cnt(i) = i, 表明[1, i]内的所有数字都出现了
 *            若cnt(i) < i, 表明[1, i]中有某些数字被t替代了
 * 对于性质(2), 因为t至少出现了两次, 因此[t, n]中任意的j, 都有cnt(j) > j
 *
 * 我们在[1, n]的范围内不断二分, 直到找到t
 */
class Solution2 {
public:
    int findDuplicate(vector<int>& nums) {
        int left = 0, right = nums.size()-1;
        int ans = 0;
        while (left <= right) {
            /* 注意, mid不一定出现在nums数组中 */
            int mid = (left + right) / 2;
            int cnt = 0;
            for (int x : nums)
                cnt += x <= mid;
            if (cnt <= mid)
                /* mid满足cnt(mid) <= mid, 证明mid∈[1, t-1]
                 * 向右继续二分 */
                left = mid + 1;
            else {
                /* mid满足cnt(mid) > mid, 证明mid∈[t, n]
                 * 向左继续二分 */
                right = mid - 1;
                ans = mid; /* mid可能就是t, 先保存下来 */
            }
        }
        return ans;
    }
};

/**
 * 比较tricky的做法, 将数组看成一个链表
 *
 * 设当前下标为i, 那么我们指向下一个节点的指针就是nums[i]
 * 如果存在重复数字t, 那么必定有大于等于两个指针指向nums[t], 即这个链表有环
 * 例如: [1,3,4,2,2]
 * 0 -> 1
 * 1 -> 3
 * 2 -> 4
 * 3 -> 2
 * 4 -> 2
 * 我们遍历链表, 从0开始, nums[0]是1, 那么下一个节点就是nums[1]
 * nums[1]为3, 那么下一个节点就是nums[3], 以此类推, 链表的形式如下:
 * 1->3->2->4->2->4->2->4->2...
 * 由此, 我们需要做的就是找到环的入口, 用leetcode 142的方法即可
 *
 * 详细解释参考链接:
 * https://leetcode-cn.com/problems/find-the-duplicate-number/solution/kuai-man-zhi-zhen-de-jie-shi-cong-damien_undoxie-d/
 */
class Solution3 {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0, fast = 0;
        do {
            /* 相当于slow = slow->next */
            slow = nums[slow];
            /* 相当于fast = fast->next->next */
            fast = nums[nums[fast]];
        } while (slow != fast);
        fast = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};