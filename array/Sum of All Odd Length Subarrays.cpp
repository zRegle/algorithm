/**
 * Leetcode 1588. 所有奇数长度子数组的和
 * 给你一个正整数数组 arr ，请你计算所有可能的奇数长度子数组的和。
 * 子数组 定义为原数组中的一个连续子序列。
 * 请你返回 arr 中 所有奇数长度子数组的和 。
 *
 * 示例 1：
 *  输入：arr = [1,4,2,5,3]
 *  输出：58
 *  解释：所有奇数长度子数组和它们的和为：
 *   [1] = 1
 *   [4] = 4
 *   [2] = 2
 *   [5] = 5
 *   [3] = 3
 *   [1,4,2] = 7
 *   [4,2,5] = 11
 *   [2,5,3] = 10
 *   [1,4,2,5,3] = 15
 *   我们将所有值求和得到 1 + 4 + 2 + 5 + 3 + 7 + 11 + 10 + 15 = 58
 */
#include <vector>
using std::vector;

/* 可以老实地一个一个数组求和, 时间复杂度为O(N^3)
 * 也可以用一个memo数组, 时间复杂度为O(N^2), 空间复杂度为O(N)
 * 下面说明时间O(N), 空间O(1)的方法
 *
 * 我们来看数组中第i(从1开始计数)个元素, 可以从例子中看到, arr[i-1]在求解过程中被相加了很多次
 * 如果我们能通过一次遍历就知道arr[i-1]相加了多少次, 就能得出O(N)解法
 * 即: 需要求出包含arr[i-1]在内, 长度为奇数的子数组的个数
 *
 * 设arr数组长度为len(从1开始计数),满足条件的其中一个子数组为sub
 * sub由两部分组成, 以第i个元素为分界, 左边部分在[1, i], 右边部分在(i, len]
 * 显然, 左边部分的长度是奇数时, 右边必须为偶数; 左边长度是偶数时, 右边必须是奇数
 *
 * 设[1, i]中有奇数偶数的个数分别为EVEN(left)和ODD(left), (i, len]中为EVEN(right)和ODD(right)
 * 那么包含arr[i-1]在内, 长度为奇数的子数组的个数:
 *      EVEN(left) * ODD(right) + ODD(left) * EVEN(right)
 *
 * 例如: arr = {1,4,2,5,3}, i = 2, arr[i-1] = 4
 * [1, 2]里有一个奇数一个偶数, 分别是1和2
 *  (1)以1作例子, 在{1，4}中选择包含4并且长度为1的子数组
 *     那么对应的, 在{2,5,3}中选择长度为偶数的子数组, 分别有{}, {2,5}
 *     那么合并起来长度为奇数的sub就有{4}, {4,2,5}
 *  (2)同样的, 我们在{1, 4}中选择包含4并且长度为2的子数组, 为{1,4}
 *     那么对应的, 在{2,5,3}中选择长度为奇数的子数组, 分别有{2}, {2,5,3}
 *     那么合并起来长度为奇数的sub就有{1,4,2}, {1,4,2,5,3}
 */

/* 统计[1, x]有多少个偶数和奇数 */
#define CNT_EVEN(x) ((x) / 2)
#define CNT_ODD(x) ((x) / 2 + ((x) & 1))
class Solution {
public:
    int sumOddLengthSubarrays(vector<int>& arr) {
        int len = arr.size(), ans = 0;
        for (int i = 0; i < len; i++) {
            ans += helper(i + 1, len) * arr[i];
        }
        return ans;
    }

private:
    int helper(int i, int len) const {
        int leftEven = CNT_EVEN(i), leftOdd = CNT_ODD(i);
        /* (i, len]部分, 0也是偶数, 因此加一 */
        int rightEven = CNT_EVEN(len - i) + 1, rightOdd = CNT_ODD(len - i);
        return leftEven * rightOdd + leftOdd * rightEven;
    }
};