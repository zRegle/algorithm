/**
 * 剑指 Offer 33. 二叉搜索树的后序遍历序列
 * 输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历结果。
 * 如果是则返回 true，否则返回 false。假设输入的数组的任意两个数字都互不相同。
 *
 * 参考以下这颗二叉搜索树：
 *      5
 *     / \
 *    2   6
 *   / \
 *  1   3
 * 示例 1：
 * 输入: [1,6,3,2,5]
 * 输出: false
 * 示例 2：
 *
 * 输入: [1,3,2,6,5]
 * 输出: true
 */
#include <vector>
using namespace std;

class Solution {
public:
    bool verifyPostorder(vector<int>& postorder) {
        return solve(0, postorder.size()-1, postorder);
    }

private:
    bool solve(int start, int end, vector<int>& postOrder) {
        if (start >= end)
            /* start == end: 只剩一个节点
             * start > end: 没有节点 */
            return true;
        int root = postOrder[end];
        /* 保证[start, mid)的元素小于root */
        int mid = start;
        while (postOrder[mid] < root) mid++;
        /* 保证[mid, end)的元素大于root */
        int tmp = mid;
        while (postOrder[tmp] > root) tmp++;
        /* 循环结束后, tmp应该等于end */
        if (tmp != end)
            return false;
        /* 递归左右子树 */
        return solve(start, mid-1, postOrder) && solve(mid, end-1, postOrder);
    }
};