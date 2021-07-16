/* Leetcode 240.搜索二维矩阵 II
 * 编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target。
 * 该矩阵具有以下特性：
 * (1)每行的元素从左到右升序排列。
 * (2)每列的元素从上到下升序排列。
 * 示例:
 * 现有矩阵 matrix 如下：
 *  [
 *      [1,   4,  7, 11, 15],
 *      [2,   5,  8, 12, 19],
 *      [3,   6,  9, 16, 22],
 *      [10, 13, 14, 17, 24],
 *      [18, 21, 23, 26, 30]
 *  ]
 * 给定 target = 5，返回 true。
 * 给定 target = 20，返回 false。
 */
#include <iostream>
#include <vector>
using namespace std;

/* 初始坐标可以为左下角或者右上角, 这里以左下角为例
 * 如果matrix[i][j] > target就上移
 * 否则就右移, 直到找到为止
 *
 * 为什么从左下或者右上开始, 而不从左上或者右下开始?
 *  (1)假设我们从左上角开始, 遇到matrix[i][j] < target时,
 *     我们就有两种选择, 下移或者右移
 *     如果我们选择了下移, 那么target可能就在下移后位置的左边
 *     如果我们选择了右移, 那么target可能就在右移前位置的下面
 *     总而言之, 我们无法从matrix[i][j] < target这个信息中获取足够的剪枝信息. 从右下开始也同理
 *  (2)但是如果我们从左下开始, 遇到matrix[i][j] < target时,
 *     我们必然知道matrix[i][j]的上面肯定都小于target, 我们只能右移或者下移
 *     但是下移是不正确的, 因为matrix[i][j]必然是从第i+1行转移来的, 假设在matrix[i+1][j']时转移到第i行
 *     那么表明之前发现了matrix[i+1][j'] = val > target(j > j')了, 如果我们在matrix[i][j]时下移,
 *     就必然有matrix[i+1][j] > matrix[i+1][j'] > target
 *     所以向下转移是错误的, 因此我们只能右移
 * 
 *     同理, 如果matrix[i][j] > target, 那么matrix[i][j]的右面肯定都大于target, 我们只能上移或者左移
 *     但是我们左移是不对的, 因为matrix[i][j]必然从matrix[i-1][j]转移过来, 为什么matrix[i-1][j]需要转移?
 *     很明显, 因为matrix[i-1][j] < target, 所以我们左移是没道理的, 因此上移
 */

/* 更形象的解释:
 * 假设我们从右上角开始, 我们可以将矩阵逆时针旋转45度
 * 以右上角为根节点, 将整个矩阵看成一棵二叉搜索树
 * 图解:
 * https://leetcode-cn.com/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/solution/mian-shi-ti-04-er-wei-shu-zu-zhong-de-cha-zhao-zuo/ */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row = matrix.size();
        if (row == 0) return false;
        int col = matrix[0].size();
        int i = row-1, j = 0;
        while (i >= 0 && j < col) {
            if (matrix[i][j] == target)
                return true;
            if (matrix[i][j] > target)
                i--;
            else
                j++;
        }
        return false;
    }
};