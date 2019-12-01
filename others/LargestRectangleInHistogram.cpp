/* Leetcode 84.柱状图中最大的矩形
 * 给定n个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为1.
 * 求在该柱状图中，能够勾勒出来的矩形的最大面积.
 * 示例:
 *  输入: [2,1,5,6,2,3]
 *  输出: 10(5和6组成最大矩形)
 */
#include <iostream>
#include <climits>
#include <stack>
#include <vector>
using namespace std;

//将h[i]作为最矮的bar, 计算它的最大面积, 这样遍历一遍数组就行了
//h[i]作为最矮的bar的面积如何计算?
//找到它左边第一个比h[i]矮的bar坐标记为left, 右边第一个比h[i]矮的bar坐标记为right
//area = (right-left-1) * h[i]
class Solution {
public:
    int largestRectangleArea(vector<int>& h) {
        if (h.empty()) return 0;
        int area = 0, size = h.size();
        stack<int> s;
        int i = 0;
        while(i < size) {
            //递增高度则入栈
            if (s.empty() || h[i] >= h[s.top()])
                s.push(i++);
            else {
                //h[i] < h[s.top()], s.top()右边第一个低过它的就是i
                //因为之前是按递增高度入栈的, 那么s.top()左边第一个低过它的就是s.top()出栈后的下一个栈顶元素
                int idx = s.top(); s.pop();
                //如果栈空了, 说明从0出发到i-1都是递增高度, h[0] > h[i], 所以此时宽度为i
                area = max(area, h[idx] * (s.empty() ? i : i-s.top()-1));
            }
        }
        //栈里还有bar, 清空一下
        while (!s.empty()) {
            int idx = s.top(); s.pop();
            area = max(area, h[idx] * (s.empty() ? i : i-s.top()-1));
        }
        return area;
    }
};

//暴力递归求解, 勉强AC
class Solution2 {
public:
    int largestRectangleArea(vector<int>& heights) {
        if (heights.empty()) return 0;
        int area = -1;
        getArea(heights, 0, heights.size()-1, area);
        return area;
    }
private:
    //递归的复杂度是logn, 获取最低高度的坐标复杂度是n
    //整个复杂度是O(nlogn)
    void getArea(vector<int>& h, int start, int end, int& area) {
        if (start <= end) {
            int idx = getMinHeightIdx(h, start, end);
            int curArea = (end - start + 1) * h[idx];
            area = max(area, curArea);
            //left
            getArea(h, start, idx-1, area);
            //right
            getArea(h, idx+1, end, area);
        }
    }

    int getMinHeightIdx(vector<int>& h, int start, int end) {
        int minHeightIdx = start, minHeight = INT_MAX;
        for (int i = start+1; i <= end; i++) {
            if (h[i] < minHeight) {
                minHeight = h[i];
                minHeightIdx = i;
            }
        }
        return minHeightIdx;
    }
};

int main() {
    int a[] = {2,1,5,6,2,3};
    vector<int> h(a, a+6);
    Solution s;
    cout<<s.largestRectangleArea(h);
    return 0;
}