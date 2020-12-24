/**
 * Leetcode 1036. 逃离大迷宫
 * 在一个 10^6 x 10^6 的网格中，每个网格块的坐标为 (x, y)，其中 0 <= x, y < 10^6。
 * 我们从源方格 source 开始出发，意图赶往目标方格 target。每次移动，
 * 我们都可以走到网格中在四个方向上相邻的方格，只要该方格不在给出的封锁列表 blocked 上。
 * 只有在可以通过一系列的移动到达目标方格时才返回 true。否则，返回 false。
 *  
 * 示例 1：
 * 输入：blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
 * 输出：false
 * 解释：从源方格无法到达目标方格，因为我们无法在网格中移动。
 */
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

#define SIZE 1000000

struct pair_hash {	
	inline size_t operator()(const pair<int, int>& p) const {
        /* 先转化为uint64, 防止溢出 */
		return (uint64_t)p.first * SIZE + p.second;
	}
};

/**
 * 思路:
 * blocked能封锁最大的面积是 (blocked.size()) * (blocked.size() - 1) / 2
 * 即, blocked以对角线方式排列, 与矩阵两条边形成一个三角形
 * (封锁面积为一个等差数列求和, 画个图就知道了)
 * 
 * 例如:
 * ------------------
 * |            b       
 * |[source]  b           
 * |        b
 * |      b   [target]
 * |    b
 * |  b
 * |b
 * 
 * 如果从 开始-->目标 能走的面积大于这个数, 并且从 目标-->开始 能走的面积大于这个数,  
 * (因为目标也可能被blocked包围,双向检测), 则为true.
 */
class Solution {
public:
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        if (blocked.empty()) return true;
        /* 能够封锁的最大面积 */
        int max_area = (blocked.size()) * (blocked.size() - 1) / 2;
        /* blocked格子转化为set, 加速查找 */
        unordered_set<pair<int, int>, pair_hash> set;
        for (auto& b : blocked) {
            set.insert({b[0], b[1]});
        }
        /* 双向bfs, 因为目标点也可能被封锁住 */
        return bfs(source, target, set, max_area) && bfs(target, source, set, max_area);
    }
private:
    int direction[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    bool bfs(vector<int>& source, vector<int>& target, 
            unordered_set<pair<int, int>, pair_hash>& blocked, int max_area) {
        queue<pair<int, int>> q;
        unordered_set<pair<int, int>, pair_hash> visited;
        q.push({source[0], source[1]});
        visited.insert({source[0], source[1]});
        /* 当前已经走过的面积 */
        int area = 1; 
        while (!q.empty()) {
            /* 已经走过的面积大于最大封锁面积, 肯定能到达终点 */
            if (area > max_area) return true;
            auto p = q.front(); q.pop();
            int x = p.first, y = p.second;
            /* 已经到达终点, 直接返回 */
            if (x == target[0] && y == target[1]) return true;
            for (auto& d : direction) {
                int i = x + d[0], j = y + d[1];
                if (i >= 0 && j >= 0 && i < SIZE && j < SIZE) {
                    pair<int, int> next(i, j);
                    if (blocked.find(next) == blocked.end() && 
                            visited.find(next) == visited.end()) {
                        /* 能够到达下一个格子, 走过的面积加一 */
                        q.push(next);
                        visited.insert(next);
                        area++;
                    }
                }
            }
        }
        /* 还没到达终点并且走过的面积小于最大封锁面积, 肯定被封锁住了 */
        return false;
    }
};