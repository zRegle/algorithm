/**
 * Leetcode 494. 目标和
 * 给定一个非负整数数组，a1, a2, ..., an, 和一个目标数，S。
 * 现在你有两个符号 + 和 -。对于数组中的任意一个整数，你都可以从 + 或 -中选择一个符号添加在前面。
 * 返回可以使最终数组和为目标数 S 的所有添加符号的方法数。
 * 
 * 示例：
 *  输入：nums: [1, 1, 1, 1, 1], S: 3
 *  输出：5
 *  解释：
 *   -1+1+1+1+1 = 3
 *   +1-1+1+1+1 = 3
 *   +1+1-1+1+1 = 3
 *   +1+1+1-1+1 = 3
 *   +1+1+1+1-1 = 3
 *   一共有5种方法让最终目标和为3。
 * 
 * 提示：
 *  (1)数组非空，且长度不会超过 20 。
 *  (2)初始的数组的和不会超过 1000 。
 *  (3)保证返回的最终结果能被 32 位整数存下。
 */
#include <vector>
#include <unordered_map>
using std::vector;
using std::unordered_map;

/* dp方法查看dp文件夹 */

/* dfs暴搜 + 记忆化 */
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        vis.resize(nums.size(), unordered_map<int, int>());
        return dfs(0, nums, 0, S);
    }

private:
    /* 记忆化
     * vis[i][sum] = cnt
     * 表示递归到第i个数字时, 并且之前的和为sum
     * 有多少种方法可以使得最终和为target
     */
    vector<unordered_map<int, int>> vis;
    /**
     * @param idx 当前下标, 即dfs深度
     * @param nums nums数组
     * @param sum 进入到idx时, 之前的和
     * @param target target
     * @return 进入到idx并且之前的和为sum时, 有多少种不同的方法使得最终和为target
     */
    int dfs(int idx, vector<int>& nums, int sum, int target) {
        if (idx == nums.size()) {
            if (sum == target)
                return 1;
            return 0;
        }

        auto& map = vis[idx];
        if (map.find(sum) != map.end())
            return map[sum];

        int cnt = 0;
        sum += nums[idx];
        cnt += dfs(idx + 1, nums, sum, target);
        sum -= nums[idx];

        sum -= nums[idx];
        cnt += dfs(idx + 1, nums, sum, target);
        sum += nums[idx];

        map[sum] = cnt;
        return cnt;
    }
};