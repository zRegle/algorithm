/* Leetcode 42. 接雨水
 * 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
 * 输入: [0,1,0,2,1,0,1,3,2,1,2,1]
 * 输出: 6
 */

#include <iostream>
#include <vector>
using namespace std;

//思路:计算每一列能存多少水
//例如, 第i列能存的水=min(i列的左边的最高高度, i列右边的最高高度)-i列的高度
class Solution {
public:
    int trap(vector<int>& height) {
        int i = 0, j = height.size()-1;
        int max_left = 0, max_right = 0;    //某一列的左右两边的最高高度
        int water = 0;
        while (i < j) {
            if (height[i] <= height[j]) {
                //因为max_left和max_right是分别由i和j决定的
                //所以当height[i] <= height[j]时, 必定有max_left <= max_right
                if (height[i] >= max_left)
                    //左边没有比它更高的边, 所以装不了水, 更新max_left即可
                    max_left = height[i];
                else
                    water += max_left - height[i];
                i++;
            } else {
                if (height[j] >= max_right)
                    max_right = height[j];
                else
                    water += max_right - height[j];
                j--;
            }
        }
        return water;
    }
};