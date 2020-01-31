#include <vector>
using namespace std;

/* Leetcode 118.杨辉三角
 * 给定一个非负整数 numRows，生成杨辉三角的前numRows行
 */
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> triangle;
        if (!numRows) return triangle;
        triangle.emplace_back(1, 1);
        for (int i = 2; i <= numRows; i++) {
            vector<int> v(i);
            v[0] = v[i-1] = 1;
            vector<int> prev = triangle.back();
            for (int j = 1; j < i-1; j++) {
                v[j] = prev[j-1] + prev[j];
            }
            triangle.push_back(v);
        }
        return triangle;
    }
};

/* Leetcode 119.杨辉三角2
 * 给定一个非负索引k，其中k <= 33,返回杨辉三角的第k行
 * 示例:
 *  输入: 3
 *  输出: [1,3,3,1]
 * 要求空间复杂度为O(k)
 */
class Solution2 {
public:
    //动态规划中优化空间复杂度的方法
    vector<int> getRow(int rowIndex) {
        vector<int> row(rowIndex+1, 0);
        row[0] = 1;
        for (int i = 2; i <= rowIndex+1; i++)
            for (int j = i-1; j >= 1; j--)
                row[j] += row[j-1];
        return row;
    }
};