#include <iostream>
#include <vector>
using namespace std;

/*
 * leetcode 11. Container With Most Water
 * 给定一个数组, 每个元素代表一定的高度, 问最多能容纳多少水
 * 例如:
 * Input: [1,8,6,2,5,4,8,3,7]
 * Output: 49
 * 
 *   1         1
 *   1         1   1
 *   1 1       1   1
 *   1 1   1   1   1
 *   1 1   1 1 1   1
 *   1 1   1 1 1 1 1
 *   1 1 1 1 1 1 1 1
 * 1 1 1 1 1 1 1 1 1
 * 1 2 3 4 5 6 7 8 9 <- 横坐标  
 *
 * 选定元素2和元素9做容器壁时, 得最大面积49=7*7
 *
 * 两端两个指针分别遍历, 每次遍历取矮的那个作高
 * 比较两个容器壁, 较矮的那个向前移动
 */

class Solution {
public:
    int maxArea(vector<int>& height) {
        int max_area = 0;
        if (height.size() == 0) return 0;
        int i = 0, j = height.size()-1;
        while (i < j) {
            max_area = max(max_area, (j-i)*min(height[i], height[j]));
            if (height[i] > height[j]) j--;
            else i++; 
        }
        return max_area;
    }
};