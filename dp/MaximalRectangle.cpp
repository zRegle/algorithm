//
// Created by Administrator on 2018/8/4.
//
#include <iostream>
#include <vector>
#include <climits>
#include <string>
using namespace std;

/*
 * leetcode 85: maximal rectangle
 * 给定一个01矩阵, 求只包含1的最大面积矩形
 * 思路:
 * height代表这一列的最大高度
 * left, right数组分别代表这一列在高度不为0时, 向左右两边扩展能够扩展到最远的坐标
 * 给定一个一行中的某一列, 面积有:
 * right[j] - left[j] * height[j]
 */

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size();
        if (m == 0) return 0;
        int n = matrix[0].size();
        int* left = new int[n+1], *right = new int[n+1], *height = new int[n+1];
        fill_n(left, n, 0); fill_n(right, n, n); fill_n(height, n, 0);  //初始化
        int max_area = -1;
        for (int i = 0; i < m; ++i) {
            //分别代表只考虑当前行, 所能扩展到最远的坐标, 初始化的值解释见下
            int cur_left = 0, cur_right = n;
            for (int j = 0; j < n; ++j)
                height[j] = matrix[i][j] == '1' ? height[j] + 1 : 0;
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == '1')
                    //将上一行的当前列跟这一行的能够向左扩展的最远坐标比较
                    //取较大值, 即取坐标靠右的值, 确保当前列及上一行的这一列的值都是1
                    left[j] = max(left[j], cur_left);
                else {
                    //如果不是'1'
                    left[j] = 0;    //取0, 为下一行做准备, 不用担心面积会搞错, 因为高度为0
                    cur_left = j + 1;   //这一行的接下来的几列, 最多只能向左扩展到j + 1
                }
            }
            for (int j = n-1; j >= 0; --j) {
                if (matrix[i][j] == '1')
                    //将上一行的当前列跟这一行的能够向右扩展的最远坐标比较
                    //取较小值, 即取坐标靠左的值, 确保当前列及上一行的这一列的值都是1
                    right[j] = min(right[j], cur_right);
                else {
                    //如果不是'1'
                    right[j] = n;   //取n, 为下一行做准备, 不用担心面积会搞错, 因为高度为0
                    cur_right = j;  //这一行的接下来的几列, 最多只能向右扩展到j
                    //按照上一个循环, 应该这样算才对:
                    //right[j] = n - 1; cur_right = j - 1;
                    //这是因为如果遇到'0','1','0', 遇到左边的那个0时, cur_left = '1'的位置
                    //遇到右边那个0时, cur_right = '1'的位置, 那么这时面积就为0了, 所以需要考虑right - left的有效性
                }
            }
            for (int j = 0; j < n; ++j)
                max_area = max(max_area, (right[j] - left[j]) * height[j]);
        }
        delete[](left); delete[](right); delete[](height);
        return max_area;
    }
};

int main() {
    Solution solution;
    return 0;
}