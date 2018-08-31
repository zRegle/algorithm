#include <iostream>
#include <vector>
using namespace std;

/**
 * leetcode 42 Trapping Rain Water
 * 给定一个高度数组height, 每个元素代表一个height[i], 长度为1的方块
 * 问这个容器最多能容纳多少水
 * 例如:
 * Input: [0,1,0,2,1,0,1,3,2,1,2,1]
 *               1
 *       1 * * * 1 1 * 1
 *   1 * 1 1 * 1 1 1 1 1  1
 * 0 1 2 3 4 5 6 7 8 9 10 11 <-横坐标
 * (1代表实块, *代表水)
 * Output: 6
 */

/*
 * 思路1
 * 两个指针left, right分别从两边开始遍历, 各维护一个max_left, max_right变量
 * 这两个变量相当于容器的两面壁, 我们就分别在容器的左右边装水, 直到left与right相遇
 * 比如当height[left] <= height[right], 我们就在容器的左边装水, 即water += max_left - height[left]
 * 理解如下:
 * 我们在装水时, 需要确保max_left的另一面容器壁(max_right)的高度不小于max_left, 而在循环过程中,
 * 我们只有在height[left] <= height[right]时才会尝试在左边装水, 而max_left由left得出, 故必定满足条件.反过来如果去右边装水, 就不行了
 *
 * 第二点: 在循环过程中, max_left和max_right是不断变化的, 当它们发生变化时, 我们不用担心之前的装的水会漏出来
 * 因为原来的max_left肯定会比新的max_left要矮
 */
class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0, right = height.size()-1;
        int max_left = 0, max_right = 0;
        int water = 0;
        while (left < right) {
            if (height[left] <= height[right]) {
                if (height[left] > max_left) max_left = left;
                else water += max_left - height[left];
                left++;
            } else {
                if (height[right] > max_right) max_right = right;
                else water += max_right - height[right];
                right--;
            }
        }
        return water;
    }
};
