/**
 * Leetcode 778. 水位上升的泳池中游泳
 * 在一个 N x N 的坐标方格 grid 中，每一个方格的值 grid[i][j] 表示在位置 (i,j) 的平台高度。
 * 现在开始下雨了。当时间为 t 时，此时雨水导致水池中任意位置的水位为 t 。
 * 
 * 你可以从一个平台游向四周相邻的任意一个平台，但是前提是此时水位必须同时淹没这两个平台。
 * 假定你可以瞬间移动无限距离，也就是默认在方格内部游动是不耗时的。
 * 当然，在你游泳的时候你必须待在坐标方格里面。
 * 
 * 你从坐标方格的左上平台 (0，0) 出发。最少耗时多久你才能到达坐标方格的右下平台 (N-1, N-1)？
 * 
 * 示例:
 *  输入:
 *   (0)  (1)  (2)  (3)   (4)
 *   24   23   22   21    (5)
 *   (12) (13) (14) (15) (16)
 *   (11) 17   18   19    20
 *   (10) (9)  (8)  (7)   (6)
 *  输出: 16
 *  解释: 最终的路线用'()'进行了标记。我们必须等到时间为 16，
 *        此时才能保证平台 (0, 0) 和 (4, 4) 是连通的
 */
#include <vector>
#include <stack>
using namespace std;

/**
 * 二分搜索 + dfs - dfs判断是否能够到达终点, 二分搜索求最优值
 * 由题意可知, 最终我们一定能够达到(n-1, n-1)
 * 需要花费的时间区间为[grid(0, 0), n * n - 1](最少需要等到水位淹没(0, 0))
 * 那么我可以二分搜索枚举时间T, 如果在时限T内, 能够到达(n-1, n-1), 则继续二分搜索
 * 直到T刚好满足为止, 即为答案
 */
class Solution {
public:
    int direction[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        int l = grid[0][0], r = n * n - 1;
        vector<int> vis(n * n, 0);
        while (l < r) {
            /* 二分枚举时间T, 判断时限T内能否到达目的地 */
            int m = (l + r) >> 1;
            if (dfs(m, n, grid))
                /* 能够到达, 缩小右边界
                 * 注意不能是r = m - 1
                 * 因为m可能就是最优值
                 */
                r = m;
            else
                /* 不能到达, 放大左边界
                 * 因为m肯定不能到达, 所以可以直接略过m
                 */
                l = m + 1;
        }
        return l;
    }

    /**
     * dfs判断从(0, 0)出发, 最多经过T时间后, 能否到达(n-1, n-1)
     * \param T 时限
     * \param n 节点个数
     * \param grid 网格
     */
    bool dfs(int T, int n, vector<vector<int>>& grid) {
        vector<int> vis(n * n, 0);
        /* 用栈来手动模拟递归 */
        stack<int> stk;
        stk.push(0), vis[0] = 1;
        while (!stk.empty()) {
            int pos = stk.top(); stk.pop();
            int x = pos / n, y = pos % n;
            if (x == n - 1 && y == n - 1) return true;
            vis[pos] = 1;
            for (auto& d : direction) {
                int i = x + d[0], j = y + d[1];
                if (i >= 0 && j >= 0 && i < n && j < n) {
                    if (grid[i][j] <= T) {
                        /* 经过T时间后, 水位已经淹没(i, j) */
                        int npos = i * n + j;
                        if (vis[npos] == 0) {
                            vis[npos] = 1;
                            stk.push(npos);
                        }
                    }
                }
            }
        }
        return false;
    }
};