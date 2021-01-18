/**
 * Leetcode 526. 优美的排列
 * 假设有从 1 到 N 的 N 个整数，如果从这 N 个数字中成功构造出一个数组，
 * 使得数组的第 i 位 (1 <= i <= N) 满足如下两个条件中的一个，
 * 我们就称这个数组为一个优美的排列。条件：
 *  (1)第 i 位的数字能被 i 整除
 *  (2)i 能被第 i 位上的数字整除
 *
 * 现在给定一个整数 N，请问可以构造多少个优美的排列？
 *
 * 示例1:
 * 输入: 2
 * 输出: 2
 * 解释:
 *  第 1 个优美的排列是 [1, 2]:
 *   第 1 个位置（i=1）上的数字是1，1能被 i（i=1）整除
 *   第 2 个位置（i=2）上的数字是2，2能被 i（i=2）整除
 *  第 2 个优美的排列是 [2, 1]:
 *   第 1 个位置（i=1）上的数字是2，2能被 i（i=1）整除
 *   第 2 个位置（i=2）上的数字是1，i（i=2）能被 1 整除
 */
#include <vector>
using std::vector;

/* dp方法查看dp文件夹 */

/* 简单的dfs回溯, 没啥好说的 */
class Solution {
public:
    int countArrangement(int n) {
        used.resize(n + 1, 0);
        dfs(1, n);
        return cnt;
    }

private:
    int cnt = 0;
    vector<int> used;
    void dfs(int idx, int n) {
        if (idx > n) {
            cnt++;
            return;
        }
        for (int i = 1; i <= n; i++) {
            if (i % idx == 0 || idx % i == 0) {
                if (used[i] == 0) {
                    used[i] = 1;
                    dfs(idx + 1, n);
                    used[i] = 0; /* 回溯 */
                }
            }
        }
    }
};