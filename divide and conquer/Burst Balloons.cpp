/**
 * Leetcode 312.戳气球
 * 有 n 个气球，编号为0 到 n - 1，每个气球上都标有一个数字，这些数字存在数组 nums 中。
 * 现在要求你戳破所有的气球。戳破第 i 个气球，你可以获得 nums[i - 1] * nums[i] * nums[i + 1] 枚硬币。
 * 这里的 i - 1 和 i + 1 代表和 i 相邻的两个气球的序号。
 * 如果 i - 1或 i + 1 超出了数组的边界，那么就当它是一个数字为 1 的气球。
 * 求所能获得硬币的最大数量。
 *
 * 示例 1：
 *  输入：nums = [3,1,5,8]
 *  输出：167
 *  解释：
 *   nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
 *   coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
 * 示例 2：
 *  输入：nums = [1,5]
 *  输出：10
 *
 * 提示：
 *  1.n == nums.length
 *  2.1 <= n <= 500
 *  3.0 <= nums[i] <= 100
 */
#include <vector>
using namespace std;

/* dp方法参考dp文件夹 */

/**
 * 比较直观的暴搜思路:
 *  [i, j]区间枚举戳爆所有气球, 改变数组, 递归搜索
 * 毫无疑问, 直接TLE了.
 * 假设数组元素一共为n个, 第一层递归有n个气球可以枚举, 第二层递归有n-1个气球可以枚举
 * 以此类推, 时间复杂度是O(n!), 属于最高时间复杂度的方法
 */

/**
 * 转化一下思路, 采用分治法来解决
 * 首先定问题: 设戳破[i, j]区间所有气球得到的最大硬币数为coins(i, j)
 * 我们能否通过划分一个一个子问题来求解?
 * 我们观察戳气球的操作, 发现这会导致两个气球从不相邻变成相邻, 使得后续操作难以处理
 *  比如i<=k<=j, 我们戳破气球k, 会使得本来不相邻的k-1和k+1相邻.
 *  接着我们如果再戳破k-1或者k+1, 两者导致的结果也不一样
 *  即: 两个子问题之间差生了依赖, 子问题的处理顺序将影响到每个子问题的解
 *
 * 此时我们应该换另外一种划分方式
 * 既然两个子问题都依赖k和两个边界i和j, 那么我们划分子问题时,
 * k与两个边界i和j这三个气球我们都不戳破, 求出[i+1, k-1]与[k+1, j-1]的解.
 * 这样两个子问题间的依赖便被消除了, 两个边界i和j及气球k不戳破,
 * 两个子问题的依赖都不会越过k到另一个子问题上子问题间是相互独立的
 *
 * 我们重新定义一下问题, 设coins(i, j)为不戳破i和j气球下, 区间(i, j)最多获得的硬币数
 * 我可以枚举(i, j)区间的所有k, 然后取最大值即可:
 *   coins(i, j) = max{val[i] * val[k] * val[j] + coins(i, k) + coins(k, j) | i < k < j}
 *   其中val[k]为k代表的气球的数字
 *   公式中第一个元素代表, (i, j)区间内所有的气球都被戳破, 只剩下i, k, j三个气球时, 戳破k气球获得的硬币数
 *   第二三个元素代表两个子问题
 */

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        mem.resize(n+2, vector<int>(n+2, -1));
        /* 为数组添上两个虚拟气球作为边界, 即nums[-1]和nums[n], 方便后续处理
         * 其余元素为val[i] = nums[i-1] */
        val.resize(n+2, 0);
        val[0] = val[n+1] = 1;
        for (int i = 1; i <= n; i++) {
            val[i] = nums[i-1];
        }
        return solve(0, n+1);
    }

private:
    vector<vector<int>> mem; /* 记忆化数组 */
    vector<int> val;

    int solve(int left, int right) {
        if (left >= right-1)
            return 0;
        if (mem[left][right] != -1)
            return mem[left][right];
        /* i, j气球不戳破, 枚举(i, j)内的所有气球 */
        for (int i = left + 1; i < right; i++) {
            int coins = val[left] * val[i] * val[right];
            coins += solve(left, i) + solve(i, right);
            mem[left][right] = max(mem[left][right], coins);
        }
        return mem[left][right];
    }
};