/* Leetcode 279. Perfect Squares
 * 给定一个数, 求出一系列平方数之和等于这个数的最少个数
 *
 * Input: n = 12
 * Output: 3
 * Explanation: 12 = 4 + 4 + 4.
 *
 * Input: n = 13
 * Output: 2
 * Explanation: 13 = 4 + 9.
 */
#include <vector>
#include <queue>
using namespace std;

/* 动态规划方法参考dp文件夹 */

/* 不断对队列元素加上平方数, 直到达到n */
class Solution {
public:
    int numSquares(int n) {
        queue<int> q; /* 每层树的节点队列 */
        q.push(0); /* 根节点 */
        vector<int> visited(n+1, 0);
        int level = 0; /* 树高 */
        int tmp;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                int x = q.front(); q.pop();
                if (x == n)
                    return level;
                for (int j = 1; (tmp = x + j * j) <= n; j++) {
                    if (visited[tmp] == 0) {
                        visited[tmp] = level;
                        q.push(tmp);
                    }
                }
            }
            level++;
        }
        return 0;
    }
};