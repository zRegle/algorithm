/* Leetcode 213.打家劫舍2
 * 你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，
 * 这个地方所有的房屋都围成一圈，这意味着第一个房屋和最后一个房屋是紧挨着的。
 * 影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，
 * 如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
 * 给定一个代表每个房屋存放金额的非负整数数组，计算你在不触动警报装置的情况下，能够偷窃到的最高金额。
 * 示例 1:
 *  输入: [2,3,2]
 *  输出: 3
 *  解释: 你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的。
 */
#include <vector>
using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int size = nums.size();
        if (size == 0) return 0;
        if (size < 2) return nums[0];
        int prev = 0, prev_p = 0;
        int include = 0, exclude = 0;
        //第一个循环不抢最后一间房子, 所以循环到倒数第二间房子即可
        for (int i = 0; i < size-1; i++) {
            include = max(prev, prev_p + nums[i]);
            prev_p = prev;
            prev = include;
        }
        prev = prev_p = 0;
        //第二个循环不抢第一间房子, 所以从第二间房子开始循环
        for (int i = 1; i < size; i++) {
            exclude = max(prev, prev_p + nums[i]);
            prev_p = prev;
            prev = exclude;
        }
        return max(include, exclude);
    }
};