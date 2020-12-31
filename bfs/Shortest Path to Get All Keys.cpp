/**
 * Leetcode 864. 获取所有钥匙的最短路径
 * 给定一个二维网格 grid。 "." 代表一个空房间， "#" 代表一堵墙， 
 * "@" 是起点，（"a", "b", ...）代表钥匙，（"A", "B", ...）代表锁。
 * 
 * 我们从起点开始出发，一次移动是指向四个基本方向之一行走一个单位空间。
 * 我们不能在网格外面行走，也无法穿过一堵墙。如果途经一个钥匙，我们就把它捡起来。
 * 除非我们手里有对应的钥匙，否则无法通过锁。
 * 
 * 假设 K 为钥匙/锁的个数，且满足 1 <= K <= 6，字母表中的前 K 个字母在网格中都有自己对应的一个小写和一个大写字母。
 * 换言之，每个锁有唯一对应的钥匙，每个钥匙也有唯一对应的锁。
 * 另外，代表钥匙和锁的字母互为大小写并按字母顺序排列。
 * 返回获取所有钥匙所需要的移动的最少次数。如果无法获取所有钥匙，返回 -1 。
 *  
 * 示例 1：
 * 输入：["@.a.#","###.#","b.A.B"]
 * 输出：8
 */
#include <string>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        row = grid.size(), col = grid[0].length();
        int x, y;
        //确定起点和钥匙数量
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (grid[i][j] == '@') 
                    x = i, y = j;
                else if (isKey(i, j, grid)) 
                    keys_cnt++;
            }
        }

    out:
        //设置掩码
        all_keys = (1 << keys_cnt) - 1;

        int node = makeNode(x, y, 0);
        queue<int> q; 
        q.push(node);
        /**
         * 一共有row * col个格子, 每个格子有2^keys个状态
         * 因此一共有(row * col * 2^keys)个元素
         * PS: 不要使用unordered_set, leetcode上运算时间差了很多
         */
        vector<int> vis(row * col << keys_cnt, 0); 
        vis[node] = 0;

        int cnt = 0;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                int node = q.front(); q.pop();
                int pos = getPos(node), state = getState(node);
                x = pos / col, y = pos % col;
                if (isKey(x, y, grid))
                    //当前格子有key, 获取
                    setKey(state, grid[x][y] - 'a');
                if (state == all_keys)
                    //获取完所有的key
                    return cnt;
                for (auto& d : direction) {
                    int i = x + d[0], j = y + d[1];
                    if (isValid(i, j, grid)) {
                        if (isLock(i, j, grid)) {
                            int lock = grid[i][j] - 'A';
                            if (!hasKey(state, lock))
                                continue;
                        }
                        int next = makeNode(i, j, state);
                        if (vis[next] == 0) {
                            vis[next] = 1;
                            q.push(next);
                        }
                    }
                }
            }
            cnt++;
        }
        return -1;
    }
private:
    int row, col;
    /**
     * key掩码: 用于获取当前总共拿到多少钥匙
     * 网格中有多少把钥匙就有多少个1, 例如一共有3把钥匙
     * all_keys = 111
     */
    int all_keys;
    int keys_cnt = 0;
    int direction[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    inline int makeNode(int x, int y, int state) {
        /**
         * node低位的keys_cnt个bit表示是否持有对应钥匙
         * 
         * 例如 row = 5, col = 4, 一共有a, b, c 3把钥匙
         * 当前在(1, 3), 持有钥匙a和c
         * 那么node = (1 * 5 + y) << 3 | 5(二进制为101)
         */
        return x * col + y << keys_cnt | state;
    }
    inline int getState(int node) {
        //获取node低位的keys_cnt个bit
        return node & all_keys;
    }
    inline int getPos(int node) {
        return node >> keys_cnt;
    }
    inline bool hasKey(int state, int lock) {
        //判断是否持有对应lock的钥匙
        return state & (1 << lock);
    }
    inline void setKey(int& state, int key) {
        //获取key
        state |= (1 << key);
    }
    inline bool isValid(int x, int y, vector<string>& grid) {
        return x >= 0 && y >= 0 && x < row && y < col && grid[x][y] != '#';
    }
    inline bool isKey(int x, int y, vector<string>& grid) {
        return 'a' <= grid[x][y] && grid[x][y] <= 'f';
    }
    inline bool isLock(int x, int y, vector<string>& grid) {
        return 'A' <= grid[x][y] && grid[x][y] <= 'F';
    }
};