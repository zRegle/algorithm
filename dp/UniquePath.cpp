/* Leetcode 62 不同路径
 * 一个机器人位于一个 m x n 网格的左上角
 * 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角
 * 问总共有多少条不同的路径？
 */
#include <vector>
using std::vector;

//明显要用dp
class Solution {
public:
    int uniquePaths(int m, int n) {
        //我们只需要存着上一行的结果就行
        vector<int> cur(m, 1);  //第一行路径条数都是1
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cur[j] = j > 0 ? cur[j-1] + cur[j] : cur[j];
            }
        }
        return cur[m-1];
    }
};