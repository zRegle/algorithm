/* Leetcode 198.打家劫舍
 * 你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，
 * 影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，
 * 如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
 * 给定一个代表每个房屋存放金额的非负整数数组，计算你在不触动警报装置的情况下，能够偷窃到的最高金额。
 * 示例 1:
 * 输入: [1,2,3,1]
 * 输出: 4
 * 解释: 偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
 *      偷窃到的最高金额 = 1 + 3 = 4 。
 */
#include <vector>
using namespace std;

//dp[i][1]表示抢第i个房子, 前i个房子最多能抢多少钱
//dp[i][0]表示不抢第i个房子, 前i个房子最多能抢多少钱
class Solution1 {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) return 0;
        int size = nums.size();
        vector<vector<int>> dp(size+1, vector<int>(2,0));
        for (int i = 1; i <= size; i++) {
            for (int j = 0; j < 1; j++) {
                dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
                dp[i][1] = dp[i-1][0] + nums[i-1];
            }
        }
        return max(dp[size][0], dp[size][1]);
    }
};

//更简单的方法, 代码一看就懂了
class Solution2 {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) return 0;
        int size = nums.size();
        //prev: 抢前一个房子, 之前所有房子最多能抢多少
        //prev_p: 抢前一个房子的前一个房子, 所有房子最多能抢多少
        int prev = 0, prev_p = 0;
        int money = 0;
        for (int n : nums) {
            money = max(prev, prev_p + n);
            prev_p = prev;
            prev = money;
        }
        return money;
    }
};