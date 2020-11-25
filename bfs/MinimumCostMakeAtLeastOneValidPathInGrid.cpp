/* Leetcode 1368.使网格图至少有一条有效路径的最小代价
 * 给你一个 m x n 的网格图grid。 grid中每个格子都有一个数字，对应着从该格子出发下一步走的方向。 
 * grid[i][j] 中的数字可能为以下几种情况：
 * 	1 - 下一步往右走，也就是你会从 grid[i][j] 走到 grid[i][j + 1]
 * 	2 - 下一步往左走，也就是你会从 grid[i][j] 走到 grid[i][j - 1]
 * 	3 - 下一步往下走，也就是你会从 grid[i][j] 走到 grid[i + 1][j]
 * 	4 - 下一步往上走，也就是你会从 grid[i][j] 走到 grid[i - 1][j]
 * 注意网格图中可能会有 无效数字 ，因为它们可能指向 grid 以外的区域。
 * 
 * 一开始，你会从最左上角的格子 (0,0) 出发。我们定义一条'有效路径'为从格子 (0,0) 出发，
 * 每一步都顺着数字对应方向走，最终在最右下角的格子 (m - 1, n - 1) 结束的路径。
 * ('有效路径'不需要是最短路径)
 * 
 * 你可以花费 cost = 1 的代价修改一个格子中的数字，但每个格子中的数字只能修改一次。
 * 
 * 请你返回让网格图至少有一条有效路径的最小代价。
 */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/* 思路:
 * 可以构建一个m x n个节点和不超过4mn条边的有向图 
 * 图中的每一个节点表示数组grid中的一个位置，它会向不超过4个相邻的节点各连出一条边，
 * 边的权值要么为0（移动方向与箭头方向一致），要么为1（移动方向与箭头方向不一致）
 * 然后求最短路径
 */

static constexpr int direction[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

/* 比较native的方法可以用dijkstra */
class Dijkstra {
public:
	int minCost(vector<vector<int>>& grid) {
		int m = grid.size(), n = grid[0].size();
		vector<int> dist(m * n, INT32_MAX);
		vector<int> visited(m * n, 0);
		dist[0] = 0;
		/* 优先级队列, 保证每次都当前取到最短距离的节点 
		 * pair.first = distance, pair.second = coordinate
		 */
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
		q.emplace(0, 0);

		while(!q.empty()) {
			/* 每次取当前最短距离的节点 */
			auto data = q.top(); q.pop();
			int cur_dist = data.first, cur_pos = data.second;
			if (visited[cur_pos]) continue;
			visited[cur_pos] = 1;
			int x = cur_pos / n, y = cur_pos % n;
			for (int i = 0; i < 4; i++) {
				int nx = x + direction[i][0], ny = y + direction[i][1];
				int npos = nx * n + ny;
				/* 如果grid[x][y]的方向与当前移动方向不一致, 则distance加一 */
				int ndist = cur_dist + (grid[x][y] != i + 1);
				/* 尝试更新到new pos的最短距离 */
				if (nx >= 0 && nx < m && ny >= 0 && ny < n && ndist < dist[npos]) {
					dist[npos] = ndist;
					q.emplace(ndist, npos);
				}
			}
		}
		return dist[m * n - 1];
	}
};

/* 0-1 BFS方法
 * 详细介绍在这https://codeforces.com/blog/entry/22276
 * 
 * BFS的正确性在于, 对于源点s以及任意两个节点u和v，如果dist(s, u) < dist(s, v)
 * (其中dist(x, y)表示从节点x到节点y的最短路长度)，那么节点 一定会比节点v先被取出队列
 * 
 * 在这里, 我们同样需要保证从队列中取出的节点, 它们与源点之间的距离是单调递增的.
 */
class BFS {
public:
	int minCost(vector<vector<int>>& grid) {
		int m = grid.size(), n = grid[0].size();
		vector<int> dist(m * n, INT32_MAX);
		vector<int> visited(m * n, 0);
		dist[0] = 0;
		/* 双向队列, 保证节点与源点距离单调递增, 与dijkstra中的优先队列作用相同 */
		deque<int> q;
		q.push_back(0);

		while(!q.empty()) {
			int cur_pos = q.front(); q.pop_front();
			if (visited[cur_pos]) continue;
			visited[cur_pos] = 1;
			int x = cur_pos / n, y = cur_pos % n;
			for (int i = 0; i < 4; i++) {
				int nx = x + direction[i][0], ny = y + direction[i][1];
				int npos = nx * n + ny;
				/* 如果grid[x][y]的方向与当前移动方向不一致, 则distance加一 */
				int ndist = dist[cur_pos] + (grid[x][y] != i + 1);
				/* 尝试更新到new pos的最短距离 */
				if (nx >= 0 && nx < m && ny >= 0 && ny < n && ndist < dist[npos]) {
					dist[npos] = ndist;
					if (grid[x][y] == i + 1)
						/* grid[x][y]的方向与cur_pos -> npos的移动方向一致 */
						q.push_front(npos);
					else
						q.push_back(npos);
				}
			}
			/* 实际上任意时刻队列中的节点与源点的距离均为d或d+1
			 * 并且所有与源点距离为d的节点都出现在队首附近，所有与源点距离为d+1的节点都出现在队尾附近
			 */
		}
		return dist[m * n -1];
	}
};

/* 我的BFS方法(Speed: beat 93%, Memory: beat 47%)
 * 设树的当前层高为cost, 树中每层的节点就是最少花费cost就能到达的格子
 */
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        row = grid.size();
		col = grid[0].size();
		vector<int> visited(row * col, 0);
		int i = 0, j = 0; /* 坐标 */
		int cost = 0; /* 树高 */
		traverse(0, 0, visited, grid);
		while (!q.empty()) {
			int size = q.size();
			/* 遍历本层树的所有节点 */
			while (size--) {
				auto coordinate = q.front(); q.pop();
				i = coordinate / col; j = coordinate % col;
				if (i == row - 1 && j == col - 1)
					return cost;
				/* 花费更改格子中的数字, 尝试四个不同方向, 找到下一层的节点 */
				for (auto d : direction) {
					traverse(i + d[0], j + d[1], visited, grid);
				}
			}
			cost++;
		}
		return 0;
    }

private:
	int row = 0, col = 0;
	/* 最少花费 'cost' 就能走到的格子
	 * 队列中的每一个元素表示为i * col + j 
	 */
	queue<int> q;

	/* 从i, j出发, 按照grid的方向, 遍历所有能够走到的格子
	 * 即从i, j出发, 不用额外的花费就能走到的格子, 它们应该跟节点(i, j)位于同一层
	 */
	void traverse(int i, int j, vector<int>& visited, vector<vector<int>>& grid) {
		while (true) {
			if (i < 0 || i == row || j < 0 || j == col || visited[i * col + j]  == 1)
				break;
			q.push(i * col + j);
			visited[i * col + j] = 1;
			int d = grid[i][j] - 1;
			i += direction[d][0];
			j += direction[d][1];
		}
	}
};