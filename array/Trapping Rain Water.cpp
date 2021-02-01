#include <vector>
#include <stack>
using std::vector;
using std::stack;

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
 * 双指针法：
 * 
 * 我们先明确几个变量的意思：
 * 
 *  (1)left_max：左边的最大值，它是从左往右遍历找到的
 *  (2)right_max：右边的最大值，它是从右往左遍历找到的
 *  (3)left：从左往右处理的当前下标
 *  (4)right：从右往左处理的当前下标
 * 定理一：在某个位置i处，它能存的水，取决于它左右两边的最大值中较小的一个。
 * 
 * 定理二：当我们从左往右处理到left下标时，左边的最大值left_max对它而言是可信的，
 * 但right_max对它而言是不可信的。（见下图，由于中间状况未知，对于left下标而言，right_max未必就是它右边最大的值）
 *                                    right_max
 *  left_max                             __
 *    __                                |  |
 *   |  |__    __?????????????????????? |  |
 * __|     |__|                       __|  |__
 *         left                      right
 * 
 * 定理三：当我们从右往左处理到right下标时，右边的最大值right_max对它而言是可信的，但left_max对它而言是不可信的。
 * 
 * 对于位置left而言，它左边最大值一定是left_max，右边最大值"大于等于"right_max，
 * 这时候，如果left_max<right_max成立，那么它就知道自己能存多少水了。无论右边将来会不会出现更大的right_max，都不影响这个结果。 
 * 所以当left_max<right_max时，我们就希望去处理left下标，反之，我们希望去处理right下标。
 */
class TwoPointers {
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

/**
 * 韦恩图做法:
 * 参考链接: https://leetcode-cn.com/problems/trapping-rain-water/solution/wei-en-tu-jie-fa-zui-jian-dan-yi-dong-10xing-jie-j/
 */
class Venndiagram {
public:
    int trap(vector<int>& height) {
        int leftMax = 0, rightMax = 0;
        int len = height.size();
        int s1 = 0, s2 = 0;
        int sum = 0; /* 柱子面积 */
        for (int i = 0; i < len; i++) {
            leftMax = std::max(leftMax, height[i]);
            rightMax = std::max(rightMax, height[len-i-1]);
            s1 += leftMax;
            s2 += rightMax;
            sum += height[i];
        }
        return s1 + s2 - sum - leftMax * len;
    }
};

/**
 * 单调栈(栈中元素单调递增或递减)
 * 
 * 我们在遍历数组时维护一个栈。
 * 如果当前的条形块小于或等于栈顶的条形块，我们将条形块的索引入栈，
 * 意思是当前的条形块被栈中的前一个条形块界定(前一个条形块可能作为当前条形块的右边界)
 * 如果我们发现一个条形块长于栈顶，我们可以确定栈顶的条形块被当前条形块和栈的前一个条形块界定，
 * 因此我们可以弹出栈顶元素并且累加答案到 water 。
 */
class MonotonicStack {
public:
    int trap(vector<int>& height) {
        stack<int> stk;
        int cur = 0, water = 0;
        while (cur < height.size()) {
            /* 栈顶高度小于当前高度就一直循环 */
            while (!stk.empty() && height[cur] > height[stk.top()]) {
                /* 计算当前列能装多少水 */
                int idx = stk.top(); stk.pop();
                if (stk.empty()) break;
                /* 计算新的栈顶到当前下标的距离
                 * 因为是单调栈, 因此新的栈顶必定必height[idx]高
                 * 此时idx的左右两个边界分别是idx和cur
                 */
                int distance = cur - stk.top() - 1;
                /* 木桶原理, 选取最矮的那块板 */
                int min_height = std::min(height[stk.top()], height[cur]);
                water += distance * (min_height - height[idx]);
            }
        }
        stk.push(cur);
        cur++;
        return water;
    }
};