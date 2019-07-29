/* Leetcode 45 跳跃游戏2
 * 给定一个非负整数数组，你最初位于数组的第一个位置。
 * 数组中的每个元素代表你在该位置可以跳跃的最大长度。
 * 你的目标是使用最少的跳跃次数到达数组的最后一个位置。
 * 示例:
 *  输入: [2,3,1,1,4]
 *  输出: 2
 *  解释: 跳到最后一个位置的最小跳跃数是 2。
 *      从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
 * 说明:
 *  假设你总是可以到达数组的最后一个位置。
 */
#include <vector>
using namespace std;

//贪心算法, 从可以跳的范围内, 找到能够让我们跳更远的地方作为下一次的出发点
class Solution {
public:
    int jump(vector<int>& nums) {
        int size = nums.size();
        if (size < 2) return 0;
        //jump为返回的答案, curEnd代表当前的出发点, max_jump代表下一次循环出发点能够到达的最远地方
        int jump = 0, curEnd = 0, max_jump = 0;
        while (nums[curEnd]+curEnd < size-1) {  //检查当前位置是否可以直接跳到终点, 是的话退出循环并返回jump+1
            int idx = curEnd;   //下一跳的位置
            for (int i = 0; i <= nums[curEnd] && curEnd+i < size; i++) {
                //遍历当前的跳跃范围, 选取点A, 使得从点A出发, 能够跳到最远的距离
                if ((nums[curEnd+i]+curEnd+i) >= max_jump) {
                    max_jump = nums[curEnd+i]+curEnd+i;
                    idx = curEnd+i;
                }
            }
            curEnd = idx;
            jump++;
            if (curEnd >= size-1) return jump;  //检查是否已经跳到终点, 是的话直接返回jump
        }
        return jump+1;
    }
};