/**
 * Leetcode 959. 由斜杠划分区域
 * 在由 1 x 1 方格组成的 N x N 网格 grid 中，每个 1 x 1 方块由 /、\ 或空格构成。
 * 这些字符会将方块划分为一些共边的区域，返回区域的数目。
 * 图片描述；https://leetcode-cn.com/problems/regions-cut-by-slashes/
 */
#include <string>
#include <vector>
#include "DSU.h"
using namespace std;

/* 将每个格子看成左右两个区域, 设(i, j)的两个区域分别为left(i, j)和right(i, j)
 * 那么如下(画个图就知道了):
 * (i, j) = ' '时, left(i, j)与right(i, j)相连
 *
 * (i, j) = '/'时:
 *      (i-1, j) = ‘/'时, right(i, j)与left(i-1, j)相连
 *      (i-1, j) = '\'时, right(i, j)与right(i-1, j)相连
 *      (i-1, j) = ' '时, right(i, j)与(i-1, j)两个区域都相连
 * (i, j) = '\'时:
 *      (i-1, j) = ‘/'时, left(i, j)与left(i-1, j)相连
 *      (i-1, j) = '\'时, left(i, j)与right(i-1, j)相连
 *      (i-1, j) = ' '时, left(i, j)与(i-1, j)两个区域都相连
 * (i, j) = ' '时:
 *      (i-1, j) = ‘/'时, (i, j)两个区域都与left(i-1, j)相连
 *      (i-1, j) = '\'时, (i, j)两个区域都与right(i-1, j)相连
 *      (i-1, j) = ' '时, (i, j)两个区域都与(i-1, j)两个区域相连
 *
 * 无论什么情况下, left(i, j)都与right(i, j-1)相连
 *
 * 按照以上思路, 进行并查集即可
 */
class Solution {
public:
    int regionsBySlashes(vector<string>& grid) {
        n = grid.size();
        DSU dsu(n * n << 1);
        int component = n * n << 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == ' ')
                    component -= dsu.merge(left(i, j), right(i, j));
                if (i > 0)
                    /* up */
                    component -= merge_up(i, j, grid, dsu);
                if (i < n - 1)
                    /* down */
                    component -= merge_up(i+1, j, grid, dsu);
                if (j > 0)
                    /* left */
                    component -= merge_left(i, j, grid, dsu);
                if (j < n - 1)
                    /* right */
                    component -= merge_left(i, j+1, grid, dsu);
            }
        }
        return component;
    }

private:
    int n;
    /* (i, j)与(i-1, j)合并 */
    int merge_up(int i, int j, vector<string>& grid, DSU& dsu) {
        int cnt;
        if (grid[i][j] == '\\') {
            if (grid[i-1][j] == '\\')
                /* 当前格子的右边与上面格子的左边 */
                cnt = dsu.merge(right(i, j), left(i-1, j));
            else
                /* 上一个格子可能是'/'或者' '
                 * 统一跟它的右边合并即可
                 */
                cnt = dsu.merge(right(i, j), right(i-1, j));
        } else if (grid[i][j] == '/') {
            if (grid[i-1][j] == '\\')
                /* 当前格子的左边与上面格子的左边 */
                cnt = dsu.merge(left(i, j), left(i-1, j));
            else
                /* 上一个格子可能是'/'或者' '
                 * 统一跟它的右边合并即可
                 */
                cnt = dsu.merge(left(i, j), right(i-1, j));
        } else {
            /* 当前格子为' ', 当前格子会先左右合并 */
            if (grid[i-1][j] == '\\')
                /* 当前格子的左边与上面格子的左边 */
                cnt = dsu.merge(left(i, j),  left(i-1, j));
            else
                /* 上一个格子可能是'/'或者' '
                 * 统一跟它的右边合并即可
                 */
                cnt = dsu.merge(left(i, j), right(i-1, j));
        }
        return cnt;
    }

    /* 合并(i, j)和(i, j-1) */
    int merge_left(int i, int j, vector<string>& grid, DSU& dsu) {
        /* 无论什么情况下, (i, j)的左边必定与(i, j-1)的右边相连 */
        return dsu.merge(left(i, j), right(i, j-1));
    }

    inline int left(int x, int y) const {
        return x * n + y << 1;
    }

    inline int right(int x, int y) const {
        return (x * n + y << 1) + 1;
    }
};

/* 更加优雅的做法, leetcode官解
 * 将一个格子两条对角线相连, 分成4个三角形, 按照顺时针的方式编码0, 1, 2, 3
 * 类似上面的思路进行并查集
 */
class Solution1 {
public:
    int regionsBySlashes(vector<string>& grid) {
        n = grid.size();
        DSU dsu(n * n << 2);
        int componet = n * n << 2;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int root = get_root(i, j);
                char c = grid[i][j];
                if (c != '\\') {
                    /* c == '/' || c == ' ' */
                    componet -= dsu.merge(root + 0, root + 3);
                    componet -= dsu.merge(root + 1, root + 2);
                }
                if (c != '/') {
                    /* c == '\' || c == ' ' */
                    componet -= dsu.merge(root + 0, root + 1);
                    componet -= dsu.merge(root + 2, root + 3);
                }
                if (i > 0)
                    /* north */
                    componet -= dsu.merge(root + 0, get_root(i-1, j) + 2);
                if (j < n - 1)
                    /* east */
                    componet -= dsu.merge(root + 1, get_root(i, j+1) + 3);
                if (i < n - 1)
                    /* south */
                    componet -= dsu.merge(root + 2, get_root(i+1, j) + 0);
                if (j > 0)
                    /* west */
                    componet -= dsu.merge(root + 3, get_root(i, j-1) + 1);
            }
        }
        return componet;
    }

private:
    int n;

    inline int get_root(int x, int y) const {
        return x * n + y << 2;
    }
};