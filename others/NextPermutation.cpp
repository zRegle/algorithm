/* Leetcode 31 下一个排列
 * 实现获取下一个排列的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。(即比它大的排列里最小的数列)
 * 如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。
 * 必须原地修改，只允许使用额外常数空间。
 * 以下是一些例子，输入位于左侧列，其相应输出位于右侧列。
 * 1,2,3 → 1,3,2
 * 3,2,1 → 1,2,3
 * 1,1,5 → 1,5,1
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* 思路:
 * 1.以数列尾部为终点, 寻找最短的不是(递减或者不增)的数列段
 * 2.将数列段的首位i与数列中某个数字j交换,需满足条件:
 *   (1)比i大
 *   (2)满足条件(1)中的数字中最小的数字
 *   (3)满足(1)(2)条件的数字中最靠近尾端的数字
 * 3.将交换的数列段反转, 除了数列段的首位
 */
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int size = nums.size();
        int idx = size - 1;
        //首先判断整个排列是否为不递增数列
        //1.如果是, 那么没有下一个排列, 直接反转
        //2.如果有, 则记录下目标数列段的首位位置i, 此时有a[i-1] < a[i]
        for (; idx > 0; idx--) {
            if (nums[idx - 1] < nums[idx])
                break;
        }
        if (!idx) {
            reverse(nums.begin(), nums.end());
            return;
        }
        //寻找比i大的最小值
        int minIdx = idx;   //目标数字j的位置
        int min = nums[idx];    //目标数字j
        for (int i = idx; i < size; ++i) {
            //nums[i] > nums[idx - 1]对应条件(1)
            //nums[i] < min 对应条件(2)
            //nums[i] < min 加上等于对应条件(3)
            if (nums[i] <= min && nums[i] > nums[idx - 1]) {
                minIdx = i;
                min = nums[i];
            }
        }
        //交换位置
        int tmp = nums[minIdx];
        nums[minIdx] = nums[idx - 1];
        nums[idx - 1] = tmp;
        //因为a[i-1] < a[i], 而a[i-1]右边是递减数列, 所以交换过后只需简单的反转就可得到答案
        reverse(nums.begin()+idx, nums.end());
    }
};