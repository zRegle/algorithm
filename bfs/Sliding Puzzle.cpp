/**
 * Leetcode 773. 滑动谜题
 * 在一个 2 x 3 的板上（board）有 5 块砖瓦，用数字 1~5 来表示, 以及一块空缺用 0 来表示.
 * 一次移动定义为选择 0 与一个相邻的数字（上下左右）进行交换.
 * 最终当板 board 的结果是 [[1,2,3],[4,5,0]] 谜板被解开。
 * 给出一个谜板的初始状态，返回最少可以通过多少次移动解开谜板，如果不能解开谜板，则返回 -1 。
 *
 * 示例：
 *  输入：board = [[1,2,3],[4,0,5]]
 *  输出：1
 *  解释：交换 0 和 5 ，1 步完成
 *
 *  输入：board = [[1,2,3],[5,4,0]]
 *  输出：-1
 *  解释：没有办法完成谜板
 *
 *  输入：board = [[4,1,2],[5,0,3]]
 *  输出：5
 *  解释：
 *   最少完成谜板的最少移动次数是 5 ，
 *   一种移动路径:
 *   尚未移动: [[4,1,2],[5,0,3]]
 *   移动 1 次: [[4,1,2],[0,5,3]]
 *   移动 2 次: [[0,1,2],[4,5,3]]
 *   移动 3 次: [[1,0,2],[4,5,3]]
 *   移动 4 次: [[1,2,0],[4,5,3]]
 *   移动 5 次: [[1,2,3],[4,5,0]]
 *
 *  输入：board = [[3,2,4],[1,5,0]]
 *  输出：14
 *
 * 提示：
 * (1)board 是一个如上所述的 2 x 3 的数组.
 * (2)board[i][j] 是一个 [0, 1, 2, 3, 4, 5] 的排列.
 */
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>
using namespace std;

/**
 * 朴素的bfs, 滑板的状态用字符串表示
 * 例如[[3,2,4],[1,5,0]]就是"324150"
 */
class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        int m = board.size(), n = board[0].size();
        string initial, target = "123450";
        /* 构建初始状态 */
        for (auto& r : board) {
            for (int digit : r) {
                initial += (char)(digit + '0');
            }
        }
        queue<string> q;
        unordered_set<string> visit;
        q.push(initial); visit.insert(initial);
        int level = 0;
        int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                string s = q.front(); q.pop();
                if (s == target)
                    return level;
                /* 找到'0'的坐标 */
                int pos = s.find('0');
                int x = pos / n, y = pos % n;
                for (auto& d : dirs) {
                    int nx = x + d[0], ny = y + d[1];
                    if (nx >= 0 && ny >= 0 && nx < m && ny < n) {
                        int npos = nx * n + ny;
                        swap(s[pos], s[npos]);
                        if (visit.find(s) == visit.end()) {
                            visit.insert(s);
                            q.push(s);
                        }
                        swap(s[pos], s[npos]);
                    }
                }
            }
            level++;
        }
        return -1;
    }
};