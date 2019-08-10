/* Leetcode 74 搜索二维矩阵
 * 编写一个高效的算法来判断 m x n 矩阵中，是否存在一个目标值。该矩阵具有如下特性:
 * 1.每行中的整数从左到右按升序排列
 * 2.每行的第一个整数大于前一行的最后一个整数
 * 示例 1
 * 输入:
 * matrix =
 * [
 *  [1,   3,  5,  7],
 *  [10, 11, 16, 20],
 *  [23, 30, 34, 50]
 * ]
 * target = 3
 * 输出: true
 */

#include <vector>
#include <algorithm>
using namespace std;

//思路1: 首先确定目标在哪一行, 然后再使用二分查找
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty()) return false;
        int r = matrix.size();
        int c = matrix[0].size();
        int row = -1;
        for (int i = 0; i < r; i++) {
            int first = matrix[i][0];
            int last = matrix[i][c-1];
            if (first <= target && target <= last) {
                row = i;
                break;
            }
        }
        if (row == -1) return false;
        return binary_search(matrix[row].begin(), matrix[row].end(), target);
    }
};

//思路2: 将二维数组看成一个一维数组, 就是标准的二分查找
class Solution2 {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;
        int r = matrix.size(), c = matrix[0].size();
        int left = 0, right = r * c - 1;    //初始化left为第一个元素, right为最后一个元素
        int pivotIdx, pivotEle; //一维数组中的坐标和对应的元素
        while (left <= right) {
            pivotIdx = (left + right) / 2;
            pivotEle = matrix[pivotIdx / c][pivotIdx % c];
            if (pivotEle == target)
                return true;
            else if (pivotEle > target)
                right = pivotIdx - 1;
            else if (pivotEle < target)
                left = pivotIdx + 1;
        }
        return false;
    }
private:
    //递归版本的二分查找
    bool binarySearch(int left, int right, vector<vector<int>>& matrix, int target) {
        if (left <= right) {
            int col = matrix[0].size();
            int idx = (left + right) / 2;
            int ele = matrix[idx / col][idx % col];
            if (ele == target)
                return true;
            else if (ele > target)
                return binarySearch(left, idx-1, matrix, target);
            else
                return binarySearch(idx+1, right, matrix, target);
        }
        return false;
    }
};